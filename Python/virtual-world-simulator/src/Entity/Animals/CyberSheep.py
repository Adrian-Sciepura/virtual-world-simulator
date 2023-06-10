import pygame
from queue import Queue
from src.Entity.Animals.Animal import Animal
from src.Entity.Plants.PineHogweed import PineHogweed


class CyberSheep(Animal):

    def __init__(self, world, position):
        temp = pygame.image.load('assets/sheep.png')
        scaled = pygame.transform.scale(temp, (world.scale, world.scale))
        self._neutral = scaled

        temp = pygame.image.load('assets/cyberSheep.png')
        scaled = pygame.transform.scale(temp, (world.scale, world.scale))
        self._cyber = scaled

        super().__init__(self._cyber, world, position, 'C', 11, 4)

        if self.searchForPineHogweed():
            self._texture = self._cyber
        else:
            self._texture = self._neutral

        self._newPosition = (position[0], position[1])
        self._foundPineHogweed = False

    def collision(self, entity):
        if isinstance(entity, CyberSheep):
            breedPosition = self.breed()
            if breedPosition is not None:
                element = CyberSheep(self._world, breedPosition)
                self._world.setMapElement(breedPosition[0], breedPosition[1], element)
            return False
        elif isinstance(entity, PineHogweed):
            return False

        return super().collision(entity)

    def searchForPineHogweed(self):
        visited = [[False for _ in range(self._world.width)] for _ in range(self._world.height)]
        queue = Queue()
        queue.put(self._position)
        visited[self._position[0]][self._position[1]] = True
        directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

        while not queue.empty():
            pos = queue.get()

            for i in range(4):
                newX = pos[0] + directions[i][0]
                newY = pos[1] + directions[i][1]

                if newX < 0 or newX >= self._world.height or newY < 0 or newY >= self._world.width:
                    continue
                elif visited[newX][newY]:
                    continue

                visited[newX][newY] = True
                entity = self._world.getMapElement(newX, newY)

                if entity is not None and entity.symbol == 'P':
                    verticalDiff = self._position[0] - newX
                    verticalIter = (verticalDiff > 0) - (verticalDiff < 0)
                    horizontalDiff = self._position[1] - newY
                    horizontalIter = (horizontalDiff > 0) - (horizontalDiff < 0)
                    self._newPosition = (self._position[0] - verticalIter, self._position[1] - horizontalIter)
                    self._foundPineHogweed = True
                    return True
                else:
                    queue.put((newX, newY))

        self._foundPineHogweed = False
        return False


    def update(self):
        self.searchForPineHogweed()

        if self._foundPineHogweed:
            self._texture = self._cyber
            self.move(self._newPosition)
            self._lifespan += 1
        else:
            self._texture = self._neutral
            super().update()

    def kill(self, entity):
        if isinstance(entity, PineHogweed):
            return False

        return super().kill(entity)



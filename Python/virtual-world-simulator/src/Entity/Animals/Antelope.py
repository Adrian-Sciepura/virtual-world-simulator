import random
import pygame
from src.Entity.Animals.Animal import Animal
from src.Entity.Entity import Entity


class Antelope(Animal):

    def __init__(self, world, position):
        temp = pygame.image.load('assets/antelope.png')
        scaled = pygame.transform.scale(temp, (world.scale, world.scale))
        super().__init__(scaled, world, position, 'A', 4, 4)

    def collision(self, entity):
        if isinstance(entity, Antelope):
            #print("BREED")
            return False

        runAwayChance = random.randint(1, 2)
        if runAwayChance == 2 and self.runAway():
            return True

        return super().collision(entity)

    def update(self):
        currentX = self._position[0]
        currentY = self._position[1]
        newX = currentX
        newY = currentY
        range = random.randint(1, 2)

        while newX == currentX and newY == currentY:
            newX = currentX + random.randint(-range, range)
            newY = currentY + random.randint(-range, range)

            if newX < 0:
                newX = 0
            elif newX > self._world.height - 1:
                newX -= range

            if newY < 0:
                newY = 0
            elif newY > self._world.width - 1:
                newY -= range

        self.move((newX, newY))
        self._lifespan += 1

    def runAway(self):
        currentX = self._position[0]
        currentY = self._position[1]

        for i in range(currentX - 1, currentX + 2):
            if i < 0 or i > self._world.height - 1:
                continue

            for j in range(currentY - 1, currentY + 2):
                if j < 0 or j > self._world.width - 1:
                    continue

                if self._world.getMapElement(i, j) is None:
                    self._world.setMapElement(i, j, self)
                    self._world.setMapElement(self.position[0], self._position[1], None)
                    self._position = (i, j)
                    return True

        return False

import pygame
from src.Entity.Animals.Animal import Animal


class Human(Animal):

    def __init__(self, world, position):
        temp = pygame.image.load('assets/human.png')
        scaled = pygame.transform.scale(temp, (world.scale, world.scale))
        super().__init__(scaled, world, position, 'H', 5, 4)
        self._newPosition = (position[0], position[1])
        self._abilityTurnedOn = False

    @property
    def abilityTurnedOn(self):
        return self._abilityTurnedOn

    @abilityTurnedOn.setter
    def abilityTurnedOn(self, value):
        self._abilityTurnedOn = value

    def setNewPosition(self, keyCode):
        mapWidth = self._world.width
        mapHeight = self._world.height

        if keyCode == pygame.K_UP:
            if self._position[0] != 0:
                self._newPosition = (self._position[0] - 1, self._position[1])
                return True

        elif keyCode == pygame.K_DOWN:
            if self._position[0] != mapHeight - 1:
                self._newPosition = (self._position[0] + 1, self._position[1])
                return True

        elif keyCode == pygame.K_LEFT:
            if self._position[1] != 0:
                self._newPosition = (self._position[0], self._position[1] - 1)
                return True

        elif keyCode == pygame.K_RIGHT:
            if self._position[1] != mapWidth - 1:
                self._newPosition = (self._position[0], self._position[1] + 1)
                return True

        return False

    def update(self):
        self.move(self._newPosition)

        if not self._isAlive:
            self._world.gameOver = True

    def collision(self, entity):

        if self._abilityTurnedOn:
            currentX = self._position[0]
            currentY = self._position[1]

            for i in range(currentX - 1, currentX + 2):
                if i < 0 or i > self._world.height - 1:
                    continue

                for j in range(currentY - 1, currentY + 2):
                    if j < 0 or j > self._world.width - 1:
                        continue

                    if self._world.getMapElement(i, j) is None:
                        self.move((i, j))
                        return True

            return False

        return super().collision(entity)

    def kill(self):
        if not self._abilityTurnedOn:
            super().kill()
            self._world.gameOver = True

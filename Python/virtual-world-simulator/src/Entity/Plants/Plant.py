import random
from enum import Enum

from src.Entity.Entity import Entity

class SpreadChance(Enum):
    LOW = 1
    MEDIUM = 2
    HIGH = 3


class Plant(Entity):

    def __init__(self, texture, world, position, symbol, strength, spreadChance: SpreadChance):
        super().__init__(texture, world, position, symbol, strength, 0)
        self._spreadChance = spreadChance

    def collision(self, entity):
        self.kill()
        return True

    def update(self):
        self._lifespan += 1

    def spread(self):
        chance = random.randint(1, 25)
        if chance > self._spreadChance.value:
            return

        currentX = self._position[0]
        currentY = self._position[1]
        freeFields = []

        for i in range(currentX - 1, currentX + 2):
            if i < 0 or i > self._world.height - 1:
                continue

            for j in range(currentY - 1, currentY + 2):
                if j < 0 or j > self._world.width - 1:
                    continue

                if self._world.getMapElement(i, j) is None:
                    freeFields.append((i, j))

        numberOfPossibleFields = len(freeFields)
        if numberOfPossibleFields > 0:
            newPosition = freeFields[random.randint(0, numberOfPossibleFields - 1)]
            return newPosition

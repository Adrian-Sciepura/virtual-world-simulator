import random

import pygame
from src.Entity.Animals.Animal import Animal


class Fox(Animal):

    def __init__(self, world, position):
        temp = pygame.image.load('assets/fox.png')
        scaled = pygame.transform.scale(temp, (world.scale, world.scale))
        super().__init__(scaled, world, position, 'F', 3, 7)

    def collision(self, entity):
        if isinstance(entity, Fox):
            # print("BREED")
            return False

        return super().collision(entity)

    def update(self):
        currentX = self._position[0]
        currentY = self._position[1]

        possibleMoves = []

        for i in range(currentX - 1, currentX + 2):
            if i < 0 or i > self._world.height - 1:
                continue

            for j in range(currentY - 1, currentY + 2):
                if j < 0 or j > self._world.width - 1 or i == currentX or j == currentY:
                    continue

                element = self._world.getMapElement(i, j)
                if element is None or element.strength <= self._strength:
                    possibleMoves.append((i, j))

        numberOfPossibleMoves = len(possibleMoves)
        if numberOfPossibleMoves > 0:
            newPosition = possibleMoves[random.randint(0, numberOfPossibleMoves - 1)]
            self.move(newPosition)

        self._lifespan += 1

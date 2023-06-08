import pygame
from src.Entity.Plants.Plant import *


class PineHogweed(Plant):

    def __init__(self, world, position):
        temp = pygame.image.load('assets/pineHogweed.png')
        scaled = pygame.transform.scale(temp, (world.scale, world.scale))
        super().__init__(scaled, world, position, 'P', 10, SpreadChance.LOW)

    def update(self):
        currentX = self._position[0]
        currentY = self._position[1]

        for i in range(currentX - 1, currentX + 2):
            if i < 0 or i > self._world.height - 1:
                continue

            for j in range(currentY - 1, currentY + 2):
                if j < 0 or j > self._world.width - 1:
                    continue

                element = self._world.getMapElement(i, j)
                if element is not None and element.priority != 0:
                    element.kill()

        spreadPosition = self.spread()
        if spreadPosition is not None:
            element = PineHogweed(self._world, spreadPosition)
            self._world.setMapElement(spreadPosition[0], spreadPosition[1], element)
        super().update()

    def collision(self, entity):
        entity.kill()
        self.kill()
        return True
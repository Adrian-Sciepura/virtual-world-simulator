import pygame
from src.Entity.Plants.Plant import *


class Dandelion(Plant):

    def __init__(self, world, position):
        temp = pygame.image.load('assets/dandelion.png')
        scaled = pygame.transform.scale(temp, (world.scale, world.scale))
        super().__init__(scaled, world, position, 'D', 0, SpreadChance.LOW)

    def update(self):
        for i in range(3):
            spreadPosition = self.spread()
            if spreadPosition is not None:
                element = Dandelion(self._world, spreadPosition)
                self._world.setMapElement(spreadPosition[0], spreadPosition[1], element)
        super().update()

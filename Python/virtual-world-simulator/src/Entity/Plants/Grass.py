import pygame
from src.Entity.Plants.Plant import *


class Grass(Plant):

    def __init__(self, world, position):
        temp = pygame.image.load('assets/grass.png')
        scaled = pygame.transform.scale(temp, (world.scale, world.scale))
        super().__init__(scaled, world, position, 'G', 0, SpreadChance.MEDIUM)

    def update(self):
        spreadPosition = self.spread()
        if spreadPosition is not None:
            element = Grass(self._world, spreadPosition)
            self._world.setMapElement(spreadPosition[0], spreadPosition[1], element)
        super().update()
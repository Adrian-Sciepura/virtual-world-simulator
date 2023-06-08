import pygame
from src.Entity.Plants.Plant import *


class Nightshade(Plant):

    def __init__(self, world, position):
        temp = pygame.image.load('assets/nightshade.png')
        scaled = pygame.transform.scale(temp, (world.scale, world.scale))
        super().__init__(scaled, world, position, 'N', 99, SpreadChance.LOW)

    def update(self):
        spreadPosition = self.spread()
        if spreadPosition is not None:
            element = Nightshade(self._world, spreadPosition)
            self._world.setMapElement(spreadPosition[0], spreadPosition[1], element)
        super().update()

    def collision(self, entity):
        entity.kill()
        self.kill()
        return True

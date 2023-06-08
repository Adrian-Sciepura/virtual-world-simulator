import pygame
from src.Entity.Plants.Plant import *


class Guarana(Plant):

    def __init__(self, world, position):
        temp = pygame.image.load('assets/guarana.png')
        scaled = pygame.transform.scale(temp, (world.scale, world.scale))
        super().__init__(scaled, world, position, 'U', 0, SpreadChance.LOW)

    def update(self):
        spreadPosition = self.spread()
        if spreadPosition is not None:
            element = Guarana(self._world, spreadPosition)
            self._world.setMapElement(spreadPosition[0], spreadPosition[1], element)
        super().update()

    def collision(self, entity):
        entity.strength = entity.strength + 3
        return super().collision(entity)
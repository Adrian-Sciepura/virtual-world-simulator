import random

import pygame
from src.Entity.Animals.Animal import Animal


class Turtle(Animal):

    def __init__(self, world, position):
        temp = pygame.image.load('assets/turtle.png')
        scaled = pygame.transform.scale(temp, (world.scale, world.scale))
        super().__init__(scaled, world, position, 'T', 2, 1)

    def collision(self, entity):
        if isinstance(entity, Turtle):
            breedPosition = self.breed()
            if breedPosition is not None:
                element = Turtle(self._world, breedPosition)
                self._world.setMapElement(breedPosition[0], breedPosition[1], element)
            return False

        if entity.strength < 5:
            return False

        return super().collision(entity)

    def update(self):
        chance = random.randint(1, 4)
        if chance == 4:
            super().update()
        else:
            self._lifespan += 1

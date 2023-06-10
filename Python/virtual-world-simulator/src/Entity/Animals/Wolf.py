import pygame
from src.Entity.Animals.Animal import Animal


class Wolf(Animal):

    def __init__(self, world, position):
        temp = pygame.image.load('assets/wolf.png')
        scaled = pygame.transform.scale(temp, (world.scale, world.scale))
        super().__init__(scaled, world, position, 'W', 9, 5)

    def collision(self, entity):
        if isinstance(entity, Wolf):
            breedPosition = self.breed()
            if breedPosition is not None:
                element = Wolf(self._world, breedPosition)
                self._world.setMapElement(breedPosition[0], breedPosition[1], element)
            return False

        return super().collision(entity)

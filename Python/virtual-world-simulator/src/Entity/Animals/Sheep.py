import pygame
from src.Entity.Animals.Animal import Animal


class Sheep(Animal):

    def __init__(self, world, position):
        temp = pygame.image.load('assets/sheep.png')
        scaled = pygame.transform.scale(temp, (world.scale, world.scale))
        super().__init__(scaled, world, position, 'S', 4, 4)

    def collision(self, entity):
        if isinstance(entity, Sheep):
            #print("BREED")
            return False

        return super().collision(entity)
import random
import queue
import pygame
from src.App.World import World
from src.Entity.Animals.Wolf import Wolf
from src.Entity.Animals.Antelope import Antelope
from src.Entity.Animals.Fox import Fox
from src.Entity.Animals.Sheep import Sheep
from src.Entity.Animals.Turtle import Turtle
from src.Entity.Animals.Human import Human
from src.Entity.Plants.Grass import Grass
from src.Entity.Plants.Dandelion import Dandelion
from src.Entity.Plants.Guarana import Guarana
from src.Entity.Plants.Nightshade import Nightshade
from src.Entity.Plants.PineHogweed import PineHogweed

class GameManager:

    BACKGROUND_COLOR = (124, 202, 146)

    def __init__(self):
        pygame.init()
        self._screen = pygame.display.set_mode((1200, 720))
        pygame.display.set_caption('Adrian Ściepura 193350')
        self._world = World(self._screen, 20, 20)
        self._entities = queue.PriorityQueue()
        self._player = Human(self._world, (3, 3))
        self._world.setMapElement(3, 3, self._player)
        self.placeEntities()

    def start(self):
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    exit()
                elif event.type == pygame.KEYUP:
                    if self._player.setNewPosition(event.key):
                        self.update()

            self._screen.fill(self.BACKGROUND_COLOR)
            self._world.drawWorld()
            pygame.display.update()

    def update(self):
        for i in range(self._world.height):
            for j in range(self._world.width):
                element = self._world.getMapElement(i, j)
                if element is not None:
                    self._entities.put(element)

        while not self._entities.empty():
            entity = self._entities.get()
            if entity.checkIfAlive():
                entity.update()

    def placeEntities(self):
        freeSpace = self._world.width * self._world.height
        availableTypes = ['W', 'A', 'F', 'S', 'T', 'G', 'D', 'G', 'N', 'P']
        x = 0
        y = 0
        typeToPlace = 0
        howMany = int(freeSpace / 3)
        for i in range(howMany):
            y = random.randint(0, self._world.height - 1)
            x = random.randint(0, self._world.width - 1)
            typeToPlace = random.randint(0, 9)

            if self._world.getMapElement(y, x) is None:
                self._world.setMapElement(y, x, self.getEntityFromSymbol(self._world, (y, x), availableTypes[typeToPlace]))

    def getEntityFromSymbol(self, world, position, symbol):
        types = {
            'W': Wolf(world, position),
            'A': Antelope(world, position),
            'F': Fox(world, position),
            'S': Sheep(world, position),
            'T': Turtle(world, position),
            'G': Grass(world, position),
            'D': Dandelion(world, position),
            'U': Guarana(world, position),
            'N': Nightshade(world, position),
            'P': PineHogweed(world, position)
        }

        return types.get(symbol)

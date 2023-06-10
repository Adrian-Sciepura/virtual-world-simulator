from src.Entity.Animals.Wolf import Wolf
from src.Entity.Animals.Antelope import Antelope
from src.Entity.Animals.Fox import Fox
from src.Entity.Animals.Sheep import Sheep
from src.Entity.Animals.Turtle import Turtle
from src.Entity.Animals.Human import Human
from src.Entity.Animals.CyberSheep import CyberSheep
from src.Entity.Plants.Grass import Grass
from src.Entity.Plants.Dandelion import Dandelion
from src.Entity.Plants.Guarana import Guarana
from src.Entity.Plants.Nightshade import Nightshade
from src.Entity.Plants.PineHogweed import PineHogweed


def getEntityFromSymbol(world, position, symbol):
    types = {
        'W': Wolf(world, position),
        'A': Antelope(world, position),
        'F': Fox(world, position),
        'S': Sheep(world, position),
        'T': Turtle(world, position),
        'C': CyberSheep(world, position),
        'G': Grass(world, position),
        'D': Dandelion(world, position),
        'U': Guarana(world, position),
        'N': Nightshade(world, position),
        'P': PineHogweed(world, position),
        'H': Human(world, position)
    }

    return types.get(symbol)

import os.path
import random
import queue
import pygame
from src.App.World import World
from src.Entity.Animals.Human import Human
from src.UI.Button import Button
from src.App.Other import getEntityFromSymbol


class GameManager:
    BACKGROUND_COLOR = (124, 202, 146)

    def __init__(self):
        pygame.init()
        self._screen = pygame.display.set_mode((1200, 700))
        pygame.display.set_caption('Adrian Ściepura 193350')
        self._newGameButton = Button(self._screen, 800, 200, 200, 50, "New Game", self.newGame)
        self._saveGameButton = Button(self._screen, 800, 260, 200, 50, "Save Game", self.saveGame)
        self._loadGameButton = Button(self._screen, 800, 320, 200, 50, "Load Game", self.loadGame)
        self._abilityButton = Button(self._screen, 800, 380, 200, 50, "Activate ability", self.toggleAbility)
        self._abilityButton.enabled = False
        self._buttons = [self._newGameButton, self._saveGameButton, self._loadGameButton, self._abilityButton]
        self._world = World(self._screen, 20, 20)
        self._entities = queue.PriorityQueue()
        self._player = None
        self._round = 0
        self._abilityCooldown = 5
        self._abilityDuration = 0
        self.placeEntities()

        if not os.path.exists("save.txt"):
            self._loadGameButton.enabled = False

    def start(self):
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    exit()
                elif event.type == pygame.KEYUP:
                    if self._player.setNewPosition(event.key) and not self._world.gameOver:
                        self.update()

                self._world.handleEvent(event)
                for bt in self._buttons:
                    bt.handleEvent(event)

            self._screen.fill(self.BACKGROUND_COLOR)
            self._world.drawWorld()
            self.displayMenu()
            pygame.display.update()

    def update(self):
        self._round += 1
        self._world.clearLogs()
        if self._player.abilityTurnedOn:
            if self._abilityDuration == 0:
                self._player.abilityTurnedOn = False
            self._abilityDuration -= 1
        elif self._abilityCooldown > 0:
            self._abilityCooldown -= 1
            if self._abilityCooldown == 0:
                self._abilityButton.enabled = True

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
        self._player = Human(self._world, (3, 3))
        self._world.setMapElement(3, 3, self._player)

        freeSpace = self._world.width * self._world.height
        availableTypes = ['W', 'A', 'F', 'S', 'T', 'C', 'G', 'D', 'U', 'N', 'P']
        x = 0
        y = 0
        typeToPlace = 0
        howMany = int(freeSpace / 3)
        for i in range(howMany):
            y = random.randint(0, self._world.height - 1)
            x = random.randint(0, self._world.width - 1)
            typeToPlace = random.randint(0, 10)

            if self._world.getMapElement(y, x) is None:
                self._world.setMapElement(y, x, getEntityFromSymbol(self._world, (y, x), availableTypes[typeToPlace]))

    def displayMenu(self):
        menuText = [("Adrian Ściepura", 50), ("Round: " + str(self._round), 35),
                    ("Ability Cooldown: " + str(self._abilityCooldown) if not self._player.abilityTurnedOn else "Ability Duration: " + str(self._abilityDuration), 35)]
        y = 50
        for element in menuText:
            font = pygame.font.Font(None, element[1])
            self._screen.blit(font.render(element[0], False, 'White'), (800, y))
            y += element[1]

        for bt in self._buttons:
            bt.draw()

        if self._world.gameOver:
            font = pygame.font.Font(None, 60)
            self._screen.blit(font.render("Game Over", False, 'Red'), (250, 300))

        self._world.showLastLogs((800, 450), 10)

    def newGame(self):
        self._world.restart()
        self.placeEntities()
        self._round = 0
        self._abilityCooldown = 5
        self._abilityDuration = 0

    def saveGame(self):
        file = open("save.txt", "w")
        file.write(str(self._world.width) + ' ' + str(self._world.height) + ' ' + str(self._round) + ' ' + str(self._world.gameOver) + '\n')
        file.write(str(self._abilityDuration) + ' ' + str(self._abilityCooldown) + '\n')
        for i in range(self._world.height):
            for j in range(self._world.width):
                entity = self._world.getMapElement(i, j)
                if entity is not None:
                    file.write(
                        str(entity.symbol) + ' ' + str(entity.position[0]) + ' ' + str(entity.position[1]) + ' ' + str(
                            entity.lifespan) + ' ' + str(entity.strength) + '\n')
        file.close()
        self._loadGameButton.enabled = True

    def loadGame(self):
        if not os.path.exists("save.txt"):
            return

        file = open("save.txt", "r")
        self._world.restart()
        line = file.readline().strip().split()
        self._world.width = int(line[0])
        self._world.height = int(line[1])
        self._round = int(line[2])
        self._world.gameOver = True if line[3] == "True" else False

        line = file.readline().strip().split()
        self._abilityDuration = int(line[0])
        self._abilityCooldown = int(line[1])


        for line in file:
            letter, x, y, lifespan, strength = line.strip().split()
            x = int(x)
            y = int(y)
            lifespan = int(lifespan)
            strength = int(strength)
            entity = getEntityFromSymbol(self._world, (x, y), letter)
            entity.lifespan = lifespan
            entity.strength = strength
            self._world.setMapElement(x, y, entity)
            if letter == 'H':
                self._player = entity

        if self._abilityDuration > 0:
            self._abilityButton.enabled = False
            self._player.abilityTurnedOn = True

        file.close()

    def toggleAbility(self):
        self._player.abilityTurnedOn = True
        self._abilityButton.enabled = False
        self._abilityDuration = 5
        self._abilityCooldown = 5

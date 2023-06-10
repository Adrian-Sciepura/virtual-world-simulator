import src.Entity.Entity
import pygame
from src.UI.Button import Button
from src.App.Other import getEntityFromSymbol


class World:

    def __init__(self, screen, width, height):
        self._width = width
        self._height = height
        self._gameOver = False
        self._map = [[None for _ in range(width)] for _ in range(height)]
        self._screen = screen
        self._scale = 0
        self._rect = None
        self.setSize(width, height)
        self._hoverPosition = None
        self._contextMenuElements = None
        self._contextMenuRect = None
        self._lastLogs = []
        self._numberOfLogs = 0
        self._font = pygame.font.Font(None, 25)

    def setSize(self, width, height):
        self._width = width
        self._height = height
        self._scale = int(700 / width)
        self._rect = pygame.Rect(0, 0, width * self._scale, height * self._scale)

    def handleEvent(self, event):
        if event.type == pygame.MOUSEBUTTONUP and event.button == 1:
            if self._contextMenuRect is not None:
                if self._contextMenuRect.collidepoint(event.pos):
                    for element in self._contextMenuElements:
                        element.handleEvent(event)
                    self._contextMenuRect = None
                else:
                    self._contextMenuRect = None
            elif self._rect.collidepoint(event.pos) and self._map[self._hoverPosition[1]][self._hoverPosition[0]] is None:
                self.createContextMenu((self._hoverPosition[0] * self._scale, self._hoverPosition[1] * self._scale))

        elif event.type == pygame.MOUSEMOTION:
            if self._contextMenuRect is not None and self._contextMenuRect.collidepoint(event.pos):
                for element in self._contextMenuElements:
                    element.handleEvent(event)
            elif self._rect.collidepoint(event.pos):
                self._hoverPosition = (int(event.pos[0] / self._scale), int(event.pos[1] / self._scale))
            else:
                self._hoverPosition = None

    @property
    def width(self):
        return self._width

    @width.setter
    def width(self, value):
        width = value

    @property
    def height(self):
        return self._height

    @height.setter
    def height(self, value):
        height = value

    @property
    def gameOver(self):
        return self._gameOver

    @gameOver.setter
    def gameOver(self, value):
        self._gameOver = value

    @property
    def scale(self):
        return self._scale

    def getMapElement(self, x, y):
        return self._map[x][y]

    def setMapElement(self, x, y, value):
        self._map[x][y] = value

    def drawWorld(self):
        for i in range(self._height):
            for j in range(self._width):
                if self._map[i][j] is not None:
                    self._screen.blit(self._map[i][j].texture, (j * self._scale, i * self._scale))

        for i in range(self._height + 1):
            pygame.draw.line(self._screen, (255, 255, 255), (0, i * self._scale),
                             (self._width * self._scale, i * self._scale))

        for i in range(self._width + 1):
            pygame.draw.line(self._screen, (255, 255, 255), (i * self._scale, 0),
                             (i * self._scale, self._height * self._scale))

        if self._hoverPosition is not None:
            for i in range(2):
                pygame.draw.line(self._screen, 'BLUE',
                                 (self._hoverPosition[0] * self._scale, (self._hoverPosition[1] + i) * self._scale),
                                 ((self._hoverPosition[0] + 1) * self._scale,
                                  (self._hoverPosition[1] + i) * self._scale), 2)

            for i in range(2):
                pygame.draw.line(self._screen, 'BLUE',
                                 ((self._hoverPosition[0] + i) * self._scale, (self._hoverPosition[1]) * self._scale),
                                 ((self._hoverPosition[0] + i) * self._scale,
                                  (self._hoverPosition[1] + 1) * self._scale), 2)

        if self._contextMenuRect is not None:
            self.drawContextMenu()

    def restart(self):
        self.clearLogs()
        for i in range(self._height):
            for j in range(self._width):
                self._map[i][j] = None
                self._gameOver = False

    def drawContextMenu(self):
        i = 0
        for element in self._contextMenuElements:
            element.draw()
            i += 1

    def createContextMenu(self, position):
        entitiesToAdd = [("Wolf", 'W'), ("Antelope", 'A'), ("Fox", 'F'), ("Sheep", 'S'), ("Turtle", 'T'),
                         ("Grass", 'G'), ("Dandelion", 'D'), ("Guarana", 'U'), ("Nightshade", 'N'),
                         ("Pine Hogweed", 'P')]
        i = 0
        self._contextMenuElements = []
        self._contextMenuRect = pygame.Rect(position[0] + self._scale, position[1], 150, len(entitiesToAdd) * 30)
        positionInArray = (int(position[1] / self._scale), int(position[0] / self._scale))
        for element in entitiesToAdd:
            self._contextMenuElements.append(
                Button(self._screen,
                       position[0] + self._scale,
                       position[1] + i * 30, 150,
                       30,
                       element[0],
                       lambda x=element[1]: self.setMapElement(positionInArray[0], positionInArray[1], getEntityFromSymbol(self, (positionInArray[0], positionInArray[1]), x))))
            i += 1

    def addLog(self, position, text):
        self._numberOfLogs += 1
        self._lastLogs.append('[' + str(position[0]) + ' ' + str(position[1]) + '] ' + text)

    def clearLogs(self):
        self._lastLogs = []
        self._numberOfLogs = 0

    def showLastLogs(self, position, number):
        howManyToShow = number if number <= self._numberOfLogs else self._numberOfLogs

        for log in range(howManyToShow):
            self._screen.blit(self._font.render(self._lastLogs[self._numberOfLogs - log - 1], False, 'White'),
                              (position[0], position[1] + log * 20))

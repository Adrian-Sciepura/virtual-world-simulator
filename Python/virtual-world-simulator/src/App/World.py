import src.Entity.Entity
import pygame


class World:

    def __init__(self, screen, width, height):
        self._width = width
        self._height = height
        self._gameOver = False
        self._map = [[None for _ in range(width)] for _ in range(height)]
        self._screen = screen
        self._scale = 35

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
            pygame.draw.line(self._screen, (255, 255, 255), (0, i * self._scale), (self._width * self._scale, i * self._scale))

        for i in range(self._width + 1):
            pygame.draw.line(self._screen, (255, 255, 255), (i * self._scale, 0), (i * self._scale, self._height * self._scale))
import pygame


class Button:

    def __init__(self, surface, x, y, width, height, text, onClickEvent):
        self._enabled = True
        self._text = text
        self._x = x
        self._y = y
        self._width = width
        self._height = height
        self._rect = pygame.Rect(self._x, self._y, self._width, self._height)
        self._surface = surface
        self._font = pygame.font.Font(None, 30)
        self._textSize = self._font.size(self._text)
        self._margins = ((self._width - self._textSize[0]) / 2, (self._height - self._textSize[1]) / 2)
        self._onClickEvent = onClickEvent
        self._hover = False

    def draw(self):
        if not self._enabled:
            pygame.draw.rect(self._surface, (224, 224, 224), self._rect)
        elif self._hover:
            pygame.draw.rect(self._surface, (160, 160, 160), self._rect)
        else:
            pygame.draw.rect(self._surface, (192, 192, 192), self._rect)

        self._surface.blit(self._font.render(self._text, False, 'White'), (self._x + self._margins[0], self._y + self._margins[1]))

    def handleEvent(self, event):
        if event.type == pygame.MOUSEBUTTONUP and event.button == 1:
            if self._rect.collidepoint(event.pos):
                self._onClickEvent()
        elif event.type == pygame.MOUSEMOTION:
            if self._rect.collidepoint(event.pos):
                if not self._hover:
                    self._hover = True
                    #pygame.mouse.set_cursor(pygame.SYSTEM_CURSOR_HAND)
            else:
                self._hover = False

    @property
    def enabled(self):
        return self._enabled

    @enabled.setter
    def enabled(self, value):
        self._enabled = value

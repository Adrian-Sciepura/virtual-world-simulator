
class Entity:

    def __init__(self, texture, world, position, symbol, strength, priority):
        self._texture = texture
        self._world = world
        self._position = position
        self._symbol = symbol
        self._strength = strength
        self._priority = priority
        self._isAlive = True
        self._lifespan = 0

    def __lt__(self, other):
        if self._priority == other.priority:
            return self._lifespan > other.lifespan
        else:
            return self._priority > other.priority

    def kill(self, entity):
        self._isAlive = False
        self._world.setMapElement(self._position[0], self._position[1], None)
        return True

    def checkIfAlive(self):
        return self._isAlive

    def update(self):
        raise NotImplementedError("Abstract method")

    def collision(self, entity):
        raise NotImplementedError("Abstract method")

    @property
    def texture(self):
        return self._texture

    @property
    def world(self):
        return self._world

    @property
    def position(self):
        return self._position

    @property
    def symbol(self):
        return self._symbol

    @property
    def strength(self):
        return self._strength

    @strength.setter
    def strength(self, value):
        self._strength = value

    @property
    def priority(self):
        return self._priority

    @property
    def lifespan(self):
        return self._lifespan

    @lifespan.setter
    def lifespan(self, value):
        self._lifespan = value
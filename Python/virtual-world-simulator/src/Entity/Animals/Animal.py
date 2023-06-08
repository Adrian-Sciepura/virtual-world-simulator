from src.Entity.Entity import Entity
import random


class Animal(Entity):

    def __init__(self, texture, world, position, symbol, strength, priority):
        super().__init__(texture, world, position, symbol, strength, priority)

    def move(self, newPosition):
        entity = self._world.getMapElement(newPosition[0], newPosition[1])
        if entity is not None:
            result = entity.collision(self)
            if self._isAlive is False or not result:
                return

        self._world.setMapElement(self._position[0], self._position[1], None)
        self._position = (newPosition[0], newPosition[1])
        self._world.setMapElement(self._position[0], self._position[1], self)

    def update(self):
        currentX = self._position[0]
        currentY = self._position[1]
        newX = currentX
        newY = currentY

        while newX == currentX and newY == currentY:
            newX = currentX + random.randint(-1, 1)
            newY = currentY + random.randint(-1, 1)

            if newX < 0:
                newX = 0
            elif newX > self._world.height - 1:
                newX -= 1

            if newY < 0:
                newY = 0
            elif newY > self._world.width - 1:
                newY -= 1

        self.move((newX, newY))
        self._lifespan += 1

    def collision(self, entity):
        if self._lifespan == 0:
            return False

        entityStrength = entity.strength

        if entityStrength > self._strength or (entityStrength == self._strength and entity.lifespan > self._lifespan):
            self.kill()
            return True

        entity.kill()
        return False

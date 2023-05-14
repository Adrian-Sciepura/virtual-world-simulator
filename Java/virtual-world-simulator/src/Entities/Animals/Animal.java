package Entities.Animals;

import App.World;
import Common.Point;
import Entities.Entity;

import javax.swing.*;
import java.util.Random;

public class Animal extends Entity
{
    protected static int numberOfAnimals = 0;

    public Animal(ImageIcon icon, World world, Point position, char symbol, int strength, int priority)
    {
        super(icon, world, position, symbol, strength, priority);
        numberOfAnimals++;
    }

    public static int getNumberOfAnimals()
    {
        return numberOfAnimals;
    }

    public void Move(Point newPosition)
    {
        Entity entity = world.map[newPosition.x][newPosition.y].getEntity();
        if(entity != null)
        {
            boolean result = entity.Collision(this);
            if(this.isAlive == false || !result)
                return;
        }

        world.map[position.x][position.y].setEntity(null);
        this.position = newPosition;
        world.map[newPosition.x][newPosition.y].setEntity(this);
    }

    public void Update()
    {
        int currentX = position.x;
        int currentY = position.y;
        int newX = currentX;
        int newY = currentY;

        Random rnd = new Random();

        while(newX == currentX && newY == currentY)
        {
            newX = currentX + rnd.nextInt(3) - 1;
            newY = currentY + rnd.nextInt(3) - 1;

            if(newX < 0)
                newX = 0;
            else if(newX > world.worldHeight - 1)
                newX -= 1;

            if(newY < 0)
                newY = 0;
            else if(newY > world.worldWidth - 1)
                newY -= 1;
        }

        this.Move(new Point(newX, newY));
        super.Update();
    }

    public boolean Collision(Entity entity)
    {
        if(this.lifespan == 0)
            return false;

        int entityStrength = entity.getStrength();

        if(entityStrength > strength || (entityStrength == strength && entity.getLifespan() > lifespan))
        {
            Kill();
            return true;
        }

        entity.Kill();
        return false;
    }

    public void Kill()
    {
        super.Kill();
        numberOfAnimals--;
    }
}

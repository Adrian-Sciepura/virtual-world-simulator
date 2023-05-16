package Entities.Animals;

import App.World;
import Common.Point;
import Entities.Entity;
import GUI.MapElement;

import javax.swing.*;
import java.util.ArrayList;
import java.util.Random;

public abstract class Animal extends Entity
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
        position.x = newPosition.x;
        position.y = newPosition.y;
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
            world.AppendLogs(position.x, position.y, Entity.types.get(this.symbol) + " was killed by " + Entity.types.get(entity.getSymbol()));
            Kill();
            return true;
        }

        world.AppendLogs(position.x, position.y, Entity.types.get(entity.getSymbol()) + " was killed by " + Entity.types.get(this.symbol));
        entity.Kill();
        return false;
    }

    public void Kill()
    {
        super.Kill();
        numberOfAnimals--;
    }

    protected void AddChild(Entity entity)
    {
        int currentX = position.x;
        int currentY = position.y;
        ArrayList<MapElement> freeFields = new ArrayList<>();

        for(int i = currentX - 1; i <= currentX + 1; i++)
        {
            if(i < 0 || i > world.worldHeight - 1)
                continue;

            for(int j = currentY - 1; j <= currentY + 1; j++)
            {
                if(j < 0 || j > world.worldWidth - 1 || (i == currentX && j == currentY))
                    continue;

                Entity entityOnField = world.map[i][j].getEntity();
                if(entityOnField == null || entityOnField.getPriority() == 0)
                {
                    freeFields.add(world.map[i][j]);
                }
            }
        }

        if(freeFields.size() > 0)
        {
            Random rnd = new Random();
            int index = rnd.nextInt(freeFields.size());
            MapElement field = freeFields.get(index);
            int x = field.getPosition().x;
            int y = field.getPosition().y;
            field.setEntity(entity);
            entity.setPosition(field.getPosition());
            world.AppendLogs(x, y, Entity.types.get(entity.getSymbol()) + " was born");
        }
        else
        {
            numberOfAnimals--;
        }
    }
}

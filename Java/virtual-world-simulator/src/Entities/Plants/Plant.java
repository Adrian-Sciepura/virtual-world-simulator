package Entities.Plants;

import App.World;
import Common.Point;
import Entities.Entity;
import GUI.MapElement;

import javax.swing.*;
import java.util.ArrayList;
import java.util.Random;

public abstract class Plant extends Entity
{
    protected static int numberOfPlants = 0;
    protected int spreadChance;
    protected enum SpreadChance
    {
        LOW,
        MEDIUM,
        HIGH
    }

    public Plant(ImageIcon icon, World world, Point position, char symbol, int strength, int priority, SpreadChance spreadChance)
    {
        super(icon, world, position, symbol, strength, priority);
        this.spreadChance = spreadChance.ordinal() + 1;
        numberOfPlants++;
    }

    public static int getNumberOfPlants()
    {
        return numberOfPlants;
    }

    public void Update()
    {
        super.Update();
    }

    public boolean Collision(Entity entity)
    {
        world.AppendLogs(position.x, position.y, Entity.types.get(this.symbol) + " has been eaten by " + Entity.types.get(entity.getSymbol()));
        Kill();
        return true;
    }

    public void Kill()
    {
        super.Kill();
        numberOfPlants--;
    }

    public void Spread(Entity entity)
    {
        Random rnd2 = new Random();
        int chance = rnd2.nextInt(25) + 1;
        if(chance > spreadChance)
        {
            numberOfPlants--;
            return;
        }

        int currentX = position.x;
        int currentY = position.y;
        ArrayList<MapElement> freeFields = new ArrayList<MapElement>();

        for(int i = currentX - 1; i <= currentX + 1; i++)
        {
            if(i < 0 || i > world.worldHeight - 1)
                continue;

            for(int j = currentY - 1; j <= currentY + 1; j++)
            {
                if(j < 0 || j > world.worldWidth - 1 || (i == currentX && j == currentY))
                    continue;

                if(world.map[i][j].getEntity() == null)
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
            entity.setPosition(field.getPosition());
            field.setEntity(entity);
            world.AppendLogs(x, y, Entity.types.get(entity.getSymbol()) + " spread");
        }
        else
        {
            numberOfPlants--;
        }
    }
}

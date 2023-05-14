package Entities.Animals;

import App.World;
import Common.Point;
import Entities.Entity;
import GUI.SquareMapElement;

import javax.swing.*;
import java.util.ArrayList;
import java.util.Random;

public class Antelope extends Animal
{
    public Antelope(World world, Point position)
    {
        super(new ImageIcon("assets/antelope.png"), world, position, 'A', 4, 4);
    }

    public boolean Collision(Entity entity)
    {
        if(entity instanceof Antelope)
        {
            Antelope antelope = new Antelope(this.world, new Point(-1, -1));
            AddChild(antelope);
            return false;
        }

        Random rnd = new Random();
        int runAwayChance = rnd.nextInt(2);
        if(runAwayChance == 0 && RunAway())
            return true;

        return super.Collision(entity);
    }

    public void Update()
    {
        Random rnd = new Random();
        int currentX = position.x;
        int currentY = position.y;
        int newX = currentX;
        int newY = currentY;


        while(newX == currentX && newY == currentY)
        {
            newX = currentX + rnd.nextInt(5) - 2;
            newY = currentY + rnd.nextInt(5) - 2;

            if(newX < 0)
                newX = 0;
            else if(newX > world.worldHeight - 2)
                newX -= 2;

            if(newY < 0)
                newY = 0;
            else if(newY > world.worldWidth - 2)
                newY -= 2;
        }

        this.Move(new Point(newX, newY));
        lifespan++;
    }

    public boolean RunAway()
    {
        int currentX = position.x;
        int currentY = position.y;

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
                    this.Move(new Point(i, j));
                    return true;
                }
            }
        }
        return false;
    }
}

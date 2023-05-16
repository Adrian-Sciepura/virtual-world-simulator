package Entities.Animals;

import App.World;
import Common.Point;
import Entities.Entity;
import GUI.MapElement;

import javax.swing.*;
import java.util.ArrayList;
import java.util.Random;

public class Fox extends Animal
{
    public Fox(World world, Point position)
    {
        super(new ImageIcon("assets/fox.png"), world, position, 'F', 3, 7);
    }

    public boolean Collision(Entity entity)
    {
        if(entity instanceof Fox)
        {
            Fox fox = new Fox(this.world, new Point(-1, -1));
            AddChild(fox);
            return false;
        }

        return super.Collision(entity);
    }

    public void Update()
    {
        int currentX = position.x;
        int currentY = position.y;
        ArrayList<MapElement> possibleMoves = new ArrayList<MapElement>();

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
                    possibleMoves.add(world.map[i][j]);
                }
            }
        }

        if(possibleMoves.size() > 0)
        {
            Random rnd = new Random();
            int randomIndex = rnd.nextInt(possibleMoves.size());
            Move(possibleMoves.get(randomIndex).getPosition());
        }
        super.Update();
    }
}

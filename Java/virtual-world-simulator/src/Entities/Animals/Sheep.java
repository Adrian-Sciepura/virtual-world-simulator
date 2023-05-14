package Entities.Animals;

import App.World;
import Common.Point;
import Entities.Entity;

import javax.swing.*;

public class Sheep extends Animal
{
    public Sheep(World world, Point position)
    {
        super(new ImageIcon("assets/sheep.png"), world, position, 'S', 4, 4);
    }

    public boolean Collision(Entity entity)
    {
        if(entity instanceof Sheep)
        {
            return false;
        }

        return super.Collision(entity);
    }
}

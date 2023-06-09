package Entities.Animals;

import App.World;
import Common.Point;
import Entities.Entity;

import javax.swing.*;

public class Wolf extends Animal
{
    public Wolf(World world, Point position)
    {
        super(new ImageIcon("assets/wolf.png"), world, position, 'W', 9, 5);
    }

    public boolean Collision(Entity entity)
    {
        if(entity instanceof Wolf)
        {
            Wolf wolf = new Wolf(this.world, new Point(-1, -1));
            AddChild(wolf);
            return false;
        }

        return super.Collision(entity);
    }
}

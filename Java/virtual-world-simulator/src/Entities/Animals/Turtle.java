package Entities.Animals;

import App.World;
import Common.Point;
import Entities.Entity;

import javax.swing.*;
import java.util.Random;

public class Turtle extends Animal
{
    public Turtle(World world, Point position)
    {
        super(new ImageIcon("assets/turtle.png"), world, position, 'T', 2, 1);
    }

    public boolean Collision(Entity entity)
    {
        if(entity instanceof Turtle)
        {
            Turtle turtle = new Turtle(this.world, new Point(-1, -1));
            AddChild(turtle);
            return false;
        }

        if(entity.getStrength() < 5)
            return false;

        return super.Collision(entity);
    }

    public void Update()
    {
        Random rnd = new Random();
        int chance = rnd.nextInt(4);
        if(chance == 3)
            super.Update();
        else
            lifespan++;
    }
}

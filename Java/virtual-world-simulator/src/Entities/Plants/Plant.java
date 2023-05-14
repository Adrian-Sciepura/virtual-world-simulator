package Entities.Plants;

import App.World;
import Common.Point;
import Entities.Entity;

import javax.swing.*;

public class Plant extends Entity
{
    protected static int numberOfPlants = 0;

    public Plant(ImageIcon icon, World world, Point position, char symbol, int strength, int priority)
    {
        super(icon, world, position, symbol, strength, priority);
        numberOfPlants++;
    }

    public static int getNumberOfPlants()
    {
        return numberOfPlants;
    }

    public void Update()
    {

    }

    public boolean Collision(Entity entity)
    {
        return false;
    }

    public void Kill()
    {
        super.Kill();
        numberOfPlants--;
    }
}

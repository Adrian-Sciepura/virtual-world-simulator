package Entities.Plants;

import App.World;
import Common.Point;

import javax.swing.*;

public class Dandelion extends Plant
{
    public Dandelion(World world, Point position)
    {
        super(new ImageIcon("assets/dandelion.png"), world, position, 'D', 0, 0, SpreadChance.LOW);
    }

    public void Update()
    {
        super.Update();

        for(int i = 0; i < 3; i++)
            Spread(new Grass(this.world, new Point(-1, -1)));
    }
}

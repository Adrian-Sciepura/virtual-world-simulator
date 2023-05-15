package Entities.Plants;

import App.World;
import Common.Point;

import javax.swing.*;

public class Grass extends Plant
{
    public Grass(World world, Point position)
    {
        super(new ImageIcon("assets/grass.png"), world, position, 'G', 0, 0, SpreadChance.MEDIUM);
    }

    public void Update()
    {
        super.Update();
        Spread(new Grass(this.world, new Point(-1, -1)));
    }
}

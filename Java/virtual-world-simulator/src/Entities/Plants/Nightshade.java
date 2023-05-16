package Entities.Plants;

import App.World;
import Common.Point;
import Entities.Entity;

import javax.swing.*;

public class Nightshade extends Plant
{
    public Nightshade(World world, Point position)
    {
        super(new ImageIcon("assets/nightshade.png"), world, position, 'N', 99, 0, SpreadChance.LOW);
    }

    public void Update()
    {
        super.Update();
        Spread(new Nightshade(this.world, new Point(-1, -1)));
    }

    public boolean Collision(Entity entity)
    {
        entity.Kill();
        Kill();
        return true;
    }
}

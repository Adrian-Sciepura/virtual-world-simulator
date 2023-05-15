package Entities.Plants;

import App.World;
import Common.Point;
import Entities.Entity;

import javax.swing.*;

public class Guarana extends Plant
{
    public Guarana(World world, Point position)
    {
        super(new ImageIcon("assets/guarana.png"), world, position, 'U', 0, 0, SpreadChance.MEDIUM);
    }

    public void Update()
    {
        super.Update();
        Spread(new Grass(this.world, new Point(-1, -1)));
    }

    public boolean Collision(Entity entity)
    {
        entity.setStrength(entity.getStrength() + 3);
        return super.Collision(entity);
    }
}

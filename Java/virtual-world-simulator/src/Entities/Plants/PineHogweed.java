package Entities.Plants;

import App.World;
import Common.Point;
import Entities.Entity;

import javax.swing.*;

public class PineHogweed extends Plant
{
    public PineHogweed(World world, Point position)
    {
        super(new ImageIcon("assets/pineHogweed.png"), world, position, 'P', 10, 0, SpreadChance.LOW);
    }

    public void Update()
    {
        super.Update();
        Spread(new PineHogweed(this.world, new Point(-1, -1)));

        int currentX = position.x;
        int currentY = position.y;

        for (int i = currentX - 1; i <= currentX + 1; i++)
        {
            if (i < 0 || i > world.worldHeight - 1)
                continue;

            for (int j = currentY - 1; j <= currentY + 1; j++)
            {
                if (j < 0 || j > world.worldWidth - 1)
                    continue;

                Entity entity = world.map[i][j].getEntity();
                if (entity != null && entity.getPriority() != 0)
                    entity.Kill();
            }
        }
    }

    public boolean Collision(Entity entity)
    {
        entity.Kill();
        Kill();
        return true;
    }
}

package Entities.Animals;

import App.World;
import Common.Point;
import Entities.Entity;

import javax.swing.*;
import java.awt.event.KeyEvent;

public class Human extends Animal
{
    protected boolean abilityTurnedOn;
    protected Common.Point newPosition;

    public Human(World world, Point position)
    {
        super(new ImageIcon("assets/human.png"), world, position, 'H', 99, 4);
        abilityTurnedOn = false;
        newPosition = new Point(position.x, position.y);
    }

    public void Update()
    {
        this.Move(newPosition);
        lifespan++;

        if(!isAlive)
            world.EndGame();
    }

    public boolean Collision(Entity entity)
    {
        if (abilityTurnedOn)
        {
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

                    if (world.map[i][j].getEntity() == null)
                    {
                        Move(new Common.Point(i, j));
                        return true;
                    }
                }
            }
            return false;
        }

        boolean temp = super.Collision(entity);
        if (!isAlive)
            world.EndGame();

        return temp;
    }

    public boolean CheckIfAbilityTurnedOn()
    {
        return this.abilityTurnedOn;
    }

    public void ToggleAbility(boolean value)
    {
        this.abilityTurnedOn = value;
    }

    public boolean setNewPosition(int keyCode)
    {
        int mapWidth = world.worldWidth;
        int mapHeight = world.worldHeight;

        switch (keyCode)
        {
            case KeyEvent.VK_UP:
            {
                if (position.x == 0)
                    break;

                newPosition.x = (position.x - 1);
                return true;
            }
            case KeyEvent.VK_DOWN:
            {
                if (position.x == mapHeight - 1)
                    break;

                newPosition.x = (position.x + 1);
                return true;
            }
            case KeyEvent.VK_LEFT:
            {
                if (position.y == 0)
                    break;

                newPosition.y = (position.y - 1);
                return true;
            }
            case KeyEvent.VK_RIGHT:
            {
                if (position.y == mapWidth - 1)
                    break;

                newPosition.y = (position.y + 1);
                return true;
            }
        }

        return false;
    }

    public Common.Point getNewPosition()
    {
        return this.newPosition;
    }
}

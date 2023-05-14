package App;

import Entities.Entity;
import GUI.SquareMapElement;

import javax.swing.*;
import java.awt.*;

public class World
{
    public SquareMapElement map[][];
    public int worldWidth;
    public int worldHeight;

    public World()
    {
        map = new SquareMapElement[20][20];
        worldWidth = 20;
        worldHeight = 20;

        for(int i = 0; i < worldHeight; i++)
        {
            for (int j = 0; j < worldWidth; j++)
            {
                map[i][j] = new SquareMapElement();
                map[i][j].setPreferredSize(new Dimension(10, 10));
            }
        }
    }
}
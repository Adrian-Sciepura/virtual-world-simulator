package App;

import GUI.MapElement;
import java.awt.*;

public class World
{
    public MapElement map[][];
    private String logs;
    public int worldWidth;
    public int worldHeight;
    private boolean gameOver;

    public World()
    {
        gameOver = false;
        logs = new String("");
    }

    public void AppendLogs(int x, int y, String message)
    {
        logs += "[ " + x + ", " + y + " ]  " + message + "\n";
    }

    public void ClearLogs()
    {
        logs = new String("");
    }

    public String getLogs()
    {
        return logs;
    }

    public void Reset()
    {
        for(int i = 0; i < worldHeight; i++)
        {
            for (int j = 0; j < worldWidth; j++)
            {
                if (map[i][j].getEntity() != null)
                    map[i][j].getEntity().Kill();
            }
        }
        gameOver = false;
    }

    public void EndGame()
    {
        gameOver = true;
        logs += "- - - - - - - - GAME OVER - - - - - - - -\n";
    }

    public void setGameOver(boolean value)
    {
        this.gameOver = value;
    }

    public boolean CheckIfGameOver()
    {
        return gameOver;
    }

    public void setWorldSize(int width, int height)
    {
        this.worldWidth = width;
        this.worldHeight = height;

        map = new MapElement[height][width];

        for(int i = 0; i < worldHeight; i++)
        {
            for (int j = 0; j < worldWidth; j++)
            {
                map[i][j] = new MapElement();
                map[i][j].setPreferredSize(new Dimension(10, 10));
            }
        }
    }
}

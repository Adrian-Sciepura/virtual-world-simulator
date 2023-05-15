package App;

import GUI.SquareMapElement;
import java.awt.*;

public class World
{
    public SquareMapElement map[][];
    private String logs;
    public int worldWidth;
    public int worldHeight;
    private boolean gameOver;

    public World()
    {
        map = new SquareMapElement[20][20];
        worldWidth = 20;
        worldHeight = 20;
        gameOver = false;
        logs = new String("");

        for(int i = 0; i < worldHeight; i++)
        {
            for (int j = 0; j < worldWidth; j++)
            {
                map[i][j] = new SquareMapElement();
                map[i][j].setPreferredSize(new Dimension(10, 10));
            }
        }
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
            gameOver = false;
        }
    }

    public void EndGame()
    {
        gameOver = true;
        logs += "- - - - - - - - GAME OVER - - - - - - - -\n";
    }

    public boolean CheckIfGameOver()
    {
        return gameOver;
    }
}

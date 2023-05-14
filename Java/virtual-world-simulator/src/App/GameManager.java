package App;

import Common.Point;
import Entities.Animals.Animal;
import Entities.Entity;

import javax.swing.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.PriorityQueue;
import java.util.Random;

public class GameManager
{
    private static volatile GameManager instance;
    private World world;
    private PriorityQueue<Entity> entities;
    public static GameManager GetInstance()
    {
        GameManager result = instance;
        if(result != null)
        {
            return result;
        }
        synchronized (GameManager.class)
        {
            if(instance == null)
            {
                instance = new GameManager();
            }
            return instance;
        }
    }

    private GameManager()
    {
        world = new World();
        entities = new PriorityQueue<Entity>(Entity::compareTo);
    }

    public void Start()
    {
        PlaceEntities();
        WindowManager window = WindowManager.GetInstance();
        window.ToggleWindowVisibility();
        window.SetWindowSize(1200, 800);
        window.SetWindowTitle("Adrian Ściepura 193350");

        JPanel gamePanel = window.GetGamePanel();
        for(int i = 0; i < 20; i++)
            for(int j = 0; j < 20; j++)
            {
                gamePanel.add(world.map[i][j]);
            }

        JFrame frame = window.GetWindow();
        frame.addKeyListener(new KeyListener()
        {
            @Override
            public void keyTyped(KeyEvent e)
            {

            }

            @Override
            public void keyPressed(KeyEvent e)
            {
                int keyCode = e.getKeyCode();
                if(keyCode == KeyEvent.VK_A)
                {
                   System.out.println("Liczba zwierząt: " + Animal.getNumberOfAnimals());
                }



                /*switch(keyCode)
                {
                    case KeyEvent.VK_UP:
                        System.out.println("UP");
                        break;
                    case KeyEvent.VK_DOWN:
                        System.out.println("DOWN");
                        break;
                    case KeyEvent.VK_LEFT:
                        System.out.println("LEFT");
                        break;
                    case KeyEvent.VK_RIGHT:
                        System.out.println("RIGHT");
                        break;
                }*/

                for(int i = 0; i < 20; i++)
                    for(int j = 0; j < 20; j++)
                    {
                        Entity entity = world.map[i][j].getEntity();
                        if(entity != null)
                            entities.add(entity);
                    }

                Entity entity = null;
                while(!entities.isEmpty())
                {
                    entity = entities.poll();
                    if(entity.checkIfAlive())
                        entity.Update();
                }
            }

            @Override
            public void keyReleased(KeyEvent e)
            {

            }
        });
    }

    private void PlaceEntities()
    {
        char[] types = {'W', 'S'};
        int freeSpace = world.worldHeight * world.worldWidth;
        int x = 0;
        int y = 0;
        int howMany = freeSpace / 3;
        int type = 0;

        Random rnd = new Random();
        JPanel gamePanel = WindowManager.GetInstance().GetGamePanel();
        for(int i = 0; i < howMany; i++)
        {
            x = rnd.nextInt(world.worldWidth);
            y = rnd.nextInt(world.worldHeight);
            type = rnd.nextInt(2);

            if(world.map[y][x].getEntity() == null)
                world.map[y][x].setEntity(Entity.getEntityFromSymbol(this.world, new Point(y, x), types[type]));
        }
    }

    public World getWorld()
    {
        return world;
    }
}

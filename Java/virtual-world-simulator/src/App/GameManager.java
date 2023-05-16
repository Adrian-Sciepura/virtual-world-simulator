package App;

import Common.Point;
import Entities.Animals.Animal;
import Entities.Animals.Human;
import Entities.Entity;
import Entities.Plants.Plant;
import GUI.MapElement;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.*;
import java.util.PriorityQueue;
import java.util.Random;
import java.util.Scanner;

public class GameManager
{
    private static volatile GameManager instance;
    private JLabel menuText;
    private JButton abilityButton;
    private JTextArea logArea;
    private World world;
    private PriorityQueue<Entity> entities;
    private Human player;
    private int round;
    private int abilityDuration;
    private int abiliyCooldown;

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
        round = 0;
        abilityDuration = 0;
        abiliyCooldown = 5;
        entities = new PriorityQueue<Entity>(Entity::compareTo);
    }

    private void Setup(int width, int height)
    {
        world.setWorldSize(width, height);
        PlaceEntities();
        WindowManager window = WindowManager.GetInstance();
        Common.Point fixedSize = window.getFixedSize(1200, 800);
        window.ToggleWindowVisibility();
        window.setWindowSize(fixedSize.x, fixedSize.y);
        window.setWindowTitle("Adrian Ściepura 193350");

        SetupGame();
        SetupMenu();

        JFrame frame = window.getWindow();
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

                if(!world.CheckIfGameOver() && player.setNewPosition(keyCode))
                {
                    round++;
                    if(player.CheckIfAbilityTurnedOn())
                    {
                        abilityDuration--;
                        if(abilityDuration == 0)
                            player.ToggleAbility(false);
                    }
                    else
                    {
                        if(abiliyCooldown > 0)
                            abiliyCooldown--;
                    }

                    for(int i = 0; i < world.worldHeight; i++)
                        for(int j = 0; j < world.worldWidth; j++)
                        {
                            Entity entity = world.map[i][j].getEntity();
                            if(entity != null)
                                entities.add(entity);
                        }

                    world.ClearLogs();
                    Entity entity = null;
                    while(!entities.isEmpty())
                    {
                        entity = entities.poll();
                        if(entity.checkIfAlive())
                            entity.Update();
                    }
                }

                UpdateMenu();
            }

            @Override
            public void keyReleased(KeyEvent e)
            {

            }
        });
    }

    private void SetupMenu()
    {
        WindowManager window = WindowManager.GetInstance();
        JPanel menuPanel = window.getMenuPanel();
        JPanel gamePanel = window.getGamePanel();
        menuText = new JLabel();
        Common.Point fixedSize = window.getFixedSize(menuText.getFont().getSize()*2, 0);
        menuText.setFont(new Font(menuText.getFont().getName(), Font.PLAIN, fixedSize.x));
        menuText.setHorizontalAlignment(SwingConstants.CENTER);
        menuText.setHorizontalTextPosition(SwingConstants.CENTER);
        menuText.setAlignmentX(Component.CENTER_ALIGNMENT);
        menuPanel.add(menuText);

        JButton changeAppearanceButton = new JButton("Change appearance");
        changeAppearanceButton.setFont(new Font(menuText.getFont().getName(), Font.PLAIN, fixedSize.x));
        changeAppearanceButton.setFocusable(false);
        changeAppearanceButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        changeAppearanceButton.addActionListener(e -> {
            MapElement.ChangeAppearance();
            gamePanel.repaint();
        });
        menuPanel.add(changeAppearanceButton);

        abilityButton = new JButton("Activate ability");
        abilityButton.setFont(new Font(menuText.getFont().getName(), Font.PLAIN, fixedSize.x));
        abilityButton.setFocusable(false);
        abilityButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        abilityButton.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                player.ToggleAbility(true);
                abilityButton.setEnabled(false);
                abilityDuration = 5;
                abiliyCooldown = 5;
                UpdateMenu();
                System.out.println("Activated ability");
            }
        });
        menuPanel.add(abilityButton);

        JButton saveButton = new JButton("Save game");
        saveButton.setFont(new Font(menuText.getFont().getName(), Font.PLAIN, fixedSize.x));
        saveButton.setFocusable(false);
        saveButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        saveButton.addActionListener(e -> {
            SaveGame();
        });
        menuPanel.add(saveButton);

        JButton loadButton = new JButton("Load game");
        loadButton.setFont(new Font(menuText.getFont().getName(), Font.PLAIN, fixedSize.x));
        loadButton.setFocusable(false);
        loadButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        loadButton.addActionListener(e -> {
            LoadGame();
        });
        menuPanel.add(loadButton);

        JButton newGameButton = new JButton("New game");
        newGameButton.setFont(new Font(menuText.getFont().getName(), Font.PLAIN, fixedSize.x));
        newGameButton.setFocusable(false);
        newGameButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        newGameButton.addActionListener(e -> {
            NewGame();
        });
        menuPanel.add(newGameButton);

        JPanel panel = new JPanel();
        panel.setBackground(menuPanel.getBackground());
        logArea = new JTextArea(20, 25);
        logArea.setEditable(false);
        logArea.setFocusable(false);
        JScrollPane scrollPane = new JScrollPane(logArea, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        panel.add(scrollPane);
        panel.setPreferredSize(new Dimension(100, 100));
        menuPanel.add(panel);

        UpdateMenu();
        menuPanel.repaint();
    }

    private void SetupGame()
    {
        WindowManager window = WindowManager.GetInstance();
        JPanel gamePanel = window.getGamePanel();

        if(gamePanel.getComponents().length > 0)
            gamePanel.removeAll();

        gamePanel.setLayout(new GridLayout(world.worldHeight, world.worldWidth));
        for(int i = 0; i < world.worldHeight; i++)
            for(int j = 0; j < world.worldWidth; j++)
                gamePanel.add(world.map[i][j]);
    }

    public void Start()
    {
        Setup(20, 20);
    }

    private void PlaceEntities()
    {
        char[] types = { 'A', 'F', 'T', 'W', 'S', 'G', 'D', 'U', 'N', 'P'};
        int freeSpace = world.worldHeight * world.worldWidth;
        int x = 0;
        int y = 0;
        int howMany = freeSpace / 3;
        int type = 0;

        player = new Human(world, new Point(1, 1));
        world.map[1][1].setEntity(player);

        Random rnd = new Random();
        for(int i = 0; i < howMany; i++)
        {
            x = rnd.nextInt(world.worldWidth);
            y = rnd.nextInt(world.worldHeight);
            type = rnd.nextInt(10);

            if(world.map[y][x].getEntity() == null)
                world.map[y][x].setEntity(Entity.getEntityFromSymbol(this.world, new Point(y, x), types[type]));
        }
    }

    private void UpdateMenu()
    {
        menuText.setText(
                        "<html><br><p style=\"text-align: center;\"><b>Adrian Ściepura</b>" +
                        "<br>Number of Animals: <b>" + Animal.getNumberOfAnimals() +
                        "</b><br>Number of Plants: <b>" + Plant.getNumberOfPlants() +
                        "</b><br>Round: <b>" + round +
                        "</b><br>Ability Cooldown: <b>" + abiliyCooldown + "</b></p><br></html>");

        if(abiliyCooldown == 0)
            abilityButton.setEnabled(true);
        else
            abilityButton.setEnabled(false);

        logArea.setText(world.getLogs());
    }

    private void SaveGame()
    {
        try
        {
            FileWriter saveFile = new FileWriter("save.txt");
            saveFile.write(world.worldHeight + " " + world.worldWidth + " " + round + " " + world.CheckIfGameOver() + "\n");
            saveFile.write(abilityDuration + " " + abiliyCooldown + "\n");
            for(int i = 0; i < world.worldHeight; i++)
            {
                for(int j = 0; j < world.worldWidth; j++)
                {
                    Entity entity = world.map[i][j].getEntity();
                    if(entity != null)
                        saveFile.write(entity.getSymbol() + " " + entity.getPosition().x + " " + entity.getPosition().y + " " + entity.getLifespan() + " " + entity.getStrength() + "\n");
                }
            }
            saveFile.close();

        } catch (IOException e)
        {
            System.out.println("An error has occured");
            e.printStackTrace();
        }

    }

    private void LoadGame()
    {
        try
        {
            FileReader saveFile = new FileReader("save.txt");
            Scanner sc = new Scanner(saveFile);

            int height = sc.nextInt();
            int width = sc.nextInt();
            round = sc.nextInt();
            boolean gameOver = sc.nextBoolean();
            abilityDuration = sc.nextInt();
            abiliyCooldown = sc.nextInt();

            world.Reset();
            world.ClearLogs();
            world.setWorldSize(width, height);
            if(gameOver)
                world.EndGame();
            SetupGame();
            while(sc.hasNextLine())
            {
                char symbol = sc.next().charAt(0);
                int x = sc.nextInt();
                int y = sc.nextInt();
                int lifespan = sc.nextInt();
                int strength = sc.nextInt();
                sc.nextLine();

                Entity entity = Entity.getEntityFromSymbol(world, new Point(x, y), symbol);
                entity.setLifespan(lifespan);
                entity.setStrength(strength);
                world.map[x][y].setEntity(entity);

                if(symbol == 'H')
                    player = (Human) entity;
            }

            saveFile.close();
            sc.close();

            UpdateMenu();
        }
        catch (FileNotFoundException e)
        {
            System.out.println("Save file not found");
        }
        catch (IOException e)
        {
            throw new RuntimeException(e);
        }

    }

    private void NewGame()
    {
        world.Reset();
        round = 0;
        abiliyCooldown = 5;
        abilityDuration = 0;
        PlaceEntities();
        world.ClearLogs();
        UpdateMenu();
    }

    public World getWorld()
    {
        return world;
    }
}

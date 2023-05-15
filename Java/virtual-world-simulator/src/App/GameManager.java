package App;

import Common.Point;
import Entities.Animals.Animal;
import Entities.Animals.Human;
import Entities.Entity;
import Entities.Plants.Plant;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.util.PriorityQueue;
import java.util.Random;

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

    public void Start()
    {
        PlaceEntities();
        WindowManager window = WindowManager.GetInstance();
        Common.Point fixedSize = window.getFixedSize(1200, 800);
        window.ToggleWindowVisibility();
        window.SetWindowSize(fixedSize.x, fixedSize.y);
        window.SetWindowTitle("Adrian Ściepura 193350");

        JPanel gamePanel = window.GetGamePanel();
        for(int i = 0; i < 20; i++)
            for(int j = 0; j < 20; j++)
                gamePanel.add(world.map[i][j]);


        JPanel menuPanel = window.GetMenuPanel();
        menuText = new JLabel();
        fixedSize = window.getFixedSize(menuText.getFont().getSize()*2, 0);
        menuText.setFont(new Font(menuText.getFont().getName(), Font.PLAIN, fixedSize.x));
        menuText.setHorizontalAlignment(SwingConstants.CENTER);
        menuText.setHorizontalTextPosition(SwingConstants.CENTER);
        menuText.setAlignmentX(Component.CENTER_ALIGNMENT);
        menuPanel.add(menuText);

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
        menuPanel.add(saveButton);

        JButton loadButton = new JButton("Load game");
        loadButton.setFont(new Font(menuText.getFont().getName(), Font.PLAIN, fixedSize.x));
        loadButton.setFocusable(false);
        loadButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        menuPanel.add(loadButton);

        JButton newGameButton = new JButton("New game");
        newGameButton.setFont(new Font(menuText.getFont().getName(), Font.PLAIN, fixedSize.x));
        newGameButton.setFocusable(false);
        newGameButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        menuPanel.add(newGameButton);

        JPanel panel = new JPanel();
        panel.setBackground(menuPanel.getBackground());
        logArea = new JTextArea(20, 25);
        logArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(logArea, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        panel.add(scrollPane);
        panel.setPreferredSize(new Dimension(100, 100));
        menuPanel.add(panel);

        UpdateMenu();
        menuPanel.repaint();

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

                    for(int i = 0; i < 20; i++)
                        for(int j = 0; j < 20; j++)
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
        JPanel gamePanel = WindowManager.GetInstance().GetGamePanel();
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

    public World getWorld()
    {
        return world;
    }
}

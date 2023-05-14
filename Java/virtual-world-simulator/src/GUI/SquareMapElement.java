package GUI;

import App.GameManager;
import Entities.Entity;

import javax.naming.ldap.Control;
import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.HashMap;
import java.util.Map;

public class SquareMapElement extends JComponent
{
    private Entity entity;
    private Color borderColor;
    private int borderWidth;

    private static Map<Character, String> types = new HashMap<Character, String>(){
        {
            put('H', "Human");
            put('A', "Antelope");
            put('F', "Fox");
            put('S', "Sheep");
            put('T', "Turtle");
            put('W', "Wolf");
            put('G', "Grass");
            put('D', "Dandelion");
            put('N', "Nightshade");
            put('U', "Guarana");
            put('P', "Pine Hogweed");
        }
    };

    public SquareMapElement()
    {
        super();
        borderColor = Color.WHITE;
        borderWidth = 2;
        entity = null;

        addMouseListener(new MouseListener()
        {
            @Override
            public void mouseClicked(MouseEvent e)
            {
                if(entity != null)
                {
                    Common.Point position = entity.getPosition();
                    System.out.println("Clicked on: " + position.x + " " + position.y);
                }

                ShowContextMenu();
            }

            @Override
            public void mousePressed(MouseEvent e)
            {

            }

            @Override
            public void mouseReleased(MouseEvent e)
            {

            }

            @Override
            public void mouseEntered(MouseEvent e)
            {
                borderColor = Color.BLUE;
                borderWidth = 6;
                repaint();
            }

            @Override
            public void mouseExited(MouseEvent e)
            {
                borderColor = Color.WHITE;
                borderWidth = 2;
                repaint();
            }
        });
    }

    @Override
    public void paintComponent(Graphics g)
    {
        super.paintComponent(g);

        Graphics2D g2d = (Graphics2D) g;
        g2d.setColor(borderColor);
        Stroke oldStroke = g2d.getStroke();
        Stroke newStroke = new BasicStroke(borderWidth);
        g2d.setStroke(newStroke);
        g2d.drawRect(0, 0, getWidth() - 1, getHeight() - 1);
        g2d.setStroke(oldStroke);

         if(entity != null)
         {
             int width = getWidth();
             int height = getHeight();
             g2d.drawImage(entity.getIcon().getImage(), 5, 5, width-10, height-10, this);
         }
    }

    public void setEntity(Entity entity)
    {
        this.entity = entity;
        repaint();
    }

    public Entity getEntity()
    {
        return this.entity;
    }

    public void ShowContextMenu()
    {
        MapElementContextMenu contextMenu = new MapElementContextMenu();
        contextMenu.setLayout(new BoxLayout(contextMenu, BoxLayout.Y_AXIS));
        if(entity != null)
        {
            Image originalImage = entity.getIcon().getImage();
            Image scaledImage = originalImage.getScaledInstance(90, 90, Image.SCALE_SMOOTH);
            ImageIcon scaledIcon = new ImageIcon(scaledImage);

            JLabel animalImage = new JLabel(scaledIcon);
            animalImage.setPreferredSize(new Dimension(100, 100));
            contextMenu.add(animalImage);

            JLabel animalInfo = new JLabel(
                    "<html><br>Entity: " + entity.getClass().getSimpleName() +
                    "<br>Strength: " + entity.getStrength() +
                    "<br>Lifespan: " + entity.getLifespan() +
                    "<br>Priority: " + entity.getPriority() + "</html>");
            animalInfo.setHorizontalAlignment(JLabel.CENTER);
            contextMenu.add(animalInfo);
        }
        else
        {
            for(Map.Entry<Character, String> entry : types.entrySet())
            {
                JMenuItem menuItem = new JMenuItem("Add: " + entry.getValue());
                Container parent = getParent();
                menuItem.addActionListener(e -> {
                    this.setEntity(Entity.getEntityFromSymbol(GameManager.GetInstance().getWorld(), new Common.Point(20 - (parent.getHeight() - getY())/getHeight(), 20 - (parent.getWidth() - getX())/getWidth()), entry.getKey()));
                    repaint();
                });
                contextMenu.add(menuItem);
            }

        }
        contextMenu.show(this, getWidth(), 0);
    }
}

package GUI;

import App.GameManager;
import App.WindowManager;
import Entities.Entity;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.Map;

public class SquareMapElement extends JComponent
{
    private Entity entity;
    private Color borderColor;
    private int borderWidth;

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
        WindowManager windowManager = WindowManager.GetInstance();
        contextMenu.setLayout(new BoxLayout(contextMenu, BoxLayout.Y_AXIS));
        if(entity != null)
        {
            Common.Point fixedSize = windowManager.getFixedSize(90, 90);
            Image originalImage = entity.getIcon().getImage();
            Image scaledImage = originalImage.getScaledInstance(fixedSize.x, fixedSize.y, Image.SCALE_SMOOTH);
            ImageIcon scaledIcon = new ImageIcon(scaledImage);

            JLabel animalImage = new JLabel(scaledIcon);
            fixedSize = windowManager.getFixedSize(100, 100);
            animalImage.setPreferredSize(new Dimension(fixedSize.x, fixedSize.y));
            contextMenu.add(animalImage);

            JLabel animalInfo = new JLabel(
                    "<html><br>Entity: " + entity.getClass().getSimpleName() +
                    "<br>Strength: " + entity.getStrength() +
                    "<br>Lifespan: " + entity.getLifespan() +
                    "<br>Priority: " + entity.getPriority() + "</html>");
            fixedSize = windowManager.getFixedSize(animalInfo.getFont().getSize(), 0);
            animalInfo.setFont(new Font(animalInfo.getFont().getName(), Font.PLAIN, fixedSize.x));
            animalInfo.setHorizontalAlignment(JLabel.CENTER);
            contextMenu.add(animalInfo);
        }
        else
        {
            Common.Point fixedSize = null;
            for(Map.Entry<Character, String> entry : Entity.types.entrySet())
            {
                JMenuItem menuItem = new JMenuItem("Add: " + entry.getValue());
                fixedSize = windowManager.getFixedSize(menuItem.getFont().getSize(), 0);
                menuItem.setFont(new Font(menuItem.getFont().getName(), Font.PLAIN, fixedSize.x));
                menuItem.addActionListener(e -> {
                    this.setEntity(Entity.getEntityFromSymbol(GameManager.GetInstance().getWorld(), getPosition(), entry.getKey()));
                    repaint();
                });
                contextMenu.add(menuItem);
            }

        }
        contextMenu.show(this, getWidth(), 0);
    }

    public Common.Point getPosition()
    {
        Container parent = getParent();
        GridLayout layout = (GridLayout) parent.getLayout();
        return new Common.Point(layout.getRows() - (parent.getHeight() - getY())/getHeight(), layout.getColumns() - (parent.getWidth() - getX())/getWidth());
    }
}

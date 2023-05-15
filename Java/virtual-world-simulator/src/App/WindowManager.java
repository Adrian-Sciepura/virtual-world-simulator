package App;

import javax.swing.*;
import java.awt.*;

public final class WindowManager
{
    private static volatile WindowManager instance;
    private JFrame window;
    private JPanel gamePanel;
    private JPanel menuPanel;
    private boolean visibility;
    private final float widthMultiply;
    private final float heightMultiply;

    public static WindowManager GetInstance()
    {
        WindowManager result = instance;
        if(result != null)
        {
            return result;
        }
        synchronized (WindowManager.class)
        {
            if(instance == null)
            {
                instance = new WindowManager();
            }
            return instance;
        }
    }

    private WindowManager()
    {
        GraphicsDevice gd = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice();
        int width = gd.getDisplayMode().getWidth();
        int height = gd.getDisplayMode().getHeight();

        widthMultiply = (float) width / 1920;
        heightMultiply = (float) height / 1080;

        window = new JFrame();
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setLayout(new GridBagLayout());

        gamePanel = new JPanel();
        menuPanel = new JPanel();

        gamePanel.setBackground(new Color(124, 202, 146));
        gamePanel.setLayout(new GridLayout(20, 20));
        menuPanel.setBackground(new Color(240, 237, 212));
        menuPanel.setLayout(new BoxLayout(menuPanel, BoxLayout.Y_AXIS));

        GridBagConstraints c = new GridBagConstraints();
        c.gridx = 0;
        c.gridy = 0;
        c.weightx = 5.0;
        c.weighty = 1.0;
        c.fill = GridBagConstraints.BOTH;
        window.add(gamePanel, c);

        c.gridx = 1;
        c.weightx = 1.0;
        window.add(menuPanel, c);
    }

    public void ToggleWindowVisibility()
    {
        visibility = !visibility;
        window.setVisible(visibility);
    }

    public void SetWindowSize(int width, int height)
    {
        window.setSize(width, height);
    }

    public void SetWindowTitle(String title)
    {
        window.setTitle(title);
    }

    public JPanel GetGamePanel()
    {
        return this.gamePanel;
    }

    public JPanel GetMenuPanel()
    {
        return this.menuPanel;
    }

    public JFrame GetWindow()
    {
        return this.window;
    }

    public Common.Point getFixedSize(int width, int height)
    {
        return new Common.Point((int)(width * widthMultiply), (int)(height * heightMultiply));
    }
}

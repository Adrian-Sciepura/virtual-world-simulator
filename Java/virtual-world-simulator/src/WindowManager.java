import javax.swing.*;
import java.awt.*;

public final class WindowManager {
    private static volatile WindowManager instance;

    private JFrame window;
    private JPanel gamePanel;
    private JPanel menuPanel;
    private boolean visibility;

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
        window = new JFrame();
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setLayout(new BorderLayout());

        gamePanel = new JPanel();
        menuPanel = new JPanel();

        window.add(gamePanel, BorderLayout.CENTER);
        window.add(menuPanel, BorderLayout.EAST);
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
}

import javax.swing.*;
import java.awt.*;

public class GameManager
{
    private static volatile GameManager instance;
    private JLabel map[][];
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
        map = new JLabel[20][20];
    }

    private void SetupWindow()
    {
        WindowManager window = WindowManager.GetInstance();
        window.ToggleWindowVisibility();
        window.SetWindowSize(1280, 720);
        window.SetWindowTitle("Adrian Ściepura 193350");

        JPanel gamePanel = window.GetGamePanel();

        for(int i = 0; i < 20; i++)
        {
            for(int j = 0; j < 20; j++)
            {
                ImageIcon image = new ImageIcon("assets/fox.png");
                JLabel item = new JLabel();
                //item.setText(Integer.toString(i) + " " + Integer.toString(j));
                item.setIcon(image);
                item.setPreferredSize(new Dimension(10, 10));
                map[i][j] = item;
                gamePanel.add(item);
            }
        }
    }

    public void Start()
    {
        SetupWindow();
        while(true)
        {

        }


    }
}

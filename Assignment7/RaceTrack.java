
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class RaceTrack extends JPanel {

  private JFrame frame;
  private JButton startButton;
  private JButton pauseButton;
  private JButton resetButton;

  public static void main(String argv[]) {
    frame = new JFrame("Assignment 7");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    RaceTrack track = new RaceTrack();
    frame.add(track);

    startButton = new JButton("Start");
    startButton.addActionListener(e -> {
      System.out.println("Start");
    });
    frame.getContentPane().add(startButton);

    pauseButton = new JButton("Pause");
    pauseButton.addActionListener(e -> {
      System.out.println("Pause");
    });
    frame.getContentPane().add(pauseButton);

    resetButton = new JButton("Reset");
    resetButton.addActionListener(e -> {
      System.out.println("Reset");
    });
    frame.getContentPane().add(resetButton);

    frame.setSize(500, 200);
    frame.setVisible(true);

  }

  @Override
  public void paintComponent(Graphics g) {
    super.paintComponent(g);



  }

}

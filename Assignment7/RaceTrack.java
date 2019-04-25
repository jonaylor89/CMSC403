
import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import javax.swing.*;
import javax.imageio.*;

import java.io.*;

public class RaceTrack extends JPanel {

  private static JFrame frame;
  private static JButton startButton;
  private static JButton pauseButton;
  private static JButton resetButton;
  private static BufferedImage car;

  public static void main(String argv[]) {
    frame = new JFrame("Race Track");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setResizable(false);

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

    frame.setLayout(new FlowLayout());

    try {
      car = ImageIO.read(new File("sportive-car.png"));
    } catch (IOException ex) {
      System.out.println("IO error");
      System.exit(1);
    }

    frame.setSize(500, 200);
    frame.setVisible(true);

  }

  @Override
  public void paintComponent(Graphics g) {
    super.paintComponent(g);

    // Draw 3 rectangles for the "track"
    // Draw the images at the beginning of the track
    g.drawImage(car, 0, 0, this);
    g.drawImage(car, 0, 50, this);
    g.drawImage(car, 0, 100, this);

    g.drawRect(10, 10, 10, 10);
    g.drawRect(20, 20, 20, 20);
    g.drawRect(30, 30, 30, 30);

  }

}

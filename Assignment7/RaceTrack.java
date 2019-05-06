
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

  private static boolean go;
  private static Racer[] racers;

  public static void main(String argv[]) {
    frame = new JFrame("Race Track");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setResizable(false);

    racers[0] = new Racer();
    racers[1] = new Racer();
    racers[2] = new Racer();
    runRacers();

    RaceTrack track = new RaceTrack();
    frame.add(track);

    startButton = new JButton("Start");
    startButton.addActionListener(e -> {
      System.out.println("Start");
      startRacers();
    });
    frame.getContentPane().add(startButton);

    pauseButton = new JButton("Pause");
    pauseButton.addActionListener(e -> {
      System.out.println("Pause");
      pauseRacers();
    });
    frame.getContentPane().add(pauseButton);

    resetButton = new JButton("Reset");
    resetButton.addActionListener(e -> {
      System.out.println("Reset");
      pauseRacers();
      resetDistances();
    });

    frame.getContentPane().add(resetButton);

    frame.setLayout(new FlowLayout());

    try {
      car = ImageIO.read(new File("sportive-car.png"));
      JLabel label = new JLabel(new ImageIcon(car));
      frame.add(label);
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

    // Draw the images at the beginning of the track
    g.drawImage(car, 0, 0, this);
    g.drawImage(car, 0, 50, this);
    g.drawImage(car, 0, 100, this);

    // Draw the 3 rectangle for the "tracks"
    g.drawRect(230, 80, 10, 10);
    g.drawRect(20, 20, 20, 20);
    g.drawRect(30, 30, 30, 30);

    g.setColor(Color.RED);
    g.fillRect(10, 10, 100, 100);

  }

  public static void resetDistances() {
    for (Racer r : racers) {
      r.distance = 0; 
    }
  }

  public static void runRacers() {
    for (Racer r : racers) {
      r.start();
    }
  }

  public static void startRacers() {
    for (Racer r : racers) {
      r.go = true; 
    }
  }

  public static void pauseRacers() {
    for (Racer r : racers) {
      r.go = false; 
    }
  }
}

class Racer extends Thread {

  int distance;
  boolean go;

  public Racer() {
    distance = 0; 
    go = false;
  }

  public void run() {
    if (go) {
    
    }
  }
}


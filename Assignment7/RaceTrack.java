
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

    /**
     * Initalize window settings
     */
    frame = new JFrame("Race Track");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setResizable(false);


    /**
     * Create the track to place objects
     */
    RaceTrack track = new RaceTrack();
    frame.setContentPane(track);

    /**
     * Add buttons to the screen for starting and stopping the race
     */
    JPanel panel = new JPanel();
    panel.setLayout(new FlowLayout());

    startButton = new JButton("Start");
    startButton.addActionListener(e -> {
      startRacers();
    });
    panel.add(startButton);

    pauseButton = new JButton("Pause");
    pauseButton.addActionListener(e -> {
      pauseRacers();
    });
    panel.add(pauseButton);

    resetButton = new JButton("Reset");
    resetButton.addActionListener(e -> {
      pauseRacers();
      resetDistances();
    });

    panel.add(resetButton);

    try {
      car = ImageIO.read(new File("sportive-car.png"));
    } catch (IOException ex) {
      System.out.println("IO error");
      System.exit(1);
    }

    frame.add(panel);

    /**
     * Create racers for the track
     */
    racers = new Racer[3];

    racers[0] = new Racer();
    racers[1] = new Racer();
    racers[2] = new Racer();

    /**
     * Start racer threads to wait for the start
     */
    runRacers();

    /**
     * Size and show the window
     */
    frame.setSize(500, 200);
    frame.setVisible(true);

  }

  @Override
  public void paintComponent(Graphics g) {
    super.paintComponent(g);

    // Draw the 3 rectangle for the "tracks"
    g.setColor(Color.GRAY);
    g.fillRect(25, 55, 400, 15);
    g.fillRect(25, 95, 400, 15);
    g.fillRect(25, 135, 400, 15);

    // Draw the images at the beginning of the track
    g.drawImage(car, racers[0].distance + 25, 50, this);
    g.drawImage(car, racers[1].distance + 25, 90, this);
    g.drawImage(car, racers[2].distance + 25, 130, this);

  }

  public static void resetDistances() {
    for (Racer r : racers) {
      System.out.println("Reset " + r.go);
      r.distance = 0; 
      r.go = false;
    }
  }

  public static void runRacers() {
    for (Racer r : racers) {
      r.start();
    }
  }

  public static void startRacers() {
    for (Racer r : racers) {
      System.out.println("Start " + r.go);
      r.go = true; 
    }
  }

  public static void pauseRacers() {
    for (Racer r : racers) {
      System.out.println("Pause " + r.go);
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

  @Override
  public void run() {
    while (true) {
      if (go) {

        System.out.println("UMMMMMMM");

        if (distance < 100) {
          System.out.println("Updating distance " + distance);
          distance += 5;
        }
        // Check to make sure I'm not at the max
        // int deltaX = rand.nextInt(11);
    
        try {
          Thread.sleep(500);
        } catch (InterruptedException e) {
          return;
        }
      }
    }
  }
}


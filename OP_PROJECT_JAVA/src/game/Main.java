package game;

import javax.swing.*;

public class Main {
    private static final int WINDOW_SIZE_WIDTH = 40*20;
    private static final int WINDOW_SIZE_HEIGHT = 35*20;
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("Game");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setResizable(false);

            WorldPanel worldPanel = new WorldPanel(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);
            frame.add(worldPanel);

            frame.pack();
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);

        });
    }
}

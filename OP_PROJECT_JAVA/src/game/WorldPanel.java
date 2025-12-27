package game;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.Serial;

public class WorldPanel extends JPanel {
    @Serial
    private static final long serialVersionUID = 1L;
    private static final int CELL_SIZE = 40;
    private static final int WORLD_SIZE_WIDTH = 20;
    private static final int WORLD_SIZE_HEIGHT = 11;
    private static final int INFO_HEIGHT = 176;
    private static final int BUTTONS_LEVEL = 470;
    private static final int BUTTON_HEIGHT = 40;
    private static final int BUTTON_WIDTH = 100;
    private final World world;
    private final JTextArea infoTextArea;

    public WorldPanel(int width, int height) {
        world = new World(WORLD_SIZE_WIDTH, WORLD_SIZE_HEIGHT, CELL_SIZE, this);

        setPreferredSize(new Dimension(width, height));
        setLayout(null);

        infoTextArea = new JTextArea();
        infoTextArea.setEditable(false);
        infoTextArea.setLineWrap(true);
        infoTextArea.setWrapStyleWord(true);

        JScrollPane scrollPane = new JScrollPane(infoTextArea);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        scrollPane.setBounds(0, height - INFO_HEIGHT, width, INFO_HEIGHT);
        add(scrollPane); // Add the scroll pane to the panel

        // Create the "Next Turn" button
        JButton makeTurnButton = new JButton("Next Turn");
        makeTurnButton.setBounds(0, BUTTONS_LEVEL, BUTTON_WIDTH, BUTTON_HEIGHT);
        add(makeTurnButton);

        // Create the "Save Game" button
        JButton saveButton = new JButton("Save Game");
        saveButton.setBounds(BUTTON_WIDTH + 10, BUTTONS_LEVEL, BUTTON_WIDTH, BUTTON_HEIGHT);
        add(saveButton);

        // Create the "Load Game" button
        JButton loadButton = new JButton("Load Game");
        loadButton.setBounds(BUTTON_WIDTH * 2 + 20, BUTTONS_LEVEL, BUTTON_WIDTH, BUTTON_HEIGHT);
        add(loadButton);

        makeTurnButton.addActionListener(e -> {
            world.makeTurn();
            if (!world.isHumanAlive()) {
                endScreen();
            } else {
                repaint();
                requestFocusInWindow();
            }
        });

        saveButton.addActionListener(e -> {
            world.saveToFile();
            addTextToInfoPanel("Game state saved.");
            requestFocusInWindow();
        });

        loadButton.addActionListener(e -> {
            world.loadFromFile();
            addTextToInfoPanel("Game state loaded.");
            repaint();
            requestFocusInWindow();
        });

        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                int mouseX = e.getX() / CELL_SIZE;
                int mouseY = e.getY() / CELL_SIZE;
                if (world.isPositionWithinBounds(new Position(mouseY, mouseX))) {
                    Organism existingOrganism = world.getOrganismAtPosition(new Position(mouseY, mouseX));
                    if (existingOrganism == null) {
                        String[] options = {"Wolf", "Sheep", "Fox", "Turtle", "Antelope", "Grass", "Sow Thistle", "Guarana", "Belladonna", "Sosnowsky Hogweed"};
                        String chosenType = (String) JOptionPane.showInputDialog(
                                null,
                                "Choose the type of organism to add:",
                                "Add Organism",
                                JOptionPane.PLAIN_MESSAGE,
                                null,
                                options,
                                options[0]);

                        if (chosenType != null) {
                            // Add the new organism at the clicked position
                            world.bornAnimal(chosenType, new Position(mouseY, mouseX));
                            repaint();
                        }
                    }
                }
            }
        });

        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                handleInput(e);
            }
        });

        setFocusable(true);
        requestFocusInWindow();

    }

    public void handleInput(KeyEvent e) {
        char ch = e.getKeyChar();
        switch (ch) {
            case 'w':
            case 's':
            case 'a':
            case 'd':
                world.setNextMove(ch);
                break;
            case 'p': // Special power of human
                world.activateSpecialPower();
                break;
        }
    }

    public void disableInput() {
        // Remove mouse click listener
        for (MouseListener listener : this.getMouseListeners()) {
            this.removeMouseListener(listener);
        }

        // Remove key listener
        for (KeyListener listener : this.getKeyListeners()) {
            this.removeKeyListener(listener);
        }

        // Remove all buttons
        Component[] components = this.getComponents();
        for (Component component : components) {
            if (component instanceof JButton) {
                this.remove(component);
            }
        }

        // Remove the scroll pane
        for (Component component : components) {
            if (component instanceof JScrollPane) {
                this.remove(component);
            }
        }
    }

    private void endScreen() {
        clearScreen();
        drawText("YOU LOST", getWidth() / 2 - 50, getHeight() / 2);
        disableInput();
    }

    public void clearScreen() {
        Graphics2D g2d = (Graphics2D) getGraphics();
        g2d.clearRect(0, 0, getWidth(), getHeight());
        g2d.dispose();
    }

    public void drawText(String text, int x, int y) {
        Graphics2D g2d = (Graphics2D) getGraphics();
        g2d.setColor(Color.RED);
        g2d.setFont(new Font("Arial", Font.BOLD, 24));
        g2d.drawString(text, x, y);
        g2d.dispose();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g.create();
        world.draw(g2d);
        g2d.dispose();
    }

    public void addTextToInfoPanel(String text) {
        infoTextArea.append(text + "\n");
        infoTextArea.setCaretPosition(infoTextArea.getDocument().getLength());
    }
}


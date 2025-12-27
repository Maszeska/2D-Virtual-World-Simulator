package game;

import game.Animals.*;
import game.Plants.*;


import java.util.List;
import java.util.Map;
import java.util.ArrayList;
import java.util.HashMap;
import javax.imageio.ImageIO;
import java.awt.*;
import java.io.File;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.ObjectInputStream;
import javax.swing.JOptionPane;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

public class World implements Serializable {
    private final int cellSize;
    private int width;
    private int height;
    private int cooldown = 0;
    private char nextMove = 'd';
    private final String saveFilename = "world_save";
    private List<List<Organism>> map;
    private List<Organism> organisms;
    private Map<OrganismType, Integer> organismCounts;
    private final WorldPanel worldPanel;

    public World(int width, int height, int cellSize, WorldPanel worldPanel) {
        this.cellSize = cellSize;
        this.width = width;
        this.height = height;
        this.worldPanel = worldPanel;
        map = new ArrayList<>();
        organisms = new ArrayList<>();
        initializeOrganismCounts();
        createWorld();
    }

    private void createWorld() {
        for (int y = 0; y < height; y++) {
            map.add(new ArrayList<>());
            for (int x = 0; x < width; x++) {
                map.get(y).add(null);
            }
        }
        createOrganism();
    }

    private void initializeOrganismCounts() {
        organismCounts = new HashMap<>();
        organismCounts.put(OrganismType.HUMAN, 1);
        organismCounts.put(OrganismType.WOLF, 2);
        organismCounts.put(OrganismType.SHEEP, 3);
        organismCounts.put(OrganismType.FOX, 2);
        organismCounts.put(OrganismType.TURTLE, 2);
        organismCounts.put(OrganismType.ANTELOPE, 2);
        organismCounts.put(OrganismType.GRASS, 3);
        organismCounts.put(OrganismType.SOW_THISTLE, 2);
        organismCounts.put(OrganismType.GUARANA, 2);
        organismCounts.put(OrganismType.BELLADONNA, 1);
        organismCounts.put(OrganismType.SOSNOWSKY_HOGWEED, 2);
    }


    private void createOrganism() {
        for (Map.Entry<OrganismType, Integer> entry : organismCounts.entrySet()) {
            OrganismType type = entry.getKey();
            int count = entry.getValue();
            for (int i = 0; i < count; ++i) {
                Position position;
                do {
                    position = new Position((int) (Math.random() * height), (int) (Math.random() * width));
                } while (isPositionEmpty(position));
                Organism newOrganism = null;
                switch (type) {
                    case HUMAN:
                        newOrganism = new Human(position, this);
                        break;
                    case WOLF:
                        newOrganism = new Wolf(position, this);
                        break;
                    case SHEEP:
                        newOrganism = new Sheep(position, this);
                        break;
                    case FOX:
                        newOrganism = new Fox(position, this);
                        break;
                    case TURTLE:
                        newOrganism = new Turtle(position, this);
                        break;
                    case ANTELOPE:
                        newOrganism = new Antelope(position, this);
                        break;
                    case GRASS:
                        newOrganism = new Grass(position, this);
                        break;
                    case SOW_THISTLE:
                        newOrganism = new SowThistle(position, this);
                        break;
                    case GUARANA:
                        newOrganism = new Guarana(position, this);
                        break;
                    case BELLADONNA:
                        newOrganism = new Belladonna(position, this);
                        break;
                    case SOSNOWSKY_HOGWEED:
                        newOrganism = new SosnowskyHogweed(position, this);
                        break;
                    default:
                        break;                }
                if (newOrganism != null) {
                    organisms.add(newOrganism);
                    addOrganism(position, newOrganism);
                }
            }
        }
    }

    private void addOrganism(Position position, Organism organism) {
        if (isPositionWithinBounds(position) && getOrganismAtPosition(position) == null) {
            map.get(position.getY()).set(position.getX(), organism);
        }
    }

    public void draw(Graphics2D g2d) {
        for (int y = 0; y < height; y++) {
            List<Organism> row = map.get(y);
            if (row != null) {
                for (int x = 0; x < width; x++) {
                    Organism organism = row.get(x);
                    if (organism != null) {
                        drawOrganism(g2d, organism, x * cellSize, y * cellSize);
                    }
                }
            }
        }
    }

    private void drawOrganism(Graphics2D g2d, Organism organism, int x, int y) {
        try {
            Image image = ImageIO.read(new File(getImagePath(organism))); // Load PNG image
            g2d.drawImage(image, x, y, cellSize, cellSize, null); // Draw the image
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private String getImagePath(Organism organism) {
        String basePath = "src/img/";
        String organismType = organism.getType();
        return basePath + organismType + ".png";  // Construct the file path
    }

    public void makeTurn() {
        worldPanel.addTextToInfoPanel("*** Next turn ***");
        for (int i = 0; i < organisms.size(); ++i) {
            Organism organism = organisms.get(i);
            if (organism != null) {
                organism.action(); // Call action for every Organism
            }
        }
        if (cooldown != 0) {
            --cooldown;
        }
    }

    public void bornAnimal(String Type, Position position) {
        Organism newOrganism = null;
        switch (Type) {
            case "Wolf":
                newOrganism = new Wolf(position, this);
                break;
            case "Sheep":
                newOrganism = new Sheep(position, this);
                break;
            case "Fox":
                newOrganism = new Fox(position, this);
                break;
            case "Turtle":
                newOrganism = new Turtle(position, this);
                break;
            case "Antelope":
                newOrganism = new Antelope(position, this);
                break;
            case "Grass":
                newOrganism = new Grass(position, this);
                break;
            case "Sow Thistle":
                newOrganism = new SowThistle(position, this);
                break;
            case "Guarana":
                newOrganism = new Guarana(position, this);
                break;
            case "Belladonna":
                newOrganism = new Belladonna(position, this);
                break;
            case "Sosnowsky Hogweed":
                newOrganism = new SosnowskyHogweed(position, this);
                break;
            default:
                break;
        }
        if (newOrganism != null) {
            organisms.add(newOrganism);
            addOrganismAtPosition(position, newOrganism);
            animalBornInfo(newOrganism);
        }
    }

    private void animalBornInfo(Organism organism) {
        String message = "New " + organism.getType() + " was born";
        worldPanel.addTextToInfoPanel(message);
    }

    public void removeOrganism(Organism organism) {
        for (int i = 0; i < organisms.size(); i++) {
            if (organisms.get(i) == organism) {
                organisms.remove(i);
                break;
            }
        }

        for (List<Organism> row : map) {
            for (int i = 0; i < row.size(); i++) {
                if (row.get(i) == organism) {
                    row.set(i, null);
                    break;
                }
            }
        }
    }

    public boolean isHumanAlive() {
        for (Organism organism : organisms) {
            if (organism instanceof Human) {
                return true; // Human is alive
            }
        }
        return false;
    }

    public void saveToFile() {
        try (
                FileOutputStream fout = new FileOutputStream(saveFilename);
                ObjectOutputStream oos = new ObjectOutputStream(fout)
        ) {
            oos.writeObject(this);
            JOptionPane.showMessageDialog(null, "Game saved successfully", "Success", JOptionPane.INFORMATION_MESSAGE);
        } catch (Exception ex) {
            ex.printStackTrace();
            JOptionPane.showMessageDialog(null, "Failed to save the game: " + ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    public void loadFromFile() {
        try (
                FileInputStream fin = new FileInputStream(saveFilename);
                ObjectInputStream ois = new ObjectInputStream(fin)
        ) {
            World loadedWorld = (World) ois.readObject();
            // Copy the state of the loaded World object to this instance
            this.width = loadedWorld.getWidth();
            this.height = loadedWorld.getHeight();
            this.cooldown = loadedWorld.getCooldown();
            this.map = loadedWorld.getMap();
            this.organisms = loadedWorld.getOrganisms();
            this.nextMove = loadedWorld.getNextMove();

            for (Organism organism : organisms) {
                if (organism instanceof Human human) {
                    human.setWorld(this);
                }
            }
            JOptionPane.showMessageDialog(null, "Game loaded successfully", "Success", JOptionPane.INFORMATION_MESSAGE);
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(null, "Failed to load the game", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    public int getCooldown() {
        return cooldown;
    }

    public char getNextMove() {
        return nextMove;
    }

    public void setNextMove(char move) {
        nextMove = move;
        printDirection();
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public List<List<Organism>> getMap() {
        return map;
    }

    public List<Organism> getOrganisms() {
        return organisms;
    }

    public Organism getOrganismAtPosition(Position position) {
        if (isPositionWithinBounds(position)) {
            return map.get(position.getY()).get(position.getX());
        } else {
            return null;
        }
    }

    public void removeOrganismAtPosition(Position position) {
        if (isPositionWithinBounds(position)) {
            map.get(position.getY()).set(position.getX(), null);
        }
    }

    public void addOrganismAtPosition(Position position, Organism organism) {
        if (isPositionWithinBounds(position)) {
            map.get(position.getY()).set(position.getX(), organism);
        }
    }

    public boolean isPositionWithinBounds(Position position) {
        int x = position.getX();
        int y = position.getY();
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    public void printDirection() {
        char dir = nextMove;
        switch (dir) {
            case 'w':
                worldPanel.addTextToInfoPanel("Human will move up");
                break;
            case 's':
                worldPanel.addTextToInfoPanel("Human will move down");
                break;
            case 'a':
                worldPanel.addTextToInfoPanel("Human will move left");
                break;
            case 'd':
                worldPanel.addTextToInfoPanel("Human will move right");
                break;
            default:
                break;
        }
    }

    public boolean isPositionEmpty(Position position) {
        return map.get(position.getY()).get(position.getX()) != null;
    }

    public void activateSpecialPower() {
        String info;
        if (cooldown == 0 ) {
            cooldown = 10;
            info = "Human special power activated";
        } else {
            info = "Not possible to activate special power for " + cooldown + " turns";
        }
        worldPanel.addTextToInfoPanel(info);
    }

    public void displayInformation(String info) {
        worldPanel.addTextToInfoPanel(info);
    }
}

package game.Animals;

import game.Animal;
import game.Position;
import game.World;

import java.util.Random;

public class Antelope extends Animal {
    private static final int ANTELOPE_STRENGTH = 4;
    private static final int ANTELOPE_INIT = 4;
    private static final String ANTELOPE_TYPE = "Antelope";


    public Antelope(Position position, World world) {
        super(ANTELOPE_TYPE, ANTELOPE_STRENGTH, ANTELOPE_INIT, position, world);
    }

    @Override
    protected boolean checkEscaped() {
        double escapeChance = new Random().nextDouble();
        // If the generated number is less than 0.5, Antelope escapes
        if (escapeChance < 0.5) {
            world.displayInformation("Antelope escaped from the fight!");
            return true;
        }
        return false;
    }

    @Override
    public void action() {
        // Generate a random direction for movement
        int direction = (int) (Math.random() * 4);
        Position newPosition = new Position(position.getY(), position.getX());

        switch (direction) {
            case 0: // Move up
                newPosition.setY(newPosition.getY() - 2);
                break;
            case 1: // Move down
                newPosition.setY(newPosition.getY() + 2);
                break;
            case 2: // Move left
                newPosition.setX(newPosition.getX() - 2);
                break;
            case 3: // Move right
                newPosition.setX(newPosition.getX() + 2);
                break;
            default:
                break;
        }

        if (world.isPositionWithinBounds(newPosition)) {
            if (world.getOrganismAtPosition(newPosition) != null) {
                collision(world.getOrganismAtPosition(newPosition));
            } else {
                moveOrganism(newPosition);
            }
        }
    }
}

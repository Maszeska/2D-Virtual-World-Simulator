package game.Animals;

import game.Animal;
import game.Position;
import game.World;

public class Human extends Animal {
    private static final int HUMAN_STRENGTH = 5;
    private static final int HUMAN_INIT = 4;
    private static final String HUMAN_TYPE = "Human";


    public Human(Position position, World world) {
        super(HUMAN_TYPE, HUMAN_STRENGTH, HUMAN_INIT, position, world);
        this.world = world;
    }

    @Override
    public void action() {
        if (world.getCooldown() == 10) {
            strength += 5;
        } else if (world.getCooldown() >= 5) {
            strength--;
        }

        char nextMove = world.getNextMove();
        Position newPosition = new Position(position.getY(), position.getX());
        switch (nextMove) {
            case 'w':
                newPosition.setY(newPosition.getY() - 1);
                break;
            case 's':
                newPosition.setY(newPosition.getY() + 1);
                break;
            case 'a':
                newPosition.setX(newPosition.getX() - 1);
                break;
            case 'd':
                newPosition.setX(newPosition.getX() + 1);
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

    public void setWorld(World world) {
        this.world = world;
    }

}

package game;

import java.util.Objects;
import java.util.Random;

public class Animal extends Organism {
    public Animal(String type, int strength, int initiative, Position position, World world) {
        super(type, strength, initiative, position, world);
    }

    @Override
    public void action() {
        Random random = new Random();
        int direction = random.nextInt(4);
        Position newPosition = new Position(position.getY(), position.getX());

        settingDirection(direction, newPosition);

        if (world.isPositionWithinBounds(newPosition)) {
            if (world.getOrganismAtPosition(newPosition) != null) {
                collision(world.getOrganismAtPosition(newPosition));
            } else {
                moveOrganism(newPosition);
            }
        }
    }

    public void moveOrganism(Position newPosition) {
        world.removeOrganismAtPosition(position);
        position = newPosition;
        world.addOrganismAtPosition(position, this);
    }

    @Override
    protected boolean checkBorn(Organism first, Organism second) {
        if (Objects.equals(first.getType(), second.getType())) {
            Position lPosition;
            do {
                lPosition = new Position((int) (Math.random() * world.getHeight()), (int) (Math.random() * world.getWidth()));
            } while (world.isPositionEmpty(lPosition));
            world.bornAnimal(first.getType(), lPosition);
            return true;
        }
        return false;
    }

    @Override
    public OrganismGroup getGroup() {
        return OrganismGroup.ANIMAL;
    }
}

package game;

import java.util.Random;

public class Plant extends Organism {
    private static final int PLANT_INIT = 0;

    public Plant(String type, int strength, Position position, World world) {
        super(type, strength, PLANT_INIT, position, world);
    }

    @Override
    public void action() {
        int pr = 15;
        Random random = new Random();
        int probability = random.nextInt(100);

        if (probability < pr) {
            int direction = random.nextInt(4);
            Position newPosition = new Position(position.getY(), position.getX());

            settingDirection(direction, newPosition);

            if (world.isPositionWithinBounds(newPosition)
                    && world.getOrganismAtPosition(newPosition) == null) {
                Plant newPlant = new Plant(type, strength, newPosition, world);
                world.getMap().get(newPosition.getY()).set(newPosition.getX(), newPlant);
                world.getOrganisms().add(newPlant);
            }
        }
    }

    @Override
    public OrganismGroup getGroup() {
        return OrganismGroup.PLANT;
    }
}

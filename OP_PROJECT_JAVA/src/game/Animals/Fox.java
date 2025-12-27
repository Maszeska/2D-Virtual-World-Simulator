package game.Animals;

import game.Animal;
import game.Organism;
import game.Position;
import game.World;

public class Fox extends Animal {
    private static final int FOX_STRENGTH = 3;
    private static final int FOX_INIT = 7;
    private static final String FOX_TYPE = "Fox";


    public Fox(Position position, World world) {
        super(FOX_TYPE, FOX_STRENGTH, FOX_INIT, position, world);
    }

    @Override
    public void action() {
        // Generate a random direction for movement
        int direction = (int) (Math.random() * 4);
        Position newPosition = new Position(position.getY(), position.getX());

        settingDirection(direction, newPosition);

        if (world.isPositionWithinBounds(newPosition)) {
            Organism targetOrganism = world.getOrganismAtPosition(newPosition);
            if (targetOrganism == null) {
                moveOrganism(newPosition);
            } else if (targetOrganism.getStrength() <= getStrength()) {
                collision(targetOrganism);  // Handle collision with a weaker organism
            }
        }
    }


}

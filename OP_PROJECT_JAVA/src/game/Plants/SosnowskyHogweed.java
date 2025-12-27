package game.Plants;

import game.Organism;
import game.OrganismGroup;
import game.Plant;
import game.Position;
import game.World;

public class SosnowskyHogweed extends Plant {

    private static final int SOSNOWSKY_HOGWEED_STRENGTH = 10;
    private static final String SOSNOWSKY_HOGWEED_TYPE = "Sosnowsky";


    public SosnowskyHogweed(Position position, World world) {
        super(SOSNOWSKY_HOGWEED_TYPE, SOSNOWSKY_HOGWEED_STRENGTH, position, world);
    }

    @Override
    public void action() {
        Position currentPosition = position;


        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0) {
                    continue;
                }
                Position neighborPosition = new Position(currentPosition.getY() + dy, currentPosition.getX() + dx);

                if (world.isPositionWithinBounds(neighborPosition)) {
                    Organism neighborOrganism = world.getOrganismAtPosition(neighborPosition);

                    if (neighborOrganism != null && neighborOrganism.getGroup() == OrganismGroup.ANIMAL) {
                        world.removeOrganismAtPosition(neighborPosition);
                        String info = "Sosnowsky Hogweed killed: " + neighborOrganism.getType();
                        world.displayInformation(info);
                        world.removeOrganism(neighborOrganism);
                    }
                }
            }
        }
    }
}

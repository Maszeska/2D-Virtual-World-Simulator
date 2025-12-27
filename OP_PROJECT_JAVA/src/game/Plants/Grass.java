package game.Plants;

import game.Plant;
import game.Position;
import game.World;
public class Grass extends Plant {
    private static final int GRASS_STRENGTH = 0;
    private static final String GRASS_TYPE = "Grass";

    public Grass(Position position, World world) {
        super(GRASS_TYPE, GRASS_STRENGTH, position, world);
    }
}

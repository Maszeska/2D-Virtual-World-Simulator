package game.Plants;

import game.Plant;
import game.Position;
import game.World;

public class Belladonna extends Plant {
    private static final int BELLADONNA_STRENGTH = 99;
    private static final String BELLADONNA_TYPE = "Belladonna";


    public Belladonna(Position position, World world) {
        super(BELLADONNA_TYPE, BELLADONNA_STRENGTH, position, world);
    }
}


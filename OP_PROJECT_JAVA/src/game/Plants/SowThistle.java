package game.Plants;

import game.Plant;
import game.Position;
import game.World;
public class SowThistle extends Plant {

    private static final int SOW_THISTLE_STRENGTH = 0;
    private static final String SOW_THISTLE_TYPE = "Sow Thistle";

    public SowThistle(Position position, World world) {
        super(SOW_THISTLE_TYPE, SOW_THISTLE_STRENGTH, position, world);
    }

    @Override
    public void action() {
        for (int i = 0; i < 3; ++i) {
            super.action();
        }
    }
}


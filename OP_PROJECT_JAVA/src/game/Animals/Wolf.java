package game.Animals;

import game.Animal;
import game.Position;
import game.World;

public class Wolf extends Animal {
    private static final int WOLF_STRENGTH = 9;
    private static final int WOLF_INIT = 5;
    private static final String WOLF_TYPE = "Wolf";


    public Wolf(Position position, World world) {
        super(WOLF_TYPE, WOLF_STRENGTH, WOLF_INIT, position, world);
    }
}

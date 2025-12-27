package game.Animals;

import game.Animal;
import game.Position;
import game.World;

public class Sheep extends Animal {
    private static final int SHEEP_STRENGTH = 4;
    private static final int SHEEP_INIT = 4;
    private static final String SHEEP_TYPE = "Sheep";


    public Sheep(Position position, World world) {
        super(SHEEP_TYPE, SHEEP_STRENGTH, SHEEP_INIT, position, world);
    }
}

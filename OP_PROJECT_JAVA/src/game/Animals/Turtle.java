package game.Animals;

import game.Animal;
import game.Organism;
import game.Position;
import game.World;

import java.util.Random;

public class Turtle extends Animal {
    private static final int TURTLE_STRENGTH = 2;
    private static final int TURTLE_INIT = 1;
    private static final String TURTLE_TYPE = "Turtle";


    public Turtle(Position position, World world) {
        super(TURTLE_TYPE, TURTLE_STRENGTH, TURTLE_INIT, position, world);
    }

    @Override
    protected boolean checkReflect(Organism attacker) {
        if ( attacker.getStrength() < 5) {   // Turtle reflects attack
            String info = "Turtle reflected " + attacker.getType();
            world.displayInformation(info);
            return true;
        }
        return false;
    }

    @Override
    public void action() {
        Random random = new Random();
        int chance = random.nextInt(100);
        if (chance <= 75) {
            return; // Turtle stays in the same place (75%)
        }
        super.action(); // Move the turtle
    }
}


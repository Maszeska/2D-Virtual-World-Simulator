package game.Plants;

import game.Organism;
import game.Plant;
import game.Position;
import game.World;
public class Guarana extends Plant {

    private static final int GUARANA_STRENGTH = 0;
    private static final String GUARANA_TYPE = "Guarana";

    public Guarana(Position position, World world) {
        super(GUARANA_TYPE, GUARANA_STRENGTH, position, world);
    }

    @Override
    protected void checkPowerUp(Organism attacker) {
        attacker.setStrength(getStrength()+3);
        String info = "Guarana increased strength of " + attacker.getType();
        world.displayInformation(info);
    }
}

package game;

import java.io.Serializable;

public abstract class Organism implements Serializable {
    protected String type;
    protected int strength;
    protected int initiative;
    protected Position position;
    protected World world;

    public Organism(String type, int strength, int initiative, Position position, World world) {
        this.type = type;
        this.strength = strength;
        this.initiative = initiative;
        this.position = position;
        this.world = world;
    }

    public abstract void action();

    public abstract OrganismGroup getGroup();

    public void collision(Organism defender) {
        int attackerStrength = this.strength;
        int defenderStrength = defender.getStrength();

        boolean newborn = checkBorn(this, defender);

        if (!newborn) {
            boolean escaped = checkEscaped();
            if (!escaped) {
                escaped = defender.checkEscaped();
            }
            boolean reflected = defender.checkReflect(this);
            defender.checkPowerUp(this);

            if (!escaped && !reflected) {
                String info;
                if (attackerStrength >= defenderStrength) {
                    // Attacker won
                    info = this.getType() + " eats " + defender.getType();
                    Position attackerNewPosition = defender.getPosition();
                    world.removeOrganism(defender);
                    world.addOrganismAtPosition(attackerNewPosition, this);
                    world.removeOrganismAtPosition(position);
                    position = attackerNewPosition;
                } else {
                    // Attacker loses
                    info = this.getType() + " attacked but lost to " + defender.getType();
                    world.removeOrganismAtPosition(position);
                    world.removeOrganism(this);
                }
                world.displayInformation(info);
            }
        }
    }

    public static void settingDirection(int direction, Position newPosition) {
        switch (direction) {
            case 0: // Move up
                newPosition.setY(newPosition.getY() - 1);
                break;
            case 1: // Move down
                newPosition.setY(newPosition.getY() + 1);
                break;
            case 2: // Move left
                newPosition.setX(newPosition.getX() - 1);
                break;
            case 3: // Move right
                newPosition.setX(newPosition.getX() + 1);
                break;
            default:
                break;
        }
    }

    protected boolean checkEscaped() {
        return false;
    }

    protected boolean checkReflect(Organism attacker) {
        return false;
    }

    protected void checkPowerUp(Organism attacker) {}

    protected boolean checkBorn(Organism first, Organism second) {
        return false;
    }

    public int getStrength() {
        return strength;
    }
    public String getType() {return type;}

    public void setStrength(int newStrength) {
        strength = newStrength;
    }

    public Position getPosition() {
        return position;
    }
}

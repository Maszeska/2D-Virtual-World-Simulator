from random import randint, random
from src.game.Animal import Animal
from src.game.Position import Position


class Antelope(Animal):
    ANTELOPE_STRENGTH = 4
    ANTELOPE_INIT = 4
    ANTELOPE_TYPE = "Antelope"

    def __init__(self, position, world):
        super().__init__(Antelope.ANTELOPE_TYPE, Antelope.ANTELOPE_STRENGTH, Antelope.ANTELOPE_INIT, position, world)

    def check_escaped(self):
        escape_chance = random()
        if escape_chance < 0.5:
            self.world.display_information("Antelope escaped from the fight!")
            return True
        return False

    def action(self):
        direction = randint(0, 3)
        new_position = Position(self.position.get_y(), self.position.get_x())

        if direction == 0:  # Move up
            new_position.set_y(new_position.get_y() - 2)
        elif direction == 1:  # Move down
            new_position.set_y(new_position.get_y() + 2)
        elif direction == 2:  # Move left
            new_position.set_x(new_position.get_x() - 2)
        elif direction == 3:  # Move right
            new_position.set_x(new_position.get_x() + 2)

        if self.world.is_position_within_bounds(new_position):
            organism_at_new_position = self.world.get_organism_at_position(new_position)
            if organism_at_new_position is not None:
                self.collision(organism_at_new_position)
            else:
                self.move(new_position)

from random import randint
from Organism import Organism
from Position import Position


class Plant(Organism):
    PLANT_INIT = 0

    def __init__(self, organism_type, strength, position, world):
        super().__init__(organism_type, strength, Plant.PLANT_INIT, position, world)

    def action(self):
        pr = 15
        probability = randint(0, 99)

        if probability < pr:
            direction = randint(0, 3)
            new_position = Position(self.position.get_y(), self.position.get_x())
            self.setting_direction(direction, new_position)

            if self.world.is_position_within_bounds(new_position) \
                    and self.world.get_organism_at_position(new_position) is None:
                self.world.born_organism(self.type, new_position)

    def get_group(self):
        return "PLANT"

from random import randint
from Organism import Organism
from Position import Position


class Animal(Organism):
    def __init__(self, organism_type, strength, initiative, position, world):
        super().__init__(organism_type, strength, initiative, position, world)

    def action(self):
        direction = randint(0, 3)
        new_position = Position(self.position.get_y(), self.position.get_x())
        self.setting_direction(direction, new_position)

        if self.world.is_position_within_bounds(new_position):
            organism_at_new_position = self.world.get_organism_at_position(new_position)
            if organism_at_new_position is not None:
                self.collision(organism_at_new_position)
            else:
                (self.move(new_position))

    def check_born(self, first, second):
        if first.get_type() == second.get_type():
            while True:
                new_position = Position(randint(0, self.world.height - 1), randint(0, self.world.width - 1))
                if self.world.is_position_empty(new_position):
                    self.world.born_organism(first.get_type(), new_position)
                    return True
        return False

    def get_group(self):
        return "ANIMAL"

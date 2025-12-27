from random import randint
from src.game.Animal import Animal
from src.game.Position import Position


class Fox(Animal):
    FOX_STRENGTH = 3
    FOX_INIT = 7
    FOX_TYPE = "Fox"

    def __init__(self, position, world):
        super().__init__(Fox.FOX_TYPE, Fox.FOX_STRENGTH, Fox.FOX_INIT, position, world)

    def action(self):
        direction = randint(0, 3)
        new_position = Position(self.position.get_y(), self.position.get_x())
        self.setting_direction(direction, new_position)

        if self.world.is_position_within_bounds(new_position):
            target_organism = self.world.get_organism_at_position(new_position)
            if target_organism is None:
                self.move(new_position)
            elif target_organism.get_strength() <= self.strength:
                self.collision(target_organism)

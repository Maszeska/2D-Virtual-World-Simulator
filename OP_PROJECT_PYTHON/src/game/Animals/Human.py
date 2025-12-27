from src.game.Animal import Animal
from src.game.Position import Position


class Human(Animal):
    HUMAN_STRENGTH = 5
    HUMAN_INIT = 4
    HUMAN_TYPE = "Human"

    def __init__(self, position, world):
        super().__init__(Human.HUMAN_TYPE, Human.HUMAN_STRENGTH, Human.HUMAN_INIT, position, world)
        self.world = world

    def action(self):
        if self.world.cooldown == 10:
            self.strength += 5
        elif self.world.cooldown >= 5:
            self.strength -= 1

        next_move = self.world.next_move
        new_position = Position(self.position.get_y(), self.position.get_x())

        if next_move == 'w':
            new_position.set_y(new_position.get_y() - 1)
        elif next_move == 's':
            new_position.set_y(new_position.get_y() + 1)
        elif next_move == 'a':
            new_position.set_x(new_position.get_x() - 1)
        elif next_move == 'd':
            new_position.set_x(new_position.get_x() + 1)

        if self.world.is_position_within_bounds(new_position):
            organism_at_new_position = self.world.get_organism_at_position(new_position)
            if organism_at_new_position is not None:
                self.collision(organism_at_new_position)
            else:
                self.move(new_position)

    def set_world(self, world):
        self.world = world

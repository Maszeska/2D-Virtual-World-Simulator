from src.game.Position import Position
from src.game.Animal import Animal


class CyberSheep(Animal):
    CYBER_SHEEP_STRENGTH = 11
    CYBER_SHEEP_INIT = 4
    CYBER_SHEEP_TYPE = "Cyber Sheep"
    SOSNOWSKY_HOGWEED_TYPE = "Sosnowsky"

    def __init__(self, position, world):
        super().__init__(CyberSheep.CYBER_SHEEP_TYPE, CyberSheep.CYBER_SHEEP_STRENGTH, CyberSheep.CYBER_SHEEP_INIT, position, world)

    def action(self):
        closest_hogweed = self.find_closest_hogweed()
        if closest_hogweed:
            self.move_to_position(closest_hogweed.position)
        else:
            super().action()

    def move_to_position(self, target_position):
        dx = target_position.get_x() - self.position.get_x()
        dy = target_position.get_y() - self.position.get_y()

        new_position = Position(self.position.get_y(), self.position.get_x())

        if abs(dx) > abs(dy):
            if dx > 0:
                new_position.set_x(new_position.get_x() + 1)
            else:
                new_position.set_x(new_position.get_x() - 1)
        else:
            if dy > 0:
                new_position.set_y(new_position.get_y() + 1)
            else:
                new_position.set_y(new_position.get_y() - 1)

        if self.world.is_position_within_bounds(new_position):
            organism_at_new_position = self.world.get_organism_at_position(new_position)
            if organism_at_new_position is not None:
                self.collision(organism_at_new_position)
            else:
                self.move(new_position)

    def find_closest_hogweed(self):
        closest_distance = float('inf')
        closest_hogweed = None

        for y in range(len(self.world.map)):
            for x in range(len(self.world.map[0])):
                organism = self.world.map[y][x]
                if organism and organism.type == CyberSheep.SOSNOWSKY_HOGWEED_TYPE:
                    distance = self.position.calculate_distance(organism.position)
                    if distance < closest_distance:
                        closest_distance = distance
                        closest_hogweed = organism

        return closest_hogweed

from src.game.Plant import Plant
from src.game.Position import Position


class SosnowskyHogweed(Plant):
    SOSNOWSKY_HOGWEED_STRENGTH = 10
    SOSNOWSKY_HOGWEED_TYPE = "Sosnowsky"

    def __init__(self, position, world):
        super().__init__(SosnowskyHogweed.SOSNOWSKY_HOGWEED_TYPE, SosnowskyHogweed.SOSNOWSKY_HOGWEED_STRENGTH, position, world)

    def action(self):
        current_position = self.position

        for dy in range(-1, 2):
            for dx in range(-1, 2):
                if dx == 0 and dy == 0:
                    continue
                neighbor_position = Position(current_position.get_y() + dy, current_position.get_x() + dx)

                if self.world.is_position_within_bounds(neighbor_position):
                    neighbor_organism = self.world.get_organism_at_position(neighbor_position)

                    if neighbor_organism is not None and neighbor_organism.get_group() == "ANIMAL" and neighbor_organism.get_type() != "Cyber Sheep":
                        self.world.remove_organism_at_position(neighbor_position)
                        info = "Sosnowsky Hogweed killed: " + neighbor_organism.get_type()
                        self.world.display_information(info)
                        self.world.remove_organism(neighbor_organism)

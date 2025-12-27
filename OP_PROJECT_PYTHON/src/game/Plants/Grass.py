from src.game.Plant import Plant


class Grass(Plant):
    GRASS_STRENGTH = 0
    GRASS_TYPE = "Grass"

    def __init__(self, position, world):
        super().__init__(Grass.GRASS_TYPE, Grass.GRASS_STRENGTH, position, world)

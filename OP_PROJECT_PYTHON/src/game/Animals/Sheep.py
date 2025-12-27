from src.game.Animal import Animal


class Sheep(Animal):
    SHEEP_STRENGTH = 4
    SHEEP_INIT = 4
    SHEEP_TYPE = "Sheep"

    def __init__(self, position, world):
        super().__init__(Sheep.SHEEP_TYPE, Sheep.SHEEP_STRENGTH, Sheep.SHEEP_INIT, position, world)

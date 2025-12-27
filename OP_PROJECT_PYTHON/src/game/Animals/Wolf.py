from src.game.Animal import Animal


class Wolf(Animal):
    WOLF_STRENGTH = 9
    WOLF_INIT = 5
    WOLF_TYPE = "Wolf"

    def __init__(self, position, world):
        super().__init__(Wolf.WOLF_TYPE, Wolf.WOLF_STRENGTH, Wolf.WOLF_INIT, position, world)

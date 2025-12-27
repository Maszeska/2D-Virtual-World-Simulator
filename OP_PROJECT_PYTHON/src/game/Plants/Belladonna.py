from src.game.Plant import Plant


class Belladonna(Plant):
    BELLADONNA_STRENGTH = 99
    BELLADONNA_TYPE = "Belladonna"

    def __init__(self, position, world):
        super().__init__(Belladonna.BELLADONNA_TYPE, Belladonna.BELLADONNA_STRENGTH, position, world)

from src.game.Plant import Plant


class SowThistle(Plant):
    SOW_THISTLE_STRENGTH = 0
    SOW_THISTLE_TYPE = "Sow Thistle"

    def __init__(self, position, world):
        super().__init__(SowThistle.SOW_THISTLE_TYPE, SowThistle.SOW_THISTLE_STRENGTH, position, world)

    def action(self):
        for _ in range(3):
            super().action()

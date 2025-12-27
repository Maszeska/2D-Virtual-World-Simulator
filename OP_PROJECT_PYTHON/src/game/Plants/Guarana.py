from src.game.Plant import Plant


class Guarana(Plant):
    GUARANA_STRENGTH = 0
    GUARANA_TYPE = "Guarana"

    def __init__(self, position, world):
        super().__init__(Guarana.GUARANA_TYPE, Guarana.GUARANA_STRENGTH, position, world)

    def check_power_up(self, attacker):
        attacker.set_strength(attacker.get_strength() + 3)
        info = "Guarana increased strength of " + attacker.get_type()
        self.world.display_information(info)

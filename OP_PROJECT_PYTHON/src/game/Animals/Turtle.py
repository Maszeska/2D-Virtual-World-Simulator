from random import randint
from src.game.Animal import Animal


class Turtle(Animal):
    TURTLE_STRENGTH = 2
    TURTLE_INIT = 1
    TURTLE_TYPE = "Turtle"

    def __init__(self, position, world):
        super().__init__(Turtle.TURTLE_TYPE, Turtle.TURTLE_STRENGTH, Turtle.TURTLE_INIT, position, world)

    def check_reflect(self, attacker):
        if attacker.get_strength() < 5:
            info = "Turtle reflected " + attacker.get_type()
            self.world.display_information(info)
            return True
        return False

    def action(self):
        chance = randint(0, 99)
        if chance <= 75:
            return
        super().action()

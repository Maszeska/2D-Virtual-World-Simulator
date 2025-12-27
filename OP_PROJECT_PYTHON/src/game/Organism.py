from abc import ABC, abstractmethod


class Organism(ABC):
    def __init__(self, organism_type, strength, initiative, position, world):
        self.type = organism_type
        self.strength = strength
        self.initiative = initiative
        self.position = position
        self.world = world

    @abstractmethod
    def action(self):
        pass

    @abstractmethod
    def get_group(self):
        pass

    def collision(self, defender):
        attacker_strength = self.strength
        defender_strength = defender.get_strength()

        newborn = self.check_born(self, defender)

        if not newborn:
            escaped = self.check_escaped()
            if not escaped:
                escaped = defender.check_escaped()
            reflected = defender.check_reflect(self)
            defender.check_power_up(self)

            if not escaped and not reflected:
                if attacker_strength >= defender_strength:
                    # Attacker won
                    info = f"{self.get_type()} eats {defender.get_type()}"
                    attacker_new_position = defender.get_position()
                    self.world.remove_organism(defender)
                    self.world.add_organism_at_position(attacker_new_position, self)
                    self.world.remove_organism_at_position(self.position)
                    self.position = attacker_new_position
                else:
                    # Attacker loses
                    info = f"{self.get_type()} attacked but lost to {defender.get_type()}"
                    self.world.remove_organism_at_position(self.position)
                    self.world.remove_organism(self)
                self.world.display_information(info)

    @staticmethod
    def setting_direction(direction, new_position):
        if direction == 0:  # Move up
            new_position.set_y(new_position.get_y() - 1)
        elif direction == 1:  # Move down
            new_position.set_y(new_position.get_y() + 1)
        elif direction == 2:  # Move left
            new_position.set_x(new_position.get_x() - 1)
        elif direction == 3:  # Move right
            new_position.set_x(new_position.get_x() + 1)

    def move(self, new_position):
        if self.world.is_position_within_bounds(new_position):
            self.world.remove_organism_at_position(self.position)
            self.world.add_organism_at_position(new_position, self)
            self.position = new_position

    def check_escaped(self):
        return False

    def check_reflect(self, attacker):
        return False

    def check_power_up(self, attacker):
        pass

    def check_born(self, first, second):
        return False

    def get_strength(self):
        return self.strength

    def get_type(self):
        return self.type

    def set_strength(self, new_strength):
        self.strength = new_strength

    def get_position(self):
        return self.position

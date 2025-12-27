import math


class Position:
    def __init__(self, y, x):
        self.y = y
        self.x = x

    def get_y(self):
        return self.y

    def set_y(self, y):
        self.y = y

    def get_x(self):
        return self.x

    def set_x(self, x):
        self.x = x

    def calculate_distance(self, other_position):
        dx = self.x - other_position.x
        dy = self.y - other_position.y
        distance = math.sqrt(dx*dx + dy*dy)
        return distance

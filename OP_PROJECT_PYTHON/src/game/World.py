import pickle
from tkinter import messagebox
from PIL import Image, ImageTk
import random
import os

import tkinter as tk

from Position import Position
from OrganismType import OrganismType  # Assuming you have a similar Enum for Organism types
from Animals.Human import Human
from Animals.Wolf import Wolf
from Animals.Sheep import Sheep
from Animals.Fox import Fox
from Animals.Turtle import Turtle
from Animals.Antelope import Antelope
from Animals.CyberSheep import CyberSheep
from Plants.Grass import Grass
from Plants.SowThistle import SowThistle
from Plants.Guarana import Guarana
from Plants.Belladonna import Belladonna
from Plants.SosnowskyHogweed import SosnowskyHogweed


def initialize_organism_counts():
    return {
        OrganismType.HUMAN: 1,
        OrganismType.WOLF: 2,
        OrganismType.SHEEP: 3,
        OrganismType.FOX: 2,
        OrganismType.TURTLE: 2,
        OrganismType.ANTELOPE: 2,
        OrganismType.GRASS: 3,
        OrganismType.SOW_THISTLE: 2,
        OrganismType.GUARANA: 2,
        OrganismType.BELLADONNA: 1,
        OrganismType.SOSNOWSKY_HOGWEED: 2,
        OrganismType.CYBER_SHEEP: 1,
    }

class World:
    def __init__(self, width, height, cell_size, world_panel):
        self.cell_size = cell_size
        self.width = width
        self.height = height
        self.cooldown = 0
        self.next_move = 'd'
        self.map = [[None for _ in range(width)] for _ in range(height)]
        self.organisms = []
        self.organism_counts = initialize_organism_counts()
        self.world_panel = world_panel
        self.image_references = []

        self.create_world()

    def get_image_path(self, organism):
        current_dir = os.path.dirname(os.path.abspath(__file__))
        base_path = os.path.join(current_dir, "..", "img")

        organism_type = organism.get_type()
        filename = f"{organism_type}.png"
        full_path = os.path.join(base_path, filename)

        if not os.path.exists(full_path):
            print(f"Warning: Image not found at {full_path}")

        return full_path

    def create_world(self):
        self.create_organism()

    def create_organism(self):
        for org_type, count in self.organism_counts.items():
            for _ in range(count):
                while True:
                    pos = Position(random.randint(0, self.height - 1), random.randint(0, self.width - 1))
                    if self.get_organism_at_position(pos) is None:
                        break
                organism = self.create_organism_by_type(org_type, pos)
                if organism:
                    self.organisms.append(organism)
                    self.add_organism_at_position(pos, organism)

    def create_organism_by_type(self, org_type, position):
        if org_type == OrganismType.HUMAN:
            return Human(position, self)
        elif org_type == OrganismType.WOLF:
            return Wolf(position, self)
        elif org_type == OrganismType.SHEEP:
            return Sheep(position, self)
        elif org_type == OrganismType.FOX:
            return Fox(position, self)
        elif org_type == OrganismType.TURTLE:
            return Turtle(position, self)
        elif org_type == OrganismType.ANTELOPE:
            return Antelope(position, self)
        elif org_type == OrganismType.GRASS:
            return Grass(position, self)
        elif org_type == OrganismType.SOW_THISTLE:
            return SowThistle(position, self)
        elif org_type == OrganismType.GUARANA:
            return Guarana(position, self)
        elif org_type == OrganismType.BELLADONNA:
            return Belladonna(position, self)
        elif org_type == OrganismType.SOSNOWSKY_HOGWEED:
            return SosnowskyHogweed(position, self)
        elif org_type == OrganismType.CYBER_SHEEP:
            return CyberSheep(position, self)
        return None

    def draw(self, canvas):
        self.image_references.clear()
        for y in range(self.height):
            for x in range(self.width):
                organism = self.map[y][x]
                if organism is not None:
                    self.draw_organism(canvas, organism, x * self.cell_size, y * self.cell_size)

    def draw_organism(self, canvas, organism, x, y):
        image_path = self.get_image_path(organism)
        image = Image.open(image_path)
        image = image.resize((self.cell_size, self.cell_size))
        photo = ImageTk.PhotoImage(image)
        canvas.create_image(x, y, anchor=tk.NW, image=photo)
        self.image_references.append(photo)

    def make_turn(self):
        self.world_panel.add_text_to_info_panel("*** Next turn ***")
        for organism in self.organisms:
            organism.action()
        if self.cooldown > 0:
            self.cooldown -= 1

    def born_organism(self, org_type_name, position):
        org_type = OrganismType[org_type_name.upper().replace(" ", "_")]
        new_organism = self.create_organism_by_type(org_type, position)
        if new_organism:
            self.organisms.append(new_organism)
            self.add_organism_at_position(position, new_organism)
            self.world_panel.add_text_to_info_panel(f"New {org_type_name} was born")

    def remove_organism(self, organism):
        if organism in self.organisms:
            self.organisms.remove(organism)
        pos = organism.get_position()
        if self.is_position_within_bounds(pos):
            self.map[pos.y][pos.x] = None

    def remove_organism_at_position(self, position):
        if self.is_position_within_bounds(position):
            self.map[position.get_y()][position.get_x()] = None

    def add_organism_at_position(self, position, organism):
        if self.is_position_within_bounds(position):
            self.map[position.get_y()][position.get_x()] = organism

    def is_human_alive(self):
        return any(isinstance(org, Human) for org in self.organisms)

    def set_next_move(self, move):
        self.next_move = move
        self.print_direction()

    def get_organism_at_position(self, position):
        if self.is_position_within_bounds(position):
            return self.map[position.y][position.x]
        return None

    def is_position_empty(self, position):
        return self.map[position.get_y()][position.get_x()] is not None

    def is_position_within_bounds(self, position):
        return 0 <= position.x < self.width and 0 <= position.y < self.height

    def print_direction(self):
        direction = {
            'w': "Human will move up",
            's': "Human will move down",
            'a': "Human will move left",
            'd': "Human will move right"
        }
        self.world_panel.add_text_to_info_panel(direction.get(self.next_move, ""))

    def display_information(self, info):
        self.world_panel.add_text_to_info_panel(info)

    def activate_special_power(self):
        if self.cooldown == 0:
            self.cooldown = 10
            info = "Human special power activated"
        else:
            info = f"Not possible to activate special power for {self.cooldown} turns"
        self.world_panel.add_text_to_info_panel(info)

    def __getstate__(self):
        state = self.__dict__.copy()
        del state['world_panel']
        if 'canvas' in state:
            del state['canvas']
        del state['image_references']
        return state

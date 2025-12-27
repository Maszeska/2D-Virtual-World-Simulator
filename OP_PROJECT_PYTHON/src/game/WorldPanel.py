import tkinter as tk
from tkinter import ttk, messagebox
import pickle
from Position import Position
from World import World


class WorldPanel(tk.Frame):
    CELL_SIZE = 40
    WORLD_SIZE_WIDTH = 20
    WORLD_SIZE_HEIGHT = 11
    INFO_HEIGHT = 180
    BUTTON_HEIGHT = 40
    BUTTON_WIDTH = 100

    def __init__(self, master, width, height, *args, **kwargs):
        super().__init__(master, *args, **kwargs)

        self.world = World(self.WORLD_SIZE_WIDTH, self.WORLD_SIZE_HEIGHT, self.CELL_SIZE, self)

        self.grid_panel = tk.Canvas(self, width=width, height=height - self.INFO_HEIGHT - self.BUTTON_HEIGHT, bg="white")
        self.grid_panel.bind("<Button-1>", self.on_canvas_click)

        self.info_text_area = tk.Text(self, wrap=tk.WORD)
        self.info_text_area.config(state=tk.DISABLED)
        self.scrollbar = tk.Scrollbar(self, command=self.info_text_area.yview)
        self.info_text_area.config(yscrollcommand=self.scrollbar.set)

        self.make_turn_button = tk.Button(self, text="Next Turn", command=self.make_turn)
        self.save_button = tk.Button(self, text="Save Game", command=self.save_game)
        self.load_button = tk.Button(self, text="Load Game", command=self.load_game)

        self.organism_options = ["Wolf", "Sheep", "Fox", "Turtle", "Antelope", "Grass", "Sow Thistle", "Guarana", "Belladonna", "Sosnowsky Hogweed", "Cyber Sheep"]

        self.setup_ui()
        self.bind_all("<Key>", self.handle_input)

        self.world.draw(self.grid_panel)
        self.grid_panel.update()

    def setup_ui(self):
        self.grid_panel.pack(side=tk.TOP, fill=tk.BOTH, expand=True)

        self.make_turn_button.pack(side=tk.LEFT, padx=5, pady=5)
        self.save_button.pack(side=tk.LEFT, padx=5, pady=5)
        self.load_button.pack(side=tk.LEFT, padx=5, pady=5)

        self.info_text_area.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        self.scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

    def make_turn(self):
        self.world.make_turn()
        if not self.world.is_human_alive():
            self.end_screen()
        else:
            self.grid_panel.delete("all")
            self.world.draw(self.grid_panel)
            self.grid_panel.update()

    def save_game(self):
        try:
            with open('savefile.pkl', 'wb') as f:
                pickle.dump(self.world, f)
            messagebox.showinfo("Success", "Game state saved.")
            self.focus_set()
        except Exception as ex:
            print(ex)
            messagebox.showerror("Error", f"Failed to save the game: {ex}")

    def load_game(self):
        try:
            with open('savefile.pkl', 'rb') as f:
                loaded_world = pickle.load(f)
                # Update the current world instance with the loaded one
                self.world.__dict__.update(loaded_world.__dict__)
                # Reassign the world reference for each organism
                for organism in self.world.organisms:
                    organism.world = self.world
                self.grid_panel.delete("all")
                self.world.draw(self.grid_panel)
                self.grid_panel.update()
            messagebox.showinfo("Success", "Game loaded successfully")
        except Exception as e:
            messagebox.showerror("Error", "Failed to load the game")

    def handle_input(self, event):
        ch = event.char
        if ch in ['w', 's', 'a', 'd']:
            self.world.set_next_move(ch)
        elif ch == 'p':
            self.world.activate_special_power()

    def on_canvas_click(self, event):
        mouse_x = event.x // self.CELL_SIZE
        mouse_y = event.y // self.CELL_SIZE
        if self.world.is_position_within_bounds(Position(mouse_y, mouse_x)):
            existing_organism = self.world.get_organism_at_position(Position(mouse_y, mouse_x))
            if existing_organism is None:
                self.open_organism_selection_window(Position(mouse_y, mouse_x))

    def open_organism_selection_window(self, position):
        self.selection_window = tk.Toplevel(self)
        self.selection_window.title("Choose Organism")

        # Center the selection window relative to the main window
        window_width = 300
        window_height = 150
        screen_width = self.master.winfo_screenwidth()
        screen_height = self.master.winfo_screenheight()
        x_cordinate = int((screen_width / 2) - (window_width / 2))
        y_cordinate = int((screen_height / 2) - (window_height / 2))
        self.selection_window.geometry(f"{window_width}x{window_height}+{x_cordinate}+{y_cordinate}")

        self.organism_var = tk.StringVar(self.selection_window)
        self.organism_var.set(self.organism_options[0])  # default value

        label = tk.Label(self.selection_window, text="Choose the type of organism to add:")
        label.pack(pady=10)

        self.organism_menu = ttk.Combobox(self.selection_window, textvariable=self.organism_var, values=self.organism_options, state='readonly')
        self.organism_menu.pack(pady=10)

        add_button = tk.Button(self.selection_window, text="Add Organism", command=lambda: self.add_organism(position))
        add_button.pack(pady=10)

    def add_organism(self, position):
        chosen_type = self.organism_var.get()
        if chosen_type in self.organism_options:
            self.world.born_organism(chosen_type, position)
            self.world.draw(self.grid_panel)
            self.grid_panel.update()
        self.selection_window.destroy()

    def add_text_to_info_panel(self, text):
        self.info_text_area.config(state=tk.NORMAL)
        self.info_text_area.insert(tk.END, text + "\n")
        self.info_text_area.see(tk.END)
        self.info_text_area.config(state=tk.DISABLED)

    def end_screen(self):
        self.disable_input()
        self.grid_panel.delete("all")
        self.grid_panel.create_text(self.grid_panel.winfo_width() / 2, self.grid_panel.winfo_height() / 2, text="YOU LOST", fill="red", font=("Arial", 24))

    def disable_input(self):
        self.grid_panel.unbind("<Button-1>")
        self.unbind_all("<Key>")
        for widget in [self.make_turn_button, self.save_button, self.load_button]:
            widget.config(state=tk.DISABLED)

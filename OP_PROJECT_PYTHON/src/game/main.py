import tkinter as tk
from WorldPanel import WorldPanel


def main():
    window = tk.Tk()
    window.title("Game")
    window.geometry("800x700")

    world_panel = WorldPanel(window, width=800, height=700)
    world_panel.pack(fill=tk.BOTH, expand=True)

    window.mainloop()


if __name__ == "__main__":
    main()

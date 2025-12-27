# Virtual World Simulator (OOP Project)

>_Project created as part of an Object Oriented Programming course during studies._

A turn-based ecosystem simulator where different species of animals and plants interact on a 2D grid. This project demonstrates core **Object-Oriented Programming (OOP)** principles like inheritance, polymorphism, and encapsulation across multiple programming languages.

### Simulation Rules & Mechanics
- Each turn, organisms act in order of **initiative**, then **age**.
- Animals can:
  - Move to adjacent cells
  - Fight other organisms based on strength
  - Reproduce with the same species
- Plants can:
  - Spread to neighboring cells
  - Apply special effects (e.g., poison, strength boost)
- The Human character is player-controlled and has a unique special ability.

### Implemented Species & Behaviors
| Species | Type | Strength | Initiative | Special Ability / Behavior |
| :--- | :--- | :---: | :---: | :--- |
| **Human** | 🐾 | 5 | 4 | Player-controlled; "Magical Potion" boosts strength to 10, decaying by 1 each turn. |
| **Wolf** | 🐾 | 9 | 5 | High strength predator. |
| **Sheep** | 🐾 | 4 | 4 | Standard prey animal. |
| **Fox** | 🐾 | 3 | 7 | **Sense of Smell:** Never moves to a cell with a stronger organism. |
| **Turtle** | 🐾 | 2 | 1 | **Defense:** 75% chance to stay still; reflects attacks from strength < 5. |
| **Antelope** | 🐾 | 4 | 4 | **Agility:** Range of 2 cells; 50% chance to escape combat. |
| **CyberSheep**| 🐾 | 11 | 4 | **Specialized:** Targets Sosnowsky's Hogweed (Python version). |
| **Grass** | 🌿 | 0 | 0 | Basic spreading plant. |
| **Sow Thistle**| 🌿 | 0 | 0 | Tries to spread 3 times per turn. |
| **Guarana** | 🌿 | 0 | 0 | Increases consumer's strength by +3 permanently. |
| **Belladonna** | 🌿 | 99 | 0 | Kills any animal that consumes it. |
| **Hogweed** | 🌿 | 10 | 0 | Kills all adjacent animals every turn. |

---

## 🛠 C++ Implementation (Ncurses)

The C++ version uses a terminal interface powered by the `ncurses` library. It features a grid-based map where organisms act based on their initiative and strength.

<img width="437" height="413" alt="Screenshot 2025-12-27 at 15 49 52" src="https://github.com/user-attachments/assets/b4363c3b-27d3-44ef-ae53-9a44dc515c4c" />

### Controls
| Key | Action |
| :--- | :--- |
| `w`, `a`, `s`, `d` | Set direction for Human (Up, Left, Down, Right) |
| `.` | Advance to the **Next Turn** (All organisms move/act) |
| `p` | Activate Human Special Power (10-turn cooldown) |
| `k` | **Save** current world state to `world_save.txt` |
| `l` | **Load** world state from `world_save.txt` |
| `q` | Quit Game |

### How to Build and Run
> **Prerequisites:** Install `ncurses` and `cmake`.
   
1. **Build:**
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```
   
2. **Run:**
   ```bash
   ./OP_PROJECT_CPP
   ```
   
---

## ☕ Java Implementation (Swing GUI)

The Java version features a graphical user interface (GUI) built with Swing. It uses high-resolution images for organisms and a mouse-interactive grid.

<img width="912" height="840" alt="Screenshot 2025-12-27 at 16 04 46" src="https://github.com/user-attachments/assets/539760bb-febc-4f85-8cc8-0d7ff12f1980" />

### Controls
| Key | Action |
| :--- | :--- |
| `w`, `a`, `s`, `d` | Set direction for Human (Up, Left, Down, Right) |
| `p` | Activate Human Special Power (10-turn cooldown) |
| **Mouse Click** | Click an empty cell to spawn a new organism from a selection menu. |
| **Buttons** | Use the UI buttons for **Next Turn**, **Save Game**, and **Load Game**. |

### How to Build and Run
> **Prerequisites:** Install **JDK 17** or higher.
   
**Open in IDE**
   - Open the `OP_PROJECT_JAVA` folder in IntelliJ IDEA.
   - Run the `Main.java` file.
   
---

## 🐍 Python Implementation (Tkinter GUI)

The Python version provides a graphical experience using the Tkinter library for the interface and Pillow (PIL) for high-quality image rendering. It features a dynamic grid and an event-driven logic.

<img width="912" height="840" alt="Screenshot 2025-12-27 at 17 27 25" src="https://github.com/user-attachments/assets/dfee2467-bc05-4792-b77b-4b51d7f90f31" />

### Controls
| Key | Action |
| :--- | :--- |
| `w`, `a`, `s`, `d` | Set direction for Human (Up, Left, Down, Right) |
| `p` | Activate Human Special Power (10-turn cooldown) |
| **Mouse Click** | Click an empty cell to spawn a new organism from a selection menu. |
| **Buttons** | Use the UI buttons for **Next Turn**, **Save Game**, and **Load Game**. |

### How to Build and Run
> **Prerequisites:** **Python 3.x** and the `Pillow` library.
   
**Open in IDE**
   - Open the `OP_PROJECT_PYTHON` folder in PyCharm.
   - Run the `Main.py` file.

# Virtual World Simulator (OOP Project)

A turn-based ecosystem simulator where different species of animals and plants interact on a 2D grid. This project demonstrates core **Object-Oriented Programming (OOP)** principles like inheritance, polymorphism, and encapsulation across multiple programming languages.



---

## 🛠 C++ Implementation (Ncurses)

The C++ version uses a terminal interface powered by the `ncurses` library. It features a grid-based map where organisms act based on their initiative and strength.

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
   
2. **Run:**
   ```bash
   ./OP_PROJECT_CPP
   

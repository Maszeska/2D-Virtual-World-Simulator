# Virtual World Simulator (OOP Project)

A turn-based ecosystem simulator where different species of animals and plants interact on a 2D grid. This project demonstrates core **Object-Oriented Programming (OOP)** principles like inheritance, polymorphism, and encapsulation across multiple programming languages.



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
| **Mouse Click** | Click an empty cell to manually spawn a new organism of your choice. |
| **Buttons** | Use the UI buttons for **Next Turn**, **Save Game**, and **Load Game**. |

### How to Build and Run
> **Prerequisites:** Install **JDK 17** or higher.
   
**Open in IDE**
   * Open the `OP_PROJECT_JAVA` folder in IntelliJ IDEA.
   * Ensure the `src` folder is marked as the "Sources Root."
   * Run the `Main.java` file.
   
   

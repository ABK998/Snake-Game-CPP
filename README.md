# Snake Game in C++

## Overview
This is a **classic Snake game** implemented in C++ for the console. It includes features such as a **main menu, difficulty selection, score saving, and smooth gameplay mechanics**.

## Features
1. **Classic Snake gameplay** with movement controls  
2. **Multiple difficulty levels** (Easy, Medium, Hard)  
3. **Score saving system** (stores past scores in a file)  
4. **Main menu with options to start, view scores, change difficulty, or exit**  
5. **Smooth rendering in the console window**  
6. **Border collision and self-collision detection**  

## Controls
- **W / A / S / D** → Move the snake
- **X** → Exit the game during play

## How to Play
1. Run the program.
2. Select an option from the main menu:
   - **Play Game**: Start playing Snake.
   - **See Scores**: View previously saved scores.
   - **Change Difficulty**: Adjust game speed.
   - **Exit**: Quit the game.
3. Control the snake using `W, A, S, D` keys.
4. Eat the food (`*`) to grow and increase score.
5. Avoid hitting the walls or your own tail.
6. When the game ends, your score is saved automatically.

## Installation & Compilation
To compile and run the game, follow these steps:

### **Windows (MinGW/GCC Compiler)**
1. Open a terminal and navigate to the directory where `snake.cpp` is saved.
2. Compile using g++:
   ```sh
   g++ snake.cpp -o snake.exe
   ```
3. Run the game:
   ```sh
   snake.exe
   ```

### **Using Visual Studio**
1. Open `snake.cpp` in Visual Studio.
2. Click on **Build** → **Compile & Run**.

## Dependencies
- **Windows OS** (uses `conio.h` and `windows.h` for rendering)
- **C++ Compiler** (MinGW, MSVC, or another supporting compiler)

## Future Improvements
- Add a **pause feature**.
- Implement **customizable controls**.
- Introduce **more power-ups and obstacles**.


## Contributing
Feel free to **fork** this repository, **submit issues**, and **contribute improvements**!

## License
This project is open-source and licensed under the **MIT License**.


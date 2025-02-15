#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <fstream> // For file handling
using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;

int snakeX, snakeY, foodX, foodY, score;
int tailX[100], tailY[100]; // Store tail positions
int tailLength;             // Length of the tail
bool gameOver;
int snakeSpeed = 100;       // Default speed (Medium)

// Direction constants
const int STOP = 0, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4;
int dir;

void gotoXY(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void initializeGame() {
    gameOver = false;
    dir = STOP; // Start with no direction
    snakeX = WIDTH / 2;
    snakeY = HEIGHT / 2;
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
    score = 0;
    tailLength = 0;
}

void draw() {
    gotoXY(0, 0); // Move cursor to the top-left corner
    // Draw the top border
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << endl;

    // Draw the playing area
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) cout << "#"; // Left border

            if (i == snakeY && j == snakeX)
                cout << "O"; // Snake head
            else if (i == foodY && j == foodX)
                cout << "*"; // Food
            else {
                bool isTail = false;
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Snake tail
                        isTail = true;
                    }
                }
                if (!isTail) cout << " ";
            }

            if (j == WIDTH - 1) cout << "#"; // Right border
        }
        cout << endl;
    }

    // Draw the bottom border
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << endl;

    // Display the score
    cout << "Score: " << score << endl;

    if(snakeSpeed == 200) cout << "The Difficulty is Easy." << endl;
    if(snakeSpeed == 100) cout << "The Difficulty is Medium." << endl;
    if(snakeSpeed == 50) cout << "The Difficulty is Hard." << endl;
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': case 'A': dir = LEFT; break;
        case 'd': case 'D': dir = RIGHT; break;
        case 'w': case 'W': dir = UP; break;
        case 's': case 'S': dir = DOWN; break;
        case 'x': case 'X': gameOver = true; break;
        }
    }
}

void logic() {
    // Update tail positions
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = snakeX;
    tailY[0] = snakeY;

    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move the snake based on the direction
    switch (dir) {
    case LEFT: snakeX--; break;
    case RIGHT: snakeX++; break;
    case UP: snakeY--; break;
    case DOWN: snakeY++; break;
    default: break;
    }

    // Check if the snake hits the wall
    if (snakeX < 0 || snakeX >= WIDTH || snakeY < 0 || snakeY >= HEIGHT)
        gameOver = true;

    // Check if the snake eats itself
    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == snakeX && tailY[i] == snakeY)
            gameOver = true;
    }

    // Check if the snake eats the food
    if (snakeX == foodX && snakeY == foodY) {
        score += 10;
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
        tailLength++;
    }
}

void saveScore(int score) {
    ofstream file("scores.txt", ios::app); // Open file in append mode
    if (file.is_open()) {
        file << "Score: " << score << endl;
        file.close();
    } else {
        cout << "Error: Unable To Open File For Saving Score." << endl;
    }
}

void displayScores() {
    ifstream file("scores.txt");
    if (file.is_open()) {
        string line;
        cout << "Past Scores:" << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "No Scores Found. Play To Add Some!" << endl;
    }
}

void changeDifficulty() {
    int choice;
    cout << "Select Difficulty:" << endl;
    cout << "1. Easy" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Hard" << endl;
    cin >> choice;

    switch (choice) {
    case 1:
        {
            snakeSpeed = 200;
            cout << "Difficulty Set To Easy" ;
            break;
        }
    case 2:
        {
            snakeSpeed = 100;
            cout << "Difficulty Set To Medium" ;
            break;
        }
    case 3:
         {
             snakeSpeed = 50;
             cout << "Difficulty Set To Hard" ;
             break;
         }
    default:
        cout << "Invalid Choice. Keeping Current Difficulty." << endl;
    }
}

void gameOverScreen() {
    cout << "Game Over! Final Score: " << score << endl;
    saveScore(score); // Save the current score at the end of the game
    cout << "Press Any Key To Return to The Main Menu." << endl;
    _getch(); // Wait for user input
}

void mainMenu() {
    int choice;
    do {
        system("cls");
        cout << "====== Snake Game ====" << endl;
        cout << "1. Play Game" << endl;
        cout << "2. See Scores" << endl;
        cout << "3. Change Difficulty" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            initializeGame();
            while (!gameOver) {
                draw();
                input();
                logic();
                Sleep(snakeSpeed);
            }
            gameOverScreen();
            break;
        case 2:
            displayScores();
            cout << "Press Any Key To Return To The Menu." << endl;
            _getch();
            break;
        case 3:
            changeDifficulty();
            break;
        case 4:
            cout << "Exiting Game. Goodbye!" << endl;
            return;
        default:
            cout << "Invalid Choice! Try Again." << endl;
        }
    } while (choice != 4);
}

int main() {
    srand(time(0)); // Seed random number generator
    mainMenu();     // Start the main menu
    return 0;
}

#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>

int carPositionX = 300; // Car's initial X position

// Function to draw the startup screen
void drawStartupScreen() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    if (graphresult() != grOk) {
        printf("Graphics initialization failed.\n");
        exit(1);
    }

    int width = getmaxx();
    int height = getmaxy();

    setbkcolor(CYAN);
    cleardevice();

    setcolor(RED);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 6);
    outtextxy((width - textwidth((char*)"F1 Clash")) / 2, height / 4, (char*)"F1 Clash");

    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
    outtextxy((width - textwidth((char*)"Press any key to start")) / 2, height / 2, (char*)"Press any key to start");

    setcolor(BLACK);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(50, height - 170, (char*)"Instructions:");
    setcolor(LIGHTMAGENTA);
    outtextxy(50, height - 120, (char*)"Press 'A' to move the car left");
    outtextxy(50, height - 90, (char*)"Press 'D' to move the car right");
    outtextxy(50, height - 60, (char*)"Navigate obstacles and score points!");

    getch();
    cleardevice();
}

// Function to draw the track
void drawTrack() {
    setcolor(WHITE);
    line(200, 0, 200, 480);
    line(400, 0, 400, 480);

    for (int i = 0; i < 480; i += 40) {
        line(270, i, 270, i + 20);
        line(330, i, 330, i + 20);
    }
}

// Function to draw the car
void drawCar(int carX, int carY) {
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    bar(carX - 10, carY, carX + 10, carY + 30);
}

// Function to erase the car
void eraseCar(int carX, int carY) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    bar(carX - 15, carY - 2, carX + 15, carY + 32);
}

// Function to draw and erase obstacles
void drawObstacle(int obstacleX, int obstacleY) {
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    bar(obstacleX - 10, obstacleY, obstacleX + 10, obstacleY + 30);
}

void eraseObstacle(int obstacleX, int obstacleY) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    bar(obstacleX - 12, obstacleY - 2, obstacleX + 12, obstacleY + 32);
}

// Display score
void displayScore(int score) {
    setcolor(WHITE);
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);
    outtextxy(420, 10, scoreText);
}

// Game over message
void displayGameOver(int score) {
    setcolor(RED); // Set the text color to red

    // Set the text style with a large font size
    settextstyle(BOLD_FONT, HORIZ_DIR, 5);

    char scoreText[50]; // Buffer to store the final score text
    sprintf(scoreText, "Game Over! Final Score: %d", score);

    // Get the width and height of the text
    int textWidth = textwidth(scoreText);   // Width of the text
    int textHeight = textheight(scoreText); // Height of the text

    // Get the screen dimensions
    int width = getmaxx();  // Width of the screen
    int height = getmaxy(); // Height of the screen

    // Calculate the position to center the text
    int x = (width - textWidth) / 2;        // Center horizontally
    int y = (height - textHeight) / 2;      // Center vertically

    // Display the "Game Over" text at the calculated position
    outtextxy(x, y, scoreText);
}


int main() {
    drawStartupScreen();

    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int score = 0, obstacleX = 250, obstacleY = 0;
    char inputKey;
    drawTrack();
    drawCar(carPositionX, 400);
    drawObstacle(obstacleX, obstacleY);

    while (1) {
        displayScore(score);

        eraseObstacle(obstacleX, obstacleY);
        obstacleY += 10;

        if (obstacleY > 480) {
            obstacleY = 0;
            obstacleX = 220 + (rand() % 160);
            score++;
        }

        if (obstacleY + 30 >= 400 && obstacleY <= 430 &&
            obstacleX + 10 >= carPositionX - 10 &&
            obstacleX - 10 <= carPositionX + 10) {
            cleardevice();
            displayGameOver(score);
            getch();
            break;
        }

        drawObstacle(obstacleX, obstacleY);
        drawTrack();

        if (kbhit()) {
            inputKey = getch();
            if (inputKey == 'a' || inputKey == 'A') {
                if (carPositionX > 220) {
                    eraseCar(carPositionX, 400);
                    carPositionX -= 20;
                    drawCar(carPositionX, 400);
                }
            } else if (inputKey == 'd' || inputKey == 'D') {
                if (carPositionX < 380) {
                    eraseCar(carPositionX, 400);
                    carPositionX += 20;
                    drawCar(carPositionX, 400);
                }
            } else if (inputKey == 27) {
                cleardevice();
                displayGameOver(score);
                getch();
                break;
            }
        }
        delay(40);
    }

    closegraph();
    return 0;
}

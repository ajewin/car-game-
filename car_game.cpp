#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define LANE_COUNT 4
#define MAX_OBSTACLES 3

struct Car {
    int lane;
    float y;
};

int screenWidth, screenHeight;
int laneWidth;
int carWidth = 50;
int carHeight = 80;
int score = 0;
float speed = 5.0f;

void drawRoad() {
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(0, 0, screenWidth, screenHeight);

    setcolor(WHITE);
    setlinestyle(DASHED_LINE, 0, 1);
    for (int i = 1; i < LANE_COUNT; i++) {
        int x = i * laneWidth;
        line(x, 0, x, screenHeight);
    }
    setlinestyle(SOLID_LINE, 0, 1);
}

// Draw a stylized 2D car with slightly curved corners and windshield
void drawPixelCar(int lane, int y, int colorBody, bool isPlayer = false) {
    int x = lane * laneWidth + (laneWidth - carWidth) / 2;

    // Car body
    int bodyTop = y + 25;
    int bodyBottom = y + 65;
    int bodyLeft = x + 10;
    int bodyRight = x + 40;

    setfillstyle(SOLID_FILL, colorBody);
    bar(bodyLeft, bodyTop, bodyRight, bodyBottom);

    // Curved corners (small ellipses)
    fillellipse(bodyLeft, bodyTop, 3, 3);
    fillellipse(bodyRight, bodyTop, 3, 3);
    fillellipse(bodyLeft, bodyBottom, 3, 3);
    fillellipse(bodyRight, bodyBottom, 3, 3);

    // Tires
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x + 7, y + 60, 3, 6);
    fillellipse(x + 7, y + 40, 3, 6);
    fillellipse(x + 43, y + 60, 3, 6);
    fillellipse(x + 43, y + 40, 3, 6);

    // Windshield
    setcolor(BLACK);
    if (isPlayer) {
        setfillstyle(SOLID_FILL, LIGHTCYAN);
        bar(x + 20, y + 27, x + 30, y + 42);
    } else {
        setfillstyle(SOLID_FILL, CYAN);
        bar(x + 20, y + 47, x + 30, y + 62);
    }
}

bool checkCollision(Car obs, int playerY, int playerLane) {
    return (obs.lane == playerLane) &&
           (obs.y + carHeight > playerY) &&
           (obs.y < playerY + carHeight);
}

bool isOverlap(Car obstacles[], int idx) {
    for (int i = 0; i < idx; i++) {
        if (obstacles[i].lane == obstacles[idx].lane) {
            int dist = abs((int)(obstacles[i].y - obstacles[idx].y));
            if (dist < carHeight + 100) return true;
        }
    }
    return false;
}

void showMenu() {
    cleardevice();
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(screenWidth / 2 - 100, screenHeight / 2 - 60, (char*)"CAR GAME");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(screenWidth / 2 - 130, screenHeight / 2, (char*)"Press ENTER to Start");
    outtextxy(screenWidth / 2 - 130, screenHeight / 2 + 40, (char*)"Press ESC to Exit");
}

bool showGameOver(int score) {
    cleardevice();
    setcolor(RED);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(screenWidth / 2 - 100, screenHeight / 2 - 60, (char*)"GAME OVER");
    setcolor(WHITE);
    char finalScore[30];
    sprintf(finalScore, "Your Score: %d", score);
    outtextxy(screenWidth / 2 - 100, screenHeight / 2 - 10, finalScore);
    outtextxy(screenWidth / 2 - 150, screenHeight / 2 + 30, (char*)"Press R to Retry");
    outtextxy(screenWidth / 2 - 150, screenHeight / 2 + 70, (char*)"Press ESC to Exit");

    while (true) {
        if (kbhit()) {
            int ch = getch();
            if (ch == 0) ch = getch();
            if (ch == 'r' || ch == 'R') return true;
            else if (ch == 27) return false;
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    screenWidth = getmaxx();
    screenHeight = getmaxy();
    laneWidth = screenWidth / LANE_COUNT;

    bool running = true;
    while (running) {
        showMenu();

        // Wait for input to start or exit
        while (true) {
            if (kbhit()) {
                int ch = getch();
                if (ch == 0) ch = getch();

                if (ch == 13) break;       // ENTER to start
                else if (ch == 27) {       // ESC to exit
                    closegraph();
                    return 0;
                }
            }
        }

        int activePage = 0;
        int playerLane = LANE_COUNT / 2;
        int playerY = screenHeight - carHeight - 20;
        score = 0;
        speed = 5.0f;

        Car obstacles[MAX_OBSTACLES];
        srand(time(0));

        for (int i = 0; i < MAX_OBSTACLES; i++) {
            do {
                obstacles[i].lane = rand() % LANE_COUNT;
                obstacles[i].y = - (rand() % 600 + i * 200);
            } while (isOverlap(obstacles, i));
        }

        bool gameOver = false;

        while (!gameOver) {
            setactivepage(activePage);
            cleardevice();

            drawRoad();

            if (kbhit()) {
                int ch = getch();
                if (ch == 0) ch = getch();

                if (ch == 75) {  // Left arrow
                    if (playerLane == 0)
                        playerLane = LANE_COUNT - 1;  // Wrap to rightmost lane
                    else
                        playerLane--;
                } else if (ch == 77) {  // Right arrow
                    if (playerLane == LANE_COUNT - 1)
                        playerLane = 0;  // Wrap to leftmost lane
                    else
                        playerLane++;
                } else if (ch == 72 && playerY > 10) {
                    playerY -= 15;  // Up arrow
                } else if (ch == 80 && playerY + carHeight < screenHeight - 10) {
                    playerY += 15;  // Down arrow
                }
            }

            drawPixelCar(playerLane, playerY, GREEN, true);

            for (int i = 0; i < MAX_OBSTACLES; i++) {
                drawPixelCar(obstacles[i].lane, (int)obstacles[i].y, RED, false);
                obstacles[i].y += speed;

                if (checkCollision(obstacles[i], playerY, playerLane)) {
                    gameOver = true;
                }

                if (obstacles[i].y > screenHeight) {
                    do {
                        obstacles[i].lane = rand() % LANE_COUNT;
                        obstacles[i].y = - (rand() % 300 + 200);
                    } while (isOverlap(obstacles, i));

                    score++;
                    if (score % 5 == 0 && speed < 30) speed += 0.5f;
                }
            }

            setcolor(WHITE);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            char scoreText[30];
            sprintf(scoreText, "Score: %d", score);
            outtextxy(20, 20, scoreText);

            setvisualpage(activePage);
            activePage = 1 - activePage;

            delay(30);
        }

        bool retry = showGameOver(score);
        if (!retry) running = false;
    }

    closegraph();
    return 0;
}


#include <graphics.h>
#include <conio.h>

void draw_road() {
    setcolor(WHITE);
    line(0, 0, 0, 480);       // Left border
    line(160, 0, 160, 480);   // Lane 1 divider
    line(320, 0, 320, 480);   // Lane 2 divider
    line(480, 0, 480, 480);   // Right border
}

void draw_car_blue() {
    setcolor(BLUE);
    rectangle(170, 400, 210, 460);  // Car body outline

    setcolor(WHITE);
    circle(170, 410, 6);  // Tyres
    circle(210, 410, 6);
    circle(170, 450, 6);
    circle(210, 450, 6);

    // Roof base (filled rectangle) — now blue
    setfillstyle(SOLID_FILL, BLUE);
    bar(175, 425, 205, 450);

    // Small horizontal roof detail — also blue
    setfillstyle(SOLID_FILL, BLUE);
    bar(179, 408, 201, 418);
}

void draw_car_red() {
    setcolor(RED);
    rectangle(20, 100, 60, 160); // Car body outline

    setcolor(WHITE);
    circle(20, 110, 6);  // Tyres
    circle(60, 110, 6);
    circle(20, 150, 6);
    circle(60, 150, 6);

    // Roof base (filled rectangle)
    setfillstyle(SOLID_FILL, RED);
    bar(25, 110, 55, 135);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    setbkcolor(BLACK);
    cleardevice();

    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(100, 200, (char*)"Press ENTER to Start...");

    while (true) {
        char key = getch();
        if (key == 13) break;  // Enter key
    }

    cleardevice();
    draw_road();
    draw_car_blue();
    draw_car_red();

    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(10, 10, (char*)"Score: 0");

    getch();
    closegraph();
    return 0;
}

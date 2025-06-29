#include <graphics.h>
#include <conio.h>

void draw_road() {
    setcolor(WHITE);
    line(0, 0, 0, 480);
    line(120, 0, 120, 480);
    line(240, 0, 240, 480);
    line(360, 0, 360, 480);
    line(480, 0, 480, 480);
}

void draw_car(int x, int y, int color, int windowFace) {
    setcolor(color);
    rectangle(x, y, x + 40, y + 60);
    setcolor(WHITE);
    circle(x, y + 6, 6);
    circle(x + 40, y + 6, 6);
    circle(x, y + 54, 6);
    circle(x + 40, y + 54, 6);
    if (windowFace == 1) {
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        bar(x + 10, y + 5, x + 30, y + 20);
    } else if (windowFace == 2) {
        setfillstyle(SOLID_FILL, RED);
        bar(x + 12, y + 15, x + 28, y + 45);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
    setbkcolor(BLACK);
    cleardevice();
    draw_road();
    draw_car(130, 400, BLUE, 1);
    draw_car(20, 100, RED, 2);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(10, 10, (char*)"Score: 0");
    getch();
    closegraph();
    return 0;
}

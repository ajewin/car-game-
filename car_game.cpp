#include <graphics.h>
#include <conio.h>

void draw_road() {
    setcolor(WHITE);
    line(0, 0, 0, 480);       // Left border
    line(160, 0, 160, 480);   // Lane 1 divider
    line(320, 0, 320, 480);   // Lane 2 divider
    line(480, 0, 480, 480);   // Right border
}

void draw_car_blue(int x=0,int y=0) {
    setcolor(BLUE);
    rectangle(170+x, 400+y, 210+x, 460+y);  // Car body outline

    setcolor(WHITE);
    circle(170+x, 410+y, 6);  // Tyres
    circle(210+x, 410+y, 6);
    circle(170+x, 450+y, 6);
    circle(210+x, 450+y, 6);

    // Roof base (filled rectangle) — now blue
    setfillstyle(SOLID_FILL, WHITE);
    bar(175+x, 425+y, 205+x, 450+y);

    // Small horizontal roof detail — also blue
    setfillstyle(SOLID_FILL, RED);

    // 2-dimensional, rectangular filled in ba
    bar(179+x, 408+y, 201+x, 418+y);
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

void car_control(int key,int &car_x, int &car_y, int step){
    // left arrow: 37
    // up arrow: 38
    // right arrow: 39
    // down arrow: 40
            if (key == 37) car_x -= step;
            else if (key == 39) car_x += step;
            else if (key == 38) car_y -= step;
            else if (key == 40) car_y += step;
        //clear the screen
        // redraw the road
        // redraw the car in the new position
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

    int car_pos_x = 0;
    int car_pos_y = 0;
    int step = 50;
    while (true) {
        // Check key press
        if (kbhit()) {
            char key = getch();
             if (key == 27) {
                break;
            }
            car_control(key,car_pos_x, car_pos_y, step);
                    
            cleardevice();
            draw_road();
            draw_car_blue(car_pos_x,car_pos_y);
            draw_car_red();

            delay(100); //fix continuos flickering
        }
    }
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(10, 10, (char*)"Score: 0");

    getch();
    closegraph();
    return 0;
}

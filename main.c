#include "raylib.h"
#include <math.h>

#define WIDTH  800
#define HEIGHT 600

#define SUN_R 50
#define RAY_N 150

// object
#define X (WIDTH*3/4)
#define Y (HEIGHT/2)
#define R 60

void DrawSun(double x, double y) {
    DrawCircle(x, y, SUN_R, GOLD);
}

void DrawObject() {
    DrawCircle(X, Y, R, WHITE);
}

void DrawLight(double x, double y, double theta, Color color) {
    for (int i = 0; ; ++i) {
        x += cos(theta);
        y += sin(theta);

        if (x < 0 || x > WIDTH) return;
        if (y < 0 || y > HEIGHT) return;

        if (pow((x-X), 2) + pow((y-Y), 2) < pow(R, 2)) return;

        if (color.a < 1) return;

        DrawPixel(x, y, color);
        if (i & 1) color.a *= 0.9999;
    }
}

void DrawLights(double cx, double cy) {
    double delta = 2*M_PI / RAY_N;
    double theta = delta / 2;
    for (int i = 0; i < RAY_N; ++i) {
        theta += delta;
        double x = cx + SUN_R*cos(theta);
        double y = cy + SUN_R*sin(theta);
        DrawLight(x, y, theta, YELLOW);
    }

    theta = 0;
    for (int i = 0; i < RAY_N; ++i) {
        theta += delta;
        double x = cx + (SUN_R - 1)*cos(theta);
        double y = cy + (SUN_R - 1)*sin(theta);
        DrawLight(x, y, theta, WHITE);
    }
}

int main() {
    Vector2 pos;

    InitWindow(WIDTH, HEIGHT, "SUN LIGHT");
    SetTargetFPS(60);
  
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        pos = GetMousePosition();
        double x = pos.x;
        double y = pos.y;

        DrawObject();
        DrawSun(x, y);
        DrawLights(x, y);

        DrawFPS(0, 0);

        EndDrawing();
    }
  
    CloseWindow();
    return 0;
}
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <cmath>

#define WIDTH 800
#define HEIGHT 600
#define SCALE 20
#define GRAVITY 9.8f

float cosd(float degrees) {
    return std::cosf(degrees * M_PI / 180.0f);
}

float sind(float degrees) {
    return std::sinf(degrees * M_PI / 180.0f);
}
float tand(float degrees) {
    return std::tanf(degrees * M_PI / 180.0f);
}

class Object {
    public:
    //initial variables
    Vector2 Position;
    float Force; // m/s
    float InitialAngle; // Degrees
    //Variables
    float T;
    float range;
    float maxHeight;
    float VelocityX;
    float VelocityY;
    //Constructor
    Object (Vector2 Position,float Force, float initialAngle) {
        this->Position = Position;
        this->Force = Force;
        this->InitialAngle = initialAngle;
    }
    //Get all the values, should be executed in the Update func
    void CalculateValues() {
        VelocityX = Force * cosd(InitialAngle);
        VelocityY = Force * sind(InitialAngle);
        T = (2 * Force * sind(InitialAngle)) / GRAVITY;
        range = VelocityX * T;
        maxHeight = (VelocityY * VelocityY) / (2*GRAVITY);

    }
    //Calculates and displays the trajectory
    void Update() {
        CalculateValues();
        for (float x = 0; x < 10;) {
            float x_world = VelocityX * x;
            float y_world = VelocityY * x - 0.5f * GRAVITY * x * x;

            float x_screen = Position.x + (x_world * SCALE);
            float y_screen = Position.y - (y_world * SCALE);
            if (y_screen <= HEIGHT) {
                DrawCircle(x_screen, y_screen, 1, RED);
                DrawCircle(Position.x, Position.y, 50, BLUE);
                x = x + 0.001;
                continue;
            }
            return;

        }
    }
    // Creates 2 sliders and sets one for the force and one for the angle
    void GetValues() {

        GuiSlider(
            (Rectangle){50,50,200,20},
            "Force:",
            TextFormat("%.2f", Force),
            &Force,
            0,
            100);
        GuiSlider(
            (Rectangle){50,10,200,20},
            "Angle: ",
            TextFormat("%.2f", InitialAngle),
            &InitialAngle,
            0,
            90
        );
    }
    void ShowValues() {
        std::string AngleString = "Angle: " + std::to_string(InitialAngle) + "°";
        std::string VelocityXString = "VelocityX: " + std::to_string(VelocityX) + "M/s";
        std::string VelocityYString = "VelocityY: " + std::to_string(VelocityY) + "M/s";
        std::string MaxHeightString = "Max Height: " + std::to_string(maxHeight) + "M";
        std::string RangeString = "Range: " + std::to_string(range) + "M";
        std::string TimeString = "Time: " + std::to_string(T) + "S";
        DrawText(VelocityXString.c_str(),50,100, 16, BLACK);
        DrawText(VelocityYString.c_str(),50,125, 16, BLACK);
        DrawText(AngleString.c_str(),50,150, 16, BLACK);
        DrawText(MaxHeightString.c_str(),50,175, 16, BLACK);
        DrawText(RangeString.c_str(),50,200, 16, BLACK);
        DrawText(TimeString.c_str(),50,225, 16, BLACK);
    }
    //Debug function: displays in the terminal all the variables that gets calculated
    void ShowCalcs() {
        float VelocityX = Force * cosd(InitialAngle);
        float VelocityY = Force * sind(InitialAngle);
        T = (2 * Force * sind(InitialAngle)) / GRAVITY;
        float maxHeight = (VelocityY * VelocityY) / (2*GRAVITY);
        range = VelocityX * T;
        std::cout << "Max time: " << T << "\n";
        std::cout << "Max height: " << maxHeight << "\n";
        std::cout << "Force: " << Force << " Angle: " << InitialAngle << std::endl;
        std::cout << "VelocityX: " << VelocityX << " VelocityY: " << VelocityY << std::endl;
    }
};



int main() {

    InitWindow(WIDTH, HEIGHT, "Trayectory");

    Object obj = Object({100,500}, 0, 0);

    while (!WindowShouldClose()) {
        obj.GetValues();
        obj.CalculateValues();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        obj.Update();
        obj.ShowValues();
        EndDrawing();
    }
    return 0;

}
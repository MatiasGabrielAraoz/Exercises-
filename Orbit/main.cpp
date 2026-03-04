#define RAYGUI_IMPLEMENTATION
#include "vcpkg_installed/x64-linux/include/raygui.h"
#include "vcpkg_installed/x64-linux/include/raylib.h"
#include "vcpkg_installed/x64-linux/include/raymath.h"
#include <iostream>
#include <raylib.h>
#define GRAVITATIONALCONSTANT 6.67430e-5

struct Object {
  Vector2 position;
  Vector2 acceleration;
  float radius;
  float mass;
  Vector2 direction;
  Vector2 velocity;
  Object(Vector2 position, Vector2 acceleration, float radius, float mass) {
    this->position = position;
    this->acceleration = acceleration;
    this->radius = radius;
    this->mass = mass;
  }

  void Draw() { DrawCircleV(position, radius, GREEN); }

  void CalculateAttraction(Object *obj2, float deltaTime,
                           float simulationSpeed) {
    float distanceSqr = Vector2DistanceSqr(position, obj2->position);
    if (distanceSqr < 0.001f)
      return;

    float force = (GRAVITATIONALCONSTANT * mass * obj2->mass) / distanceSqr;

    Vector2 direction = Vector2Subtract(obj2->position, position);
    direction = Vector2Normalize(direction);

    Vector2 acceleration = {(direction.x * force) / mass,
                            (direction.y * force) / mass};
    float adjustedDeltaTime = deltaTime * simulationSpeed;

    velocity.x += acceleration.x * adjustedDeltaTime;
    velocity.y += acceleration.y * adjustedDeltaTime;
    position.x += velocity.x * adjustedDeltaTime;
    position.y += velocity.y * adjustedDeltaTime;

    // std::cout << "acceleration: " << acceleration.x
    //           << "\n positionX: " << position.x << "\n positionY" <<
    //           position.y
    //           << "\n";
  }
};

float SpeedSlider(float speed) {

  GuiSliderBar(Rectangle{10, 20, 100, 20},
               "Simulation speed: ", TextFormat("%0.2f", speed), &speed, 0.01,
               100);
  std::cout << speed;

  return speed;
}

int main() {
  InitWindow(640, 480, "raylib window");

  float simulationSpeed = 1.0f;

  Object obj = Object({500, 240}, {-1, 10}, 15, 10);
  Object orbitObj = Object({320, 240}, {0, 0}, 50, 100000000);

  float orbitalDistance = Vector2Distance(obj.position, orbitObj.position);
  float orbitalSpeed =
      sqrt((GRAVITATIONALCONSTANT * orbitObj.mass) / orbitalDistance);

  Vector2 radialDir = Vector2Subtract(orbitObj.position, obj.position);
  radialDir = Vector2Normalize(radialDir);

  obj.velocity = {-radialDir.y * orbitalSpeed, radialDir.x * orbitalSpeed};

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    float deltatime = GetFrameTime();
    obj.CalculateAttraction(&orbitObj, deltatime, simulationSpeed);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    simulationSpeed = SpeedSlider(simulationSpeed);
	
    obj.Draw();
    orbitObj.Draw();
    EndDrawing();
  }
}

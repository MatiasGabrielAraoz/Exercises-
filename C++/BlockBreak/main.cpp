#include "raylib.h"
#include "raymath.h"
#include <vector>

enum class GameState {
    PLAYING,
    CINEMATIC
};

enum class StepType {
    MOVE,
    WAIT
};

struct CinematicStep {
    StepType type;
    Vector2 target;
    float duration = 0.0f;
};

struct Player {
    Vector2 position;
    float speed = 100.0f;

    void Update(float dt) {
        if (IsKeyDown(KEY_RIGHT)) position.x += speed * dt;
        if (IsKeyDown(KEY_LEFT))  position.x -= speed * dt;
    }

    void Draw() {
        DrawRectangleV(position, {32, 32}, BLUE);
    }
};

struct Cinematic {
    std::vector<CinematicStep> steps;
    int currentStep = 0;
    float timer = 0.0f;
    bool finished = false;

    void Update(Player& player, float dt) {
        if (finished || currentStep >= steps.size()) {
            finished = true;
            return;
        }

        CinematicStep& step = steps[currentStep];

        switch (step.type) {
            case StepType::MOVE: {
                Vector2 dir = {
                    step.target.x - player.position.x,
                    step.target.y - player.position.y
                };

                float distance = Vector2Length(dir);

                if (distance < 2.0f) {
                    player.position = step.target;
                    currentStep++;
                } else {
                    dir = Vector2Normalize(dir);
                    player.position.x += dir.x * player.speed * dt;
                    player.position.y += dir.y * player.speed * dt;
                }
            } break;

            case StepType::WAIT:
                timer += dt;
                if (timer >= step.duration) {
                    timer = 0.0f;
                    currentStep++;
                }
                break;
        }
    }
};

int main() {
    InitWindow(800, 450, "Cinematica simple - raylib");
    SetTargetFPS(60);

    Player player;
    player.position = {100, 300};

    Cinematic cinematic;
    cinematic.steps = {
        { StepType::MOVE, {400, 300}},
        { StepType::WAIT, {0, 0}, 1.0f }
    };

    GameState gameState = GameState::CINEMATIC;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (gameState == GameState::CINEMATIC) {
            cinematic.Update(player, dt);
            if (cinematic.finished)
                gameState = GameState::PLAYING;
        } else {
            player.Update(dt);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        player.Draw();

        if (gameState == GameState::CINEMATIC)
            DrawText("CINEMATICA", 10, 10, 20, RED);
        else
            DrawText("JUGANDO", 10, 10, 20, GREEN);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
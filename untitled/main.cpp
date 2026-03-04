#include <raylib.h>

#define WIDTH 800
#define HEIGHT 600
#define gridSize 5

enum Type { Dust, Solid, Fluid, Nothing };
class Grid {
public:
  static const int gridWidth = WIDTH / gridSize;
  static const int gridHeight = HEIGHT / gridSize;
  enum Type grid[gridWidth][gridHeight];

  enum Type type;

  Grid(enum Type type) { this->type = type; }

  void ClearGrid() {
    for (int i = 0; i < WIDTH / gridSize; i++) {
      for (int j = 0; j < HEIGHT / gridSize; j++) {
        grid[i][j] = Nothing;
      }
    }
  }

  void DrawGrid() {
    for (int i = 0; i < gridWidth; i++) {
      for (int j = 0; j < gridHeight; j++) {
        DrawRectangleLines(i * gridSize, j * gridSize, gridSize, gridSize,
                           GRAY);

        if (grid[i][j] == Dust) {
          DrawRectangle(i * gridSize, j * gridSize, gridSize, gridSize, MAROON);
        } else if (grid[i][j] == Solid) {
          DrawRectangle(i * gridSize, j * gridSize, gridSize, gridSize, BLACK);
        } else if (grid[i][j] == Fluid) {
          DrawRectangle(i * gridSize, j * gridSize, gridSize, gridSize, BLUE);
        }
      }
    }
  }
  void UpdateGrid() {
    enum Type newGrid[gridWidth][gridHeight];
    for (int y = 0; y < gridHeight; y++) {
      for (int x = 0; x < gridWidth; x++) {
        newGrid[x][y] = grid[x][y];
      }
    }

    for (int y = gridHeight - 2; y >= 0; y--) {
      for (int x = 0; x < gridWidth; x++) {
        newGrid[x][y] = grid[x][y];
        if (grid[x][y] == Dust) {
          if (grid[x][y + 1] == Nothing) {
            newGrid[x][y] = Nothing;
            newGrid[x][y + 1] = Dust;
          } else {
            bool tryfirst = GetRandomValue(0, 1) == 0;
            if (tryfirst) {
              if (newGrid[x + 1][y + 1] == Nothing &&
                  newGrid[x + 1][y] == Nothing) {
                newGrid[x + 1][y + 1] = Dust;
                newGrid[x][y] = Nothing;
              }
            }
            if (!tryfirst) {
              if (newGrid[x - 1][y + 1] == Nothing &&
                  newGrid[x - 1][y] == Nothing) {
                newGrid[x - 1][y + 1] = Dust;
                newGrid[x][y] = Nothing;
              }
            }

            else
              continue;
          }
        } else if (grid[x][y] == Solid) {
          // Do nothing, is static
        } else if (grid[x][y] == Fluid) {
          // Misma lógica que Dust pero con comportamiento de fluido
          if (grid[x][y + 1] == Nothing) {
            newGrid[x][y] = Nothing;
            newGrid[x][y + 1] = Fluid;
          } else {
            bool tryfirst = GetRandomValue(0, 1) == 0;

            if (tryfirst) {
              // Intentar derecha primero (diagonal abajo-derecha)
              if (x < gridWidth - 1 && grid[x + 1][y + 1] == Nothing) {
                newGrid[x][y] = Nothing;
                newGrid[x + 1][y + 1] = Fluid;
              }
              // Si no puede diagonal derecha, intentar horizontal derecha
              else if (x < gridWidth - 1 && grid[x + 1][y] == Nothing) {
                newGrid[x][y] = Nothing;
                newGrid[x + 1][y] = Fluid;
              }
              // Si no puede derecha, intentar izquierda (diagonal
              // abajo-izquierda)
              else if (x > 0 && grid[x - 1][y + 1] == Nothing) {
                newGrid[x][y] = Nothing;
                newGrid[x - 1][y + 1] = Fluid;
              }
              // Si no puede diagonal izquierda, intentar horizontal izquierda
              else if (x > 0 && grid[x - 1][y] == Nothing) {
                newGrid[x][y] = Nothing;
                newGrid[x - 1][y] = Fluid;
              }
            } else {
              // Intentar izquierda primero (diagonal abajo-izquierda)
              if (x > 0 && grid[x - 1][y + 1] == Nothing) {
                newGrid[x][y] = Nothing;
                newGrid[x - 1][y + 1] = Fluid;
              }
              // Si no puede diagonal izquierda, intentar horizontal izquierda
              else if (x > 0 && grid[x - 1][y] == Nothing) {
                newGrid[x][y] = Nothing;
                newGrid[x - 1][y] = Fluid;
              }
              // Si no puede izquierda, intentar derecha (diagonal
              // abajo-derecha)
              else if (x < gridWidth - 1 && grid[x + 1][y + 1] == Nothing) {
                newGrid[x][y] = Nothing;
                newGrid[x + 1][y + 1] = Fluid;
              }
              // Si no puede diagonal derecha, intentar horizontal derecha
              else if (x < gridWidth - 1 && grid[x + 1][y] == Nothing) {
                newGrid[x][y] = Nothing;
                newGrid[x + 1][y] = Fluid;
              }
            }
          }
        }
      }
    }
    for (int x = 0; x < WIDTH / gridSize; x++) {
      for (int y = 0; y < HEIGHT / gridSize; y++) {
        grid[x][y] = newGrid[x][y];
      }
    }
  }
};

int main() {
  InitWindow(WIDTH, HEIGHT, "raylib");
  SetTargetFPS(60);
  Grid grid = Grid(Dust);
  grid.ClearGrid();

  while (!WindowShouldClose()) {

    grid.UpdateGrid();
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {

      Vector2 mousePos = GetMousePosition();
      int x = mousePos.x;
      int y = mousePos.y;
      int col = y / gridSize;
      int row = x / gridSize;

      // if (row >= 0 && row < WIDTH/gridSize && col >= 0 && col <
      // HEIGHT/gridSize ) {
      grid.grid[row][col] = grid.type;
      //}
    }
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
      Vector2 mousePos = GetMousePosition();
      int x = mousePos.x;
      int y = mousePos.y;
      int col = y / gridSize;
      int row = x / gridSize;
      grid.grid[row][col] = Nothing;
    }
    if (IsKeyPressed(KEY_R)) {
      grid.ClearGrid();
    }
    if (IsKeyPressed(KEY_ONE)) {
      grid.type = Solid;
    }
    if (IsKeyPressed(KEY_TWO)) {
      grid.type = Dust;
    }
    if (IsKeyPressed(KEY_THREE)) {
      grid.type = Fluid;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    grid.DrawGrid();

    EndDrawing();
  }
}

#include "raylib.h"
#include "raymath.h"
#include <cstddef>


#define WIDTH 800
#define HEIGHT 600
#define GRAVITY 1500

float sind(float degrees){
	return sin(degrees * PI/180 );
}
float cosd(float degrees){
	return cos(degrees * PI/180 );
}

class Pendulum{
	public:
	float length;
	float angle;
	float angularSpeed;
	float angularAcceleration;
	Vector2 origin;
	bool isRoot;

	Pendulum(float length, Vector2 origin, float angle, bool isRoot = true ){
		this->origin = origin;
		this->length = length;
		this->angle = angle;
		this->isRoot = isRoot;
	}

	void Update(float dt, Pendulum* father = nullptr ){
		angularAcceleration = -1 * (GRAVITY/length) * sind(angle);
		angularSpeed += angularAcceleration * dt;
		angle += angularSpeed * dt;
		if (isRoot){return;}	
		if (father != nullptr){
			origin.x = father->origin.x + father->length * sind(father->angle);
			origin.y = father->origin.y + father->length * cosd(father->angle);
		}
	}

	void Draw(){
		float x = origin.x + length * sind(angle);
		float y = origin.y + length * cosd(angle);

		DrawLineV(origin, (Vector2){x,y}, RED);
		DrawCircleV((Vector2){x,y}, 10.0f, RED);
	}
};


int main(){

	InitWindow(WIDTH, HEIGHT, "Pendulum");

	Pendulum pendulum1 = Pendulum(100, {WIDTH/2,HEIGHT/2}, 170, true);
	Pendulum pendulum2 = Pendulum(100, {WIDTH/3,HEIGHT/3}, 90, false);


	SetTargetFPS(60);
	while(!WindowShouldClose()){
		float dt = GetFrameTime();

		pendulum1.Update(dt);
		pendulum2.Update(dt, &pendulum1);


		BeginDrawing();
		ClearBackground(WHITE);

		pendulum1.Draw();
		pendulum2.Draw();

		EndDrawing();

	}


	
}

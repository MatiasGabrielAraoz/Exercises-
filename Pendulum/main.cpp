#include "raylib.h"
#include "raymath.h"


#define WIDTH 800
#define HEIGHT 600
#define GRAVITY 9800

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

	Pendulum(float length, Vector2 origin, float angle ){
		this->origin = origin;
		this->length = length;
		this->angle = angle;
	}

	void Update(float dt){
		
		angularAcceleration = -(GRAVITY/length) * sind(angle);
		angularSpeed += angularAcceleration * dt;
		angle += angularSpeed * dt;
	}

	void Draw(){
		float x = origin.x + length * sind(angle);
		float y = origin.y + length * cosd(angle);

		DrawLineV(origin, (Vector2){x,y}, RED);
	}
};


int main(){

	InitWindow(WIDTH, HEIGHT, "Pendulum");

	Pendulum pendulum1 = Pendulum(100, {500,500}, 90);


	SetTargetFPS(60);
	while(!WindowShouldClose()){
		float dt = GetFrameTime();

		pendulum1.Update(dt);

		BeginDrawing();
		ClearBackground(WHITE);

		pendulum1.Draw();

		EndDrawing();

	}


	
}

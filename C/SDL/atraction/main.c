#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL.h>
#include <math.h>

#define GRAVITATIONAL_CONSTANT 6.67

SDL_Window* window;
SDL_Renderer* renderer;

typedef struct {
	float x;
	float y;
} Vector2;

typedef struct {
	SDL_Point position;
	float mass;
	Vector2 velocity;


} Body;

typedef struct {
	Body* bodies;
} AppData;

float GetDistanceSquared(Body* this, Body* other){
	// d² = (x2 - x1)² + (y2 - y1)²
	return pow(other->position.x - this->position.x, 2) + pow(other->position.y - this->position.y, 2);	
}

float GetForce(Body* this, Body* other){
	// F = G * ( (m1 * m2) / d² )
	float distanceSquared = GetDistanceSquared(this, other);
	return GRAVITATIONAL_CONSTANT * ((this->mass * other->mass) / distanceSquared);
}

float GetVelocity(float force, )

// SDL_Point GetNextPosition(Body* this, Body* other){
//
// }

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv){

	if(!SDL_Init(SDL_INIT_VIDEO)){ SDL_Log("Error inicializando sdl: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	if(!SDL_CreateWindowAndRenderer("Atraction", 800, 600, SDL_WINDOW_RESIZABLE, &window, &renderer)){
		SDL_Log("Error inicializando ventana y renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	AppData* data = (AppData*)SDL_malloc(sizeof(AppData));
	data->bodies = (Body*) SDL_calloc(2, sizeof(Body));

	*appstate = data;
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate,SDL_Event *event){
	if (event->type == SDL_EVENT_QUIT){
		return SDL_APP_SUCCESS;
	} 

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate){

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result){
	AppData* appData = (AppData*) appstate;
	SDL_free(appData->bodies);
	SDL_free(appData);
	
	return;
}

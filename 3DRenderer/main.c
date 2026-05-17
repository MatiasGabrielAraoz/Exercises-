#include <SDL3/SDL_pixels.h>
#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL_main.h>
#include <SDL3/SDL_clipboard.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>
#include <stdlib.h>
#include <wchar.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

typedef struct{
	float x;
	float y;
}Vector2;

bool Vector2IsEqual(Vector2 v1, Vector2 v2){
	return 
		v1.x == v2.x &&
		v1.y == v2.y;
}

typedef struct{
	float x;
	float y;
	float z;
}Vector3;

bool Vector3IsEqual(Vector3 v1, Vector3 v2){
	return 
		v1.x == v2.x &&
		v1.y == v2.y &&
		v1.z == v2.z;
}

typedef struct{
	float scale;
	Vector2 windowSize;
	Vector2 lastWindowSize;
	SDL_FPoint* points;
	int amountPoints;
	
}AppData;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char* argv[]){
	if (!SDL_Init(SDL_INIT_VIDEO)){
		SDL_Log("Error starting video: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	if (!SDL_CreateWindowAndRenderer("3DWindow", 800, 600,  SDL_WINDOW_RESIZABLE, &window, &renderer)){
		SDL_Log("Error starting window and renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	AppData* data = (AppData*)SDL_calloc(1, sizeof(AppData));

	data->amountPoints = 4;
	SDL_FPoint* points = SDL_calloc(data->amountPoints, sizeof(SDL_FPoint));

	points[0] = (SDL_FPoint){1, 1};
	points[1] = (SDL_FPoint){2, 1};
	points[2] = (SDL_FPoint){2, 2};
	points[3] = (SDL_FPoint){1, 2};
	
	data->points = points;
	data->scale = 50.0f;

	*appstate = data;
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event* event){
	if (event->type == SDL_EVENT_QUIT){
		return SDL_APP_SUCCESS;
	}
	
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate){
	AppData* data = (AppData*)appstate;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE_FLOAT);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE_FLOAT);
	for (int i = 1; i < data->amountPoints; i++){
		SDL_RenderLine(renderer,  data->points[i].x * data->scale, data->points[i].y * data->scale, data->points[i-1].x * data->scale, data->points[i-1].y * data->scale);
	}

	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result){
	AppData* data = (AppData*)appstate;
	SDL_free(data->points);
	SDL_free(data);

}

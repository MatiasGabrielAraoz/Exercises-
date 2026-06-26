#define SDL_MAIN_USE_CALLBACKS 1
#include "main.h"
#include <math.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL.h>
#include <SDL3_gfx/SDL3_gfxPrimitives.h>


SDL_Window* window;
SDL_Renderer* renderer;

float sind(float x){
	return sinf(x * M_PI / 180);
}
float cosd(float x){
	return cosf(x * M_PI / 180);
}


SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv){

	if(!SDL_Init(SDL_INIT_VIDEO)){ SDL_Log("Error inicializando sdl: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	if(!SDL_CreateWindowAndRenderer("inverse kinematics", 800, 600, SDL_WINDOW_RESIZABLE, &window, &renderer)){
		SDL_Log("Error inicializando ventana y renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	AppData* data = (AppData*)SDL_malloc(sizeof(AppData));

	data->armsAmount = 3;
	data->arms = (Arm*)SDL_calloc(data->armsAmount, sizeof(Arm));

	data->arms[0].position = (SDL_Point){500, 150};
	data->arms[0].length = 100;
	data->arms[0].angle = 60;

	for (size_t i = 1; i < data->armsAmount; i++){
		data->arms[i].angle = 90;
		data->arms[i].length = 50;

		Arm* prev = &data->arms[i-1];
		data->arms[i].position = (SDL_Point){
			prev->position.x + cosd(prev->angle) * prev->length,
			prev->position.y + sind(data->arms[i-1].angle) * prev->length
		};
	}

	data->objetive.x = data->objetive.y = 250;

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
	AppData* data = (AppData*)appstate;
	SDL_SetRenderDrawColor(renderer, WHITE, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, BLACK, SDL_ALPHA_OPAQUE);

	for (size_t i = 1; i < data->armsAmount; i++){
		Arm* prev = &data->arms[i-1];
		Arm* curr = &data->arms[i];
		curr->position.x = prev->position.x + cosd(prev->angle) * prev->length;
		curr->position.y = prev->position.y + sind(prev->angle) * prev->length;
	}
	Arm* last = &data->arms[data->armsAmount - 1];
    SDL_FPoint tipPosition = (SDL_FPoint){
        last->position.x + cosd(last->angle) * last->length,
        last->position.y + sind(last->angle) * last->length
    };
	SDL_FPoint error = (SDL_FPoint){
		tipPosition.x - data->objetive.x,
		tipPosition.y - data->objetive.y
	};

	for (size_t i = 0; i < data->armsAmount; i++){
		Arm* currArm = &data->arms[i];
		currArm->angle += 0.01f * i;
		
	}

	for (size_t i = 0; i < data->armsAmount-1; i++){
		Arm* currArm = &data->arms[i];
		Arm* nextArm = &data->arms[i+1];

		circleRGBA(renderer, data->arms[i].position.x, data->arms[i].position.y, 5, 0, 0, 0, 255);
		SDL_RenderLine(renderer, currArm->position.x, currArm->position.y, nextArm->position.x, nextArm->position.y);

	}
	SDL_RenderPoint(renderer, data->objetive.x, data->objetive.y);
	circleRGBA(renderer, data->objetive.x, data->objetive.y, 15, 255, 0, 0, 255);

	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result){
	SDL_free(appstate);
	return;
}

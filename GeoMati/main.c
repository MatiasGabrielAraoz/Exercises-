#define SDL_MAIN_USE_CALLBACKS 1

#include <stdio.h>
#include <printf.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <iso646.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h> 
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
typedef struct{
	float amplitude;
	float frequency;
	SDL_FPoint* points;

}Sin;

typedef struct{
	void* data;
	int capacity;
	int size;
	size_t elementSize;
}DynamicArray;

void initArray(DynamicArray *arr, size_t elementSize, int initialCapacity){
	arr->elementSize = elementSize;
	arr->capacity = initialCapacity;
	arr->size = 0;
	arr->data = SDL_calloc(1, initialCapacity * elementSize);
}

void appendArray(DynamicArray *arr, void* element){
	if (arr->size >= arr->capacity){
		arr->capacity *= 2;
		arr->data = SDL_realloc(arr->data, arr->elementSize * arr->capacity);
	}
	Sin* element2 = (Sin*)element;

	void* target = (char*)arr->data + (arr->size * arr->elementSize);
	memcpy(target, element, arr->elementSize);

	arr->size++;
}
void* getArray(DynamicArray *arr, int index){
	return (char*)arr->data + (index * arr->elementSize);
}

typedef struct{
	int windowWidth;
	int windowHeight;
	int lastWindowWidth;
	int lastWindowHeight;
	int sinsAmount;
	DynamicArray sins;

}AppData;

SDL_FPoint* GetSinPoints(int windowWidth, int windowHeight, float frequency, float amplitude){
	SDL_FPoint* points = (SDL_FPoint*)SDL_malloc(sizeof(SDL_FPoint) * (windowWidth * 2));

	for (int i = 0; i < windowWidth * 2; i++){
		SDL_FPoint point;
		float mathX = (float)i / 2.0f;
		point.x = (float)i;
		point.y = ((float)windowHeight / 2) - (sinf(mathX * frequency) * amplitude);
		
		points[i] = point;
	}

	if (points == NULL) return NULL;
	return points;
}
SDL_FPoint* GetCosPoints(int windowWidth, int windowHeight, float frequency, float amplitude){
	SDL_FPoint* points = (SDL_FPoint*)SDL_malloc(sizeof(SDL_FPoint) * (windowWidth * 2));
	
	for (int i = 0; i < windowWidth * 2; i++){
		SDL_FPoint point;
		float mathX = (float)i / 2.0f;
		point.x = (float)i;
		point.y = ((float)windowHeight /2) - (cosf(mathX * frequency) * amplitude);
		points[i] = point;
	}
	if (points == NULL) return NULL;
	return points;

}

Sin CreateSin(void *appstate, float amplitude, float frequency){
	AppData *data = appstate;
	Sin sin;

	sin.frequency = frequency;
	sin.amplitude = amplitude;
	int windowWidth, windowHeight;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	sin.points = GetSinPoints(windowWidth, windowHeight, sin.frequency, sin.amplitude);

	appendArray(&data->sins, &sin);

	return sin;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char* argv[]){ 
	if(!SDL_Init(SDL_INIT_VIDEO)){ SDL_Log("Error inicializando sdl: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	if(!SDL_CreateWindowAndRenderer("GeoMati", 800, 600, SDL_WINDOW_RESIZABLE, &window, &renderer)){
		SDL_Log("Error inicializando ventana y renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	AppData *data = (AppData*)SDL_calloc(1, sizeof(AppData)); SDL_GetWindowSize(window, &data->windowWidth, &data->windowHeight);
	
	initArray(&data->sins, sizeof(Sin), 2);
	CreateSin(data, 5, 0.02f);

	data->lastWindowWidth = 0;
	data->lastWindowHeight = 0;
	

	*appstate = data;
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){
	AppData* data = appstate;
	if (event->type == SDL_EVENT_QUIT){
		return SDL_APP_SUCCESS;
	}
	if (event->type == SDL_EVENT_WINDOW_RESIZED){
		SDL_GetWindowSize(window, &data->windowWidth, &data->windowHeight);
		appstate = data;
	}
	if (event->type == SDL_EVENT_MOUSE_WHEEL){
		for (int i = 0; i < data->sins.size; i++){

			Sin* sin = (Sin*)getArray(&data->sins, i);
			if (sin == NULL) continue;

			if (event->wheel.y > 0){
				sin->frequency *= 1.1f;
				sin->amplitude *= 1.1f;
			}
			if (event->wheel.y < 0){
				if (sin->amplitude > 1.0f && sin->frequency > 0.001f) {
					sin->frequency /= 1.1f;
					sin->amplitude /= 1.1f;
				}
			}
			SDL_free(sin->points);
			sin->points = GetSinPoints(data->windowWidth, data->windowHeight, sin->frequency, sin->amplitude);
		}
	}

	return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void *appstate){
	AppData* data = appstate;
	
	// limpiar pantalla
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE_FLOAT);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE_FLOAT);
	
	for (int i = 0; i < data->sins.size; i++){
		Sin* seno = (Sin*)getArray(&data->sins, i);
		if (seno == NULL) continue;
		
		if (data->lastWindowWidth != data->windowWidth || data->lastWindowHeight != data->windowHeight){
			SDL_free(seno->points);
			seno->points = GetSinPoints(data->windowWidth, data->windowHeight, seno->frequency, seno->amplitude);
		}

		SDL_RenderLines(renderer, seno->points, data->windowWidth*2);
	}


	// Mostrar en pantalla
	SDL_RenderPresent(renderer);
	data->lastWindowWidth = data->windowWidth;
	data->lastWindowHeight = data->windowHeight;
	appstate = data;
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result){
	AppData* data = appstate;

	for (int i = 0; i < data->sins.size; i++){
		Sin* sin = (Sin*)getArray(&data->sins, i);

		if (sin->points != NULL){
			SDL_free(sin->points);
		}
	}
	SDL_free(data->sins.data);
	SDL_free(data);

}

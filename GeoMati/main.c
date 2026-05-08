#define SDL_MAIN_USE_CALLBACKS 1

#include "libs/tinyexpr.h"

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

typedef enum {
	SIN,
	COS,
	TAN
}MathType;

typedef struct{
	float amplitude;
	float frequency;
	SDL_FPoint* points;
	MathType type;
	int colorR;
	int colorG;
	int colorB;

}Function;

typedef struct{
	void* data;
	int capacity;
	int size;
	size_t elementSize;
}DynamicArray;

typedef struct{
	int windowWidth;
	int windowHeight;
	int lastWindowWidth;
	int lastWindowHeight;
	char* formula;
	DynamicArray waves;

}AppData;

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

	void* target = (char*)arr->data + (arr->size * arr->elementSize);
	memcpy(target, element, arr->elementSize);

	arr->size++;
}
void* getArray(DynamicArray *arr, int index){
	return (char*)arr->data + (index * arr->elementSize);
}


SDL_FPoint* GetPoints(MathType type, int windowWidth, int windowHeight, float frequency, float amplitude){
	SDL_FPoint* points = (SDL_FPoint*)SDL_malloc(sizeof(SDL_FPoint) * (windowWidth * 2));

	for (int i = 0; i < windowWidth * 2; i++){
		SDL_FPoint point;
		float mathX = (float)i / 2.0f;
		point.x = (float)i / 2.0f;
		// point.y = ((float)windowHeight / 2) - (mathFunction(mathX * frequency) * amplitude);
		
		points[i] = point;
	}

	if (points == NULL) return NULL;
	return points;
}

Function CreateWave(void *appstate,MathType type, float amplitude, float frequency){
	AppData *data = appstate;
	Function wave;

	int windowWidth, windowHeight;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	wave.frequency = frequency;
	wave.amplitude = amplitude;
	wave.type = type;
	wave.points = GetPoints(type, windowWidth, windowHeight, wave.frequency, wave.amplitude);
	if (type == SIN){
		wave.colorR = 255;
		wave.colorG = 0;
		wave.colorB = 0;
	}
	if (type == COS){
		wave.colorR = 0;
		wave.colorG = 0;
		wave.colorB = 255;
	}

	appendArray(&data->waves, &wave);

	return wave;
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

	if (argc > 1){
		data->formula = argv[1];

	}
	else{
		SDL_Log("No se especificó ninguna fórmula");
		return SDL_APP_FAILURE;
	}
	
	initArray(&data->waves, sizeof(Function), 2);
	// CreateWave(data, SIN, 50.0f, 0.02f);
	// CreateWave(data, COS, 50.0f, 0.02f);


	data->lastWindowWidth = 0;
	data->lastWindowHeight = 0;

	int error;
	double x_val = 1;
	int x = 0;

	te_variable vars[] = {{"x", &x_val}};
	te_expr *expr = te_compile(data->formula, vars, 1, &error);

	if (expr){
		x_val = x;
		float y = te_eval(expr);
		printf("x = %d \n y = %.2f", x, y);
		te_free(expr);

	}
	*appstate = data;
	return SDL_APP_SUCCESS;

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
	// if (event->type == SDL_EVENT_MOUSE_WHEEL){
	// 	for (int i = 0; i < data->waves.size; i++){
	//
	// 		Wave* wave = (Wave*)getArray(&data->waves, i);
	// 		if (wave == NULL) continue;
	//
	// 		if (event->wheel.y > 0){
	// 			wave->frequency *= 1.1f;
	// 			wave->amplitude *= 1.1f;
	// 		}
	// 		if (event->wheel.y < 0){
	// 			if (wave->amplitude > 1.0f && wave->frequency > 0.001f) {
	// 				wave->frequency /= 1.1f;
	// 				wave->amplitude /= 1.1f;
	// 			}
	// 		}
	// 		SDL_free(wave->points);
	// 		wave->points = GetPoints(wave->type,data->windowWidth, data->windowHeight, wave->frequency, wave->amplitude);
	// 	}
	// }

	return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void *appstate){
	AppData* data = appstate;
	
	// limpiar pantalla
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE_FLOAT);
	SDL_RenderClear(renderer);

	
	for (int i = 0; i < data->waves.size; i++){
		Function* wave = (Wave*)getArray(&data->waves, i);
		if (wave == NULL) continue;
		
		if (data->lastWindowWidth != data->windowWidth || data->lastWindowHeight != data->windowHeight){
			SDL_free(wave->points);
			wave->points = GetPoints(wave->type, data->windowWidth, data->windowHeight, wave->frequency, wave->amplitude);
		}

		SDL_SetRenderDrawColor(renderer, wave->colorR, wave->colorG, wave->colorB, SDL_ALPHA_OPAQUE_FLOAT);
		SDL_RenderLines(renderer, wave->points, data->windowWidth*2);
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

	for (int i = 0; i < data->waves.size; i++){
		Function* sin = (Wave*)getArray(&data->waves, i);

		if (sin->points != NULL){
			SDL_free(sin->points);
		}
	}
	SDL_free(data->waves.data);
	SDL_free(data);


}

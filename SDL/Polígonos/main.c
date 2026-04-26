#include <SDL3/SDL_timer.h>
#define SDL_MAIN_USE_CALLBACKS 1
#include <stdlib.h>
#include <stdio.h>
#include <SDL3/SDL_rect.h> #include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <wchar.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <math.h>

#define WIDTH 800
#define HEIGHT 600

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;


SDL_FPoint* GetPolygonSidePoints(SDL_FPoint* points, int sides, float centerX, float centerY, float radius, float initialRotation){
	if (points == NULL){
		return NULL;
	}

	for (int i = 0; i <= sides; i++){
		SDL_FPoint point;
		float angle = ((2 * (float)M_PI * i) / sides) +  initialRotation;
		point.x = centerX + radius * SDL_cosf(angle);
		point.y = centerY + radius * SDL_sinf(angle);
		
		points[i] = point;
	}
	return points;
}
void DrawPolygon(int sides, float centerX, float centerY, float radius, float initialRotation){
	SDL_FPoint* polygonPoints = (SDL_FPoint*)SDL_malloc(sizeof(SDL_FPoint) * (sides+1));
	GetPolygonSidePoints(polygonPoints, sides, centerX, centerY, radius, initialRotation);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE_FLOAT);

	SDL_RenderLines(renderer, polygonPoints, sides+1);
	SDL_free(polygonPoints);
}
typedef struct {
	int sides;
	float rotation;
	float rotationSpeed;
	
	//deltaTime 
	Uint64 lastTime;
	float deltaTime;

} AppData;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv){

	if (!SDL_Init(SDL_INIT_VIDEO)){
		SDL_Log("Error inicializando SDL. %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	if (!SDL_CreateWindowAndRenderer("Polígono", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)){
		SDL_Log("Error creando la ventana y renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	AppData *data = (AppData *)SDL_calloc(1, sizeof(AppData));
	data->lastTime = SDL_GetTicks();
	data->rotation = 0.0f;
	if (argc > 2){
		data->sides = atoi(argv[1]);
		data->rotationSpeed = atoi(argv[2]);
	}
	else {
		printf("Error, debes de especificar la cantidad de lados como un argumento con: \"./main numero\" ");
		return SDL_APP_FAILURE;
	}

	*appstate = data;
	
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){
	if(event->type == SDL_EVENT_QUIT){
		return SDL_APP_SUCCESS;
	}
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate){
	AppData *data = appstate;
	
	Uint64 currentTime = SDL_GetTicks();

	data->deltaTime = (float)(currentTime - data->lastTime) / 1000.0f;
	data->lastTime = currentTime;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE_FLOAT);
	SDL_RenderClear(renderer);

	
	DrawPolygon(data->sides, 100, 100, 50, data->rotation);

	data->rotation += data->rotationSpeed * data->deltaTime;

	SDL_RenderPresent(renderer);
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result){

}


	

#include <SDL3/SDL_rect.h>
#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_pixels.h>

#define WIDTH 800
#define HEIGHT 600

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

SDL_AppResult SDL_AppInit(void **appState, int argc, char *argv[]){
	SDL_SetAppMetadata("Test Programa", "1.0", "Test");
	if (!SDL_Init(SDL_INIT_VIDEO)){
		SDL_Log("Error iniciando sdl: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!SDL_CreateWindowAndRenderer("Test", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)){
		SDL_Log("No se pudo crear el window renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appState, SDL_Event *event){
	if (event->type == SDL_EVENT_QUIT){
		return SDL_APP_SUCCESS;
	}
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate){
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	SDL_RenderClear(renderer);

	SDL_FRect rectangle;
	rectangle.x = rectangle.y = 100;
	rectangle.h = rectangle.w = 50;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rectangle);

	SDL_RenderPresent(renderer);
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result){

}

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL.h>

SDL_Window* window;
SDL_Renderer* renderer;

typedef struct {
} AppData;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv){

	if(!SDL_Init(SDL_INIT_VIDEO)){ SDL_Log("Error inicializando sdl: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	if(!SDL_CreateWindowAndRenderer("GeoMati", 800, 600, SDL_WINDOW_RESIZABLE, &window, &renderer)){
		SDL_Log("Error inicializando ventana y renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	AppData* data = (AppData*)SDL_malloc(sizeof(AppData));

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
	SDL_free(appstate);
	return;
}

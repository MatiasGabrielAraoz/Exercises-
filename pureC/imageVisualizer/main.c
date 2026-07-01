#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>

SDL_Window* window;
SDL_Renderer* renderer;

void GetValueFromFile(void* value, int offset, int WHENCE, size_t size, FILE* file){
	int start_pos = ftell(file);

	fseek(file, offset, WHENCE);
	fread(value, size, 1, file);

	fseek(file, start_pos, SEEK_SET);
}
typedef struct {
	int x;
	int y;
} Vector2;

typedef struct {
	int argc;
	char **argv;
	FILE* file;
	Vector2 offset;
	unsigned int imgWidth;
	unsigned int imgHeight;
	unsigned short bpp;
	unsigned int colorArrayPos;
	unsigned int byteSize;
	bool isDragging;
} AppData;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv){
	if (argc <= 1){
		SDL_Log("Debes especificar la imagen a abrir");
		return SDL_APP_FAILURE;
	}

	if (!SDL_Init(SDL_INIT_VIDEO)){
		SDL_Log("No se pudo inicializar SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!SDL_CreateWindowAndRenderer("ImgViewer", 800, 600,  SDL_WINDOW_RESIZABLE, &window,  &renderer)){
		SDL_Log("No se pudo crear una ventana/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	AppData* data = (AppData*)SDL_malloc(sizeof(AppData));
	data->file = fopen(argv[1], "r");

	if (data->file == NULL){
		SDL_Log("No se pudo abrir el archivo: %s", strerror(errno));
		return SDL_APP_FAILURE;
	}

	char signature[2];
	fread(signature, sizeof(char), 2, data->file);

	if (signature[0] != 'B' || signature[1] != 'M' ){
		SDL_Log("Formato de archivo incorrecto, firma inválida");
		return SDL_APP_FAILURE;
	}
	fseek(data->file, 0, SEEK_SET);
	// la posición del array de colores está en el byte 10
	// width está guardado en el byte 18
	// height está guardado en el byte 22
	// bits por pixel estpa guardado en el byte 28
	
	GetValueFromFile(&data->colorArrayPos, 10, SEEK_SET, sizeof(unsigned int), data->file);
	GetValueFromFile(&data->imgWidth, 18, SEEK_SET, sizeof(unsigned int), data->file);
	GetValueFromFile(&data->imgHeight, 22, SEEK_SET, sizeof(unsigned int), data->file);
	GetValueFromFile(&data->bpp, 28, SEEK_SET, sizeof(unsigned short), data->file);
	printf("color array pos: %d\n imgWidth: %d\n imgHeight: %d\n bpp: %d\n", data->colorArrayPos, data->imgWidth, data->imgHeight, data->bpp);
	// tengo que calcular el tamaño en bytes de la sección el array de pixeles
	// el ancho en bytes se calcula como ((ancho * bpp + 31)/ 32)*4 
	data->byteSize = ((data->imgWidth * data->bpp + 31)/ 32) * 4;
	data->offset.x = data->offset.y = 0;
	data->isDragging = false;
	

	*appstate = data;
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate){
	AppData* data = appstate;

	SDL_RenderClear(renderer);
	fseek(data->file, data->colorArrayPos, SEEK_SET);
	for (int j = 0; j < data->imgHeight; j++){
		for (int i = 0; i < data->imgWidth; i++){
			unsigned char b;
			fread(&b, sizeof(unsigned char), 1, data->file);
			unsigned char g;
			fread(&g, sizeof(unsigned char), 1, data->file);
			unsigned char r;
			fread(&r, sizeof(unsigned char), 1, data->file);

			// 32 bits = 4 bytes es decir incluye el alpha al ser bgra
			if (data->bpp == 32){
				unsigned char a;
				fread(&a, sizeof(unsigned char), 1, data->file);
				SDL_SetRenderDrawColor(renderer, r, g, b, a);
				SDL_RenderPoint(renderer, i+data->offset.x, data->imgHeight - j + data->offset.y);
			}
			else {
				SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
				SDL_RenderPoint(renderer, i + data->offset.x, data->imgHeight - j + data->offset.y);
			}
		}
	}

	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){
	AppData* data = appstate;
	if (event->type == SDL_EVENT_QUIT){
		return SDL_APP_SUCCESS;
	}
	if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN){
		data->isDragging = true;
	}
	if (event->type == SDL_EVENT_MOUSE_BUTTON_UP){
		data->isDragging = false;
	}
	if (event->type == SDL_EVENT_MOUSE_MOTION){
		if (data->isDragging){
				data->offset.x += event->motion.xrel;
				data->offset.y += event->motion.yrel;
		}
	}

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result){
	AppData* data = (AppData*)appstate; 

	fclose(data->file);

	SDL_free(data);
}


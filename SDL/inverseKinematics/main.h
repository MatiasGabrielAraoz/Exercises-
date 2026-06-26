#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL.h>

#define WHITE 255, 255, 255
#define BLACK 0, 0, 0
#define RED 255, 0, 0
#define GREEN 0, 255, 0
#define BLUE 0, 0, 255

typedef struct {
	SDL_Point position;
	float length;
	float angle;
} Arm;

typedef struct {
	Arm* arms;
	SDL_Point objetive;
	size_t armsAmount;
	int argc;
	char** argv;

} AppData;

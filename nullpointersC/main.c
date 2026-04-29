#include <stddef.h>
#include <stdio.h>

struct House{
	int Number;
	char* Name; 
	int Size;
	
}House;

char* CambiarNombre(struct House* Casa){
	Casa->Name = "Hola";

	return Casa;
}
int main(){
	struct House home = {12, "Casa", 25};

	char* nombre = home.Name;

	printf("%p \n", nombre);
	
}

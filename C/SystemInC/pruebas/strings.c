#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char* data;
	int length;
	int capacity;
}String;

String* StrCreate(size_t initial_cap){
	String *str = (String*)malloc(sizeof(String));
	if (str == NULL) return NULL;

	str->capacity = initial_cap > 0 ? initial_cap : 16;
	str->length = 0;
	str->data = (char*)malloc(str->capacity);
	if (str->data == NULL){
		free(str);
		return NULL;
	}

	str->data[0] = '\0';
	return str;
	
}

String* StrAppend(String* str,char* textToAppend){
	if (strlen(str->data) + strlen(textToAppend) >= str->capacity){
		int newLength = strlen(str->data) + strlen(textToAppend);

		int newCapacity = newLength + 1;

		str->capacity = newCapacity;
		str->data = realloc(str->data, newCapacity);
		if(str->data == NULL) return NULL;

	}
	char* newStr = strcat(str->data, textToAppend);
	if (newStr == NULL) return NULL;

	str->data = newStr;
	str->length = strlen(newStr);
	return str;
}
String* EmptyString(String* str){
	str->data[0] = '\0';
	str->capacity = 1;
	str->data = realloc(str->data, str->capacity);
	str->length = 0;
	return str;
}

int main(){
	char stringNormal[] = "Hola";
	String* str = StrCreate(15);
	StrAppend(str, "djkghakfjhgfljkghfghfdgfhglsalgkdfhgjkaghsdklghflglsdfj");
	printf("Capacity: %d \n", str->capacity);
	printf("length: %d \n", str->length);
	printf("Text: %s \n", str->data);
	
	printf("\n Emptying String \n");
	str = EmptyString(str);
	printf("Capacity: %d \n", str->capacity);
	printf("length: %d \n", str->length);
	printf("Text: %s \n", str->data);
	return 0;

}

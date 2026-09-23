#include "main.h"

int Strlen(const char* str){
	size_t i = 0;
	while (str[i] != '\0'){
		i++;
	}
	return i;
}

void write(const char* text, int len, int fd){
	if (text == NULL){
		const char* errorMsg = "error, el texto no es válido \n";
		asm_print(errorMsg, Strlen(errorMsg), STDOUT);
		return;
	}
	asm_print(text, len, fd);
	
}
char* IntToString(int number, char* str){

	int i = 0;
	int isNegative = number <= 0;

	if (isNegative) number = -number;
	do{
		str[i++] = (number % 10) + '0';
		number /= 10;
	}while (number > 0);

	if (isNegative) str[i++] = '-';
	for (int j = 0; j < i / 2; j++){
		char temp = str[j];
		str[j] = str[i - 1 - j];
		str[i - 1 - j] = temp;
	}
	str[i] = '\0';
	return str;
}

void print(const char* format, ...){
	char buffer[2048];
	int buf_idx = 0;

	va_list args;
	va_start(args, format);

	size_t arg_idx = 0;

	for (size_t i = 0; format[i] != '\0'; i++){
		if (buf_idx >= 2000){
			asm_print(buffer, buf_idx, STDOUT);
			buf_idx = 0;
		}
		if (format[i] == '%'){

			switch (format[i+1]){
				case 's':{
					char* str_var = va_arg(args, char*);

					if (str_var != NULL) {
						for (size_t j = 0; str_var[j] != '\0'; j++){
							buffer[buf_idx++] = str_var[j];
						}
					}
					break;
				}

				case 'c':{
					char str_var = (char)va_arg(args, int);
					buffer[buf_idx++] = str_var;
					break;
				}
				case 'd':{
					int intVar = va_arg(args, int);
					char strVar[20];
					IntToString(intVar, strVar);

					for (int j = 0; strVar[j] != '\0'; j++) {
						buffer[buf_idx++] = strVar[j];
					}

					break;
				}
			}
			i++;
		}
		else{
			buffer[buf_idx++] = format[i];
		}
	}
	va_end(args);

	if (buf_idx > 0){
		write(buffer, buf_idx, STDOUT);
	}
}

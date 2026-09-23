//file descriptors
#define STD_IN 0
#define STD_OUT 1
#define STD_ERR 2

#define size_t unsigned long long

// NULL
#define NULL ((void*)0)

//BUILTINS
typedef __builtin_va_list va_list;
#define va_start(v, l) __builtin_va_start(v, l)
#define va_arg(v, l)   __builtin_va_arg(v, l)
#define va_end(v)      __builtin_va_end(v)

// ASM FUNCTIONS
extern void asm_print(const char* text, int len, int fd);
extern void asm_exit();

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
		asm_print(errorMsg, Strlen(errorMsg), STD_OUT);
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
			asm_print(buffer, buf_idx, STD_OUT);
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
		write(buffer, buf_idx, STD_OUT);
	}


	

}

void _start(){
	char* name = "Jorgito";
	print("Hola %s \n", name);

	asm_exit();
}

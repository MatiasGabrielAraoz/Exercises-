#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void ShowPromptList(vector<string>& opts){
	for (int i = 1; i <= opts.size(); i++){
		string opt = opts[i-1];
		printf("[%d] %s \n", i, opt.c_str());
	}
}

class Objeto {

	public:

		float price = 0;
		string desc;
		int stock = 0;

		Objeto() {}

	void Modify(int code){
		vector<string> values = {"Descripción", "Precio", "Stock", "Volver"};
		int opt = 0;

		printf("Selecciona uno de los valores a modificar \n");
		ShowPromptList(values);


		bool repeating = true;
		while (repeating){
			printf("Selecciona otra opción: ");
			cin >> opt;
			switch (opt) {
				case 1:
					// desc
					printf("Inserta la nueva descripción: ");
					cin >> this->desc;
					break;
				case 2:
					// precio
					printf("Inserta el nuevo precio: ");
					cin >> this->price;
					break;
				case 3:
					// stock
					printf("Inserta el nuevo stock: ");
					cin >> this->stock;
					break;
				case 4:
					repeating = false;
					break;
				default:
					printf("Opción inválida \n");
					break;
			
			}
		}
		
	}
};

void MostrarPresupuesto(const map<int, Objeto>& articles){
	int final_price = 0;

	for (const auto&[k, p] : articles){
		int tmp_price = p.stock * p.price;
		final_price += tmp_price;
	}

	printf("Para conseguir el stock de todos los productos se necesita un presupuesto de: %d", final_price);

}

// consigna:
// crear programa con:
// - gestión de stock (CRUD)
// - Cálculo de presupuesto
// - Validación de datos


int main(){
	map<int, Objeto> articles;
	vector<std::string> options = {"Crear item", "Eliminar item", "Modificar item", "Consultar item", "Obtener presupuesto", "Salir"};

	bool isRunning = true;
	while (isRunning){
		printf("Selecciona una opción: \n");
		ShowPromptList(options);

		int opt = 0;;
		cin >> opt;
		int code = 0;

		if (opt != 6){
			printf("Inserta un código para el producto: ");
			cin >> code;

		}
		
		switch (opt){
			case 1:
				articles[code] = Objeto();
				break;

			case 2:
				articles.erase(code);
				break;

			case 3:
				articles[code].Modify(code);
				break;

			case 4:
				printf("codigo: %d \n Precio: %.2f \n Stock: %d \n Descripción: %s \n", 
						code, 
						articles[code].price,
						articles[code].stock,
						articles[code].desc.c_str()
				);
				break;

			case 5:
				MostrarPresupuesto(articles);
				break;

			case 6:
				isRunning = false;
				break;

			default:
				printf("Opción inválida, vuelva a intentar con una opción valida");
				break;

		}
	}
	return 0;
}

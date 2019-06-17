#include<iostream>
#include<math.h>
#include<iomanip>

using namespace std;

struct punto {

	float x, y;

}puntos_orig[100], puntos_alt[500] ;

void capturar_datos(int cant_puntos);
int combinaciones(int n, int i);
punto nuevo_punto(int cant_puntos, float t);
int fact(int num);
void bezier_line(const int cant_puntos, const float interv);
void print_table(const float interv);

void main() {

	//EL USUARIO INGRESA LA CANTIDAD DE PUNTOS A INGRESAR

	int cant_punt;

	do {

		system("cls");

		cout << "Ingrese el numero de puntos: " << endl;
		cin >> cant_punt;

	} while (cant_punt <= 0);
	
	capturar_datos(cant_punt); //SE INGRESAN LOS DATOS DE CADA PUNTO

	//EL USUARIO INGRESA EL INTERVALO DE VARIACION DE t

	float intervalo;

	do {

		system("cls");

		cout << "Ingrese el intervalo: " << endl;
		cin >> intervalo;

	} while (intervalo <= 0);

	bezier_line(cant_punt,intervalo); //SE CREAN LOS PUNTOS DE LA CURVA

	print_table(intervalo); //SE IMPRIMEN LOS NUEVOS PUNTOS DE LA CURVA

	system("pause");

}

void capturar_datos(const int cant_puntos) {

	//FUNCION PARA CAPTURAR EL NUMERO DE PUNTOS INGRESADO POR EL USUARIO
	//LA INFORMACION DE LOS PUNTOS SE ALMACENA EN EL ARREGLO puntos_orig

	for (int i = 0; i < cant_puntos; i++) {

		cout << "Ingrese la coordenada x del punto " << i << " : ";
		cin >> puntos_orig[i].x;
		cout << "Ingrese la coordenada y del punto " << i << " : ";
		cin >> puntos_orig[i].y;

	}

}

int combinaciones(const int n, const int i) {

	//COMBINACIONES DE n CON i

	int comb = (fact(n)) / ((fact(n - i)) * (fact(i)));

	return comb;

}

int fact(const int num) {

	//FACTORIAL DE UN NUMERO

	int tot = 1;

	if (num != 0) {

		for (int i = 1; i <= num; i++) {

			tot = tot * i;

		}

	}

	return tot;

}

punto nuevo_punto(const int cant_puntos, const float t) {

	//INICIALIZACION DEL NUEVO PUNTO
	punto new_point;
	new_point.x = 0;
	new_point.y = 0;

	int n = cant_puntos - 1; //SE CALCULA n A PARTIR DE LA CANTIDAD DE PUNTOS

	//SE CALCULA EL NUEVO PUNTO
	for (int i = 0; i <= n; i++) {

		int comb = combinaciones(n, i), //Combinaciones de n con i
			exponente = n - i;

		new_point.x += comb * puntos_orig[i].x*(pow((1 - t), exponente))*pow(t, i); //COORD. x

		new_point.y += comb * puntos_orig[i].y*(pow((1 - t), exponente))*pow(t, i); //COORD. y

	}

	return new_point;

}

void bezier_line(const int cant_puntos, const float interv) {

	float flujo = 0, limit = 1.01;
	int i = 0;

	do {

		puntos_alt[i] = nuevo_punto(cant_puntos, flujo);

		flujo += interv;

		i++;

	} while (flujo <= limit);
}

void print_table(const float interv) {

	system("cls");

	cout << setw(10) << left << "t" << setw(10) << left << "x" << setw(10) << left << "y" << endl << endl;

	int i = 0;
	float flujo = 0, limit = 1.01;

	cout << fixed;
	cout << setprecision(3);

	do {

		cout << setw(10) << left << flujo << setw(10) << left << puntos_alt[i].x << setw(10) << left << puntos_alt[i].y << endl;
		i++;
		flujo += interv;

	} while (flujo <= limit);

}

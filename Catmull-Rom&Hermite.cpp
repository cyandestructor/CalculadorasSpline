#include<iostream>
#include<iomanip>
#include<fstream>
#include<math.h>

using namespace std;

struct point {

	float x, y;

};

point ingresar_puntos(const int indice);
point catmull_rom(point arr_puntos[], int num_punt, int ind_anterior, int ind_actual, int ind_post);
point hermite(point arr_puntos[], point arr_tensores[], int indice, float intervalo);

void main() {

	int num_punt;

	cout << "Ingrese el numero de puntos a introducir: ";
	cin >> num_punt;

	point puntos_orig[100];

	for (int i = 0; i < num_punt; i++) {

		puntos_orig[i] = ingresar_puntos(i);

	}

	system("cls");

	float intervalo;

	cout << "Ingrese el intervalo: ";
	cin >> intervalo;

	system("cls");

	point tensores[100];

	for (int i = 0; i < num_punt; i++) {

		tensores[i] = catmull_rom(puntos_orig, num_punt, i - 1, i, i + 1);

	}

	//IMPRESION DE TENSORES
	cout << "Tensores" << endl;
	cout << setw(8) << "x" << setw(8) << "y" << endl;

	for (int i = 0; i < num_punt; i++) {

		cout << setw(8) << tensores[i].x << setw(8) << tensores[i].y << endl;

	}
	cout << endl;

	system("pause");
	system("cls");

	for (int i = 0; i < num_punt - 1; i++) { //se aplica para cada punto hasta el penultimo punto

		cout << "Tabla de P" << i << " con P" << i + 1 << endl;
		cout << setw(8) << "t" << setw(8) << "x" << setw(8) << "y" << endl;
		float flujo = 0; //flujo va de 0 a 1 en razon del intervalo
		while (flujo < 1.001) {

			point new_point = hermite(puntos_orig, tensores, i, flujo); //nuevo punto tras utilizar hermite

			cout << fixed;
			cout << setprecision(3);

			cout << setw(8) << flujo << setw(8) << new_point.x << setw(8) << new_point.y << endl;

			flujo += intervalo;

		}
		cout << endl;

	}

	//IMPRESION EN ARCHIVO .txt

	system("pause");

	ofstream ARCHIVO;

	ARCHIVO.open("CatmullRom.txt");

	for (int i = 0; i < num_punt - 1; i++) { //se aplica para cada punto hasta el penultimo punto

		ARCHIVO << "Tabla de P" << i << " con P" << i + 1 << endl;
		ARCHIVO << setw(8) << "t" << setw(8) << "x" << setw(8) << "y" << endl;
		float flujo = 0; //flujo va de 0 a 1 en razon del intervalo
		while (flujo < 1.001) {

			point new_point = hermite(puntos_orig, tensores, i, flujo); //nuevo punto tras utilizar hermite

			ARCHIVO << fixed;
			ARCHIVO << setprecision(3);

			ARCHIVO << setw(8) << flujo << setw(8) << new_point.x << setw(8) << new_point.y << endl;

			flujo += intervalo;

		}
		ARCHIVO << endl;

	}

	ARCHIVO.close();

}

point ingresar_puntos(const int indice) {

	system("cls");

	point punto;

	cout << "Ingrese la coordenada x del punto " << indice << " : ";
	cin >> punto.x;
	cout << "Ingrese la coordenada y del punto " << indice << " : ";
	cin >> punto.y;

	return punto;
}

point catmull_rom(point arr_puntos[], int num_punt, int ind_anterior, int ind_actual, int ind_post) {

	point tensor_T;
	
	if (ind_actual == 0) { //primer punto

		tensor_T.x = (arr_puntos[ind_post].x - arr_puntos[ind_actual].x) * 0.5;
		tensor_T.y = (arr_puntos[ind_post].y - arr_puntos[ind_actual].y) * 0.5;

	}
	else {

		if (ind_actual == num_punt - 1) { //ultimo punto

			tensor_T.x = (arr_puntos[ind_actual].x - arr_puntos[ind_anterior].x) * 0.5;
			tensor_T.y = (arr_puntos[ind_actual].y - arr_puntos[ind_anterior].y) * 0.5;

		}
		else { //cualquier otro punto

			tensor_T.x = (arr_puntos[ind_post].x - arr_puntos[ind_anterior].x) * 0.5;
			tensor_T.y = (arr_puntos[ind_post].y - arr_puntos[ind_anterior].y) * 0.5;

		}
	}

	return tensor_T;

}

point hermite(point arr_puntos[], point arr_tensores[], int indice, float intervalo) {

	point new_point;
	int indice_sig = indice + 1;

	new_point.x = (2 * pow(intervalo, 3) - 3 * pow(intervalo, 2) + 1) * arr_puntos[indice].x + (-2 * pow(intervalo, 3) + 3 * pow(intervalo, 2)) * arr_puntos[indice_sig].x + (pow(intervalo, 3) - 2 * pow(intervalo, 2) + intervalo) * arr_tensores[indice].x + (pow(intervalo, 3) - pow(intervalo, 2))* arr_tensores[indice_sig].x;
	new_point.y = (2 * pow(intervalo, 3) - 3 * pow(intervalo, 2) + 1) * arr_puntos[indice].y + (-2 * pow(intervalo, 3) + 3 * pow(intervalo, 2)) * arr_puntos[indice_sig].y + (pow(intervalo, 3) - 2 * pow(intervalo, 2) + intervalo) * arr_tensores[indice].y + (pow(intervalo, 3) - pow(intervalo, 2))* arr_tensores[indice_sig].y;

	return new_point;

}

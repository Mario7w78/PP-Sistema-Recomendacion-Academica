#pragma once

#include <string>
#include <vector>

using namespace std;

// Limpia espacios al inicio y al final de un texto
string limpiarEspacios(const string& texto);

// Separa una linea CSV simple usando coma como delimitador
vector<string> separarCsv(const string& linea);

// Reemplaza comas por espacios para evitar romper el formato CSV
string limpiarParaCsv(string texto);

// Lee una cadena no vacia desde consola
string leerTextoNoVacio(const string& mensaje);

// Lee un area academica que pertenezca a las areas de la data predeterminada
string leerAreaAcademicaValida(const string& mensaje);

// Lee un entero dentro de un rango permitido
int leerEnteroEnRango(const string& mensaje, int minimo, int maximo);

// Lee un decimal dentro de un rango permitido
float leerDecimalEnRango(const string& mensaje, float minimo, float maximo);

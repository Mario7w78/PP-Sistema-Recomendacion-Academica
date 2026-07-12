#include "Utilidades.h"
#include "Modelos.h"

#include <iostream>
#include <sstream>
#include <cctype>
#include <limits>

using namespace std;

// Limpia espacios al inicio y al final para evitar datos con espacios accidentales
string limpiarEspacios(const string& texto) {
    int inicio = 0;
    int fin = static_cast<int>(texto.size()) - 1;

    while (inicio <= fin && isspace(static_cast<unsigned char>(texto[inicio]))) {
        inicio++;
    }

    while (fin >= inicio && isspace(static_cast<unsigned char>(texto[fin]))) {
        fin--;
    }

    if (inicio > fin) {
        return "";
    }

    return texto.substr(inicio, fin - inicio + 1);
}

// Separa una linea CSV simple porque los archivos del proyecto no usan comas dentro de los datos
vector<string> separarCsv(const string& linea) {
    vector<string> partes;
    string parte;
    stringstream ss(linea);

    while (getline(ss, parte, ',')) {
        partes.push_back(limpiarEspacios(parte));
    }

    return partes;
}

// Reemplaza comas para que el texto ingresado por consola no altere las columnas del CSV
string limpiarParaCsv(string texto) {
    for (char& caracter : texto) {
        if (caracter == ',') {
            caracter = ' ';
        }
    }

    return limpiarEspacios(texto);
}

// Repite la lectura mientras el usuario deje el dato vacio
string leerTextoNoVacio(const string& mensaje) {
    string valor;

    do {
        cout << mensaje;
        getline(cin, valor);
        valor = limpiarParaCsv(valor);

        if (valor.empty()) {
            cout << "El dato no puede estar vacio\n";
        }
    } while (valor.empty());

    return valor;
}

// Repite la lectura hasta que el area coincida con una de las areas de la malla curricular
string leerAreaAcademicaValida(const string& mensaje) {
    while (true) {
        string area = leerTextoNoVacio(mensaje);

        if (esAreaAcademicaValida(area)) {
            return area;
        }

        cout << "Area no valida. Ingrese una de las areas disponibles\n";
    }
}

// Valida la lectura de enteros para evitar que el programa falle si el usuario escribe texto
int leerEnteroEnRango(const string& mensaje, int minimo, int maximo) {
    int valor;

    while (true) {
        cout << mensaje;
        cin >> valor;

        if (!cin.fail() && valor >= minimo && valor <= maximo) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }

        cout << "Ingrese un numero entre " << minimo << " y " << maximo << "\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Valida la lectura de notas usando el rango oficial del sistema universitario
float leerDecimalEnRango(const string& mensaje, float minimo, float maximo) {
    float valor;

    while (true) {
        cout << mensaje;
        cin >> valor;

        if (!cin.fail() && valor >= minimo && valor <= maximo) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }

        cout << "Ingrese un numero entre " << minimo << " y " << maximo << "\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

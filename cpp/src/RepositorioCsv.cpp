#include "RepositorioCsv.h"
#include "Utilidades.h"

#include <fstream>
#include <iostream>

using namespace std;

// Carga cursos omitiendo la cabecera del archivo CSV
vector<Curso> RepositorioCsv::cargarCursos(const string& rutaArchivo) {
    vector<Curso> cursos;
    ifstream archivo(rutaArchivo);
    string linea;

    if (!archivo.is_open()) {
        return cursos;
    }

    getline(archivo, linea);

    while (getline(archivo, linea)) {
        vector<string> partes = separarCsv(linea);

        if (partes.size() >= 4) {
            Curso curso;
            curso.codigo = partes[0];
            curso.nombre = partes[1];
            curso.area = partes[2];
            curso.creditos = stoi(partes[3]);
            cursos.push_back(curso);
        }
    }

    return cursos;
}

// Carga relaciones curso-prerrequisito desde el archivo CSV
vector<Prerrequisito> RepositorioCsv::cargarPrerrequisitos(const string& rutaArchivo) {
    vector<Prerrequisito> prerrequisitos;
    ifstream archivo(rutaArchivo);
    string linea;

    if (!archivo.is_open()) {
        return prerrequisitos;
    }

    getline(archivo, linea);

    while (getline(archivo, linea)) {
        vector<string> partes = separarCsv(linea);

        if (partes.size() >= 2) {
            Prerrequisito prerrequisito;
            prerrequisito.codigoCurso = partes[0];
            prerrequisito.codigoPrerrequisito = partes[1];
            prerrequisitos.push_back(prerrequisito);
        }
    }

    return prerrequisitos;
}

// Carga las notas de todos los estudiantes desde historial.csv
vector<RegistroHistorial> RepositorioCsv::cargarHistorial(const string& rutaArchivo) {
    vector<RegistroHistorial> historial;
    ifstream archivo(rutaArchivo);
    string linea;

    if (!archivo.is_open()) {
        return historial;
    }

    getline(archivo, linea);

    while (getline(archivo, linea)) {
        vector<string> partes = separarCsv(linea);

        if (partes.size() >= 3) {
            RegistroHistorial registro;
            registro.estudiante = partes[0];
            registro.codigoCurso = partes[1];
            registro.nota = stod(partes[2]);
            historial.push_back(registro);
        }
    }

    return historial;
}

// Carga las areas de interes de los estudiantes desde intereses.csv
vector<Interes> RepositorioCsv::cargarIntereses(const string& rutaArchivo) {
    vector<Interes> intereses;
    ifstream archivo(rutaArchivo);
    string linea;

    if (!archivo.is_open()) {
        return intereses;
    }

    getline(archivo, linea);

    while (getline(archivo, linea)) {
        vector<string> partes = separarCsv(linea);

        if (partes.size() >= 2) {
            Interes interes;
            interes.estudiante = partes[0];
            interes.area = partes[1];
            intereses.push_back(interes);
        }
    }

    return intereses;
}

// Sobrescribe cursos.csv con todos los cursos disponibles del sistema
void RepositorioCsv::guardarCursos(const string& rutaArchivo, const vector<Curso>& cursos) {
    ofstream archivo(rutaArchivo);

    archivo << "codigo,nombre,area,creditos\n";

    for (const Curso& curso : cursos) {
        archivo << curso.codigo << "," << curso.nombre << "," << curso.area << "," << curso.creditos << "\n";
    }
}

// Sobrescribe prerrequisitos.csv con todas las relaciones registradas
void RepositorioCsv::guardarPrerrequisitos(const string& rutaArchivo, const vector<Prerrequisito>& prerrequisitos) {
    ofstream archivo(rutaArchivo);

    archivo << "curso,prerrequisito\n";

    for (const Prerrequisito& prerrequisito : prerrequisitos) {
        archivo << prerrequisito.codigoCurso << "," << prerrequisito.codigoPrerrequisito << "\n";
    }
}

// Sobrescribe historial.csv con todas las notas registradas
void RepositorioCsv::guardarHistorial(const string& rutaArchivo, const vector<RegistroHistorial>& historial) {
    ofstream archivo(rutaArchivo);

    archivo << "estudiante,codigoCurso,nota\n";

    for (const RegistroHistorial& registro : historial) {
        archivo << registro.estudiante << "," << registro.codigoCurso << "," << registro.nota << "\n";
    }
}

// Sobrescribe intereses.csv con todas las areas de interes registradas
void RepositorioCsv::guardarIntereses(const string& rutaArchivo, const vector<Interes>& intereses) {
    ofstream archivo(rutaArchivo);

    archivo << "estudiante,area\n";

    for (const Interes& interes : intereses) {
        archivo << interes.estudiante << "," << interes.area << "\n";
    }
}

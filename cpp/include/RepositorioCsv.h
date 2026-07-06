#pragma once

#include "Modelos.h"

#include <string>
#include <vector>

using namespace std;

// Centraliza la lectura y escritura de todos los archivos CSV del sistema
class RepositorioCsv {
public:
    // Carga los cursos desde cursos.csv
    vector<Curso> cargarCursos(const string& rutaArchivo);

    // Carga los prerrequisitos desde prerrequisitos.csv
    vector<Prerrequisito> cargarPrerrequisitos(const string& rutaArchivo);

    // Carga el historial academico desde historial.csv
    vector<RegistroHistorial> cargarHistorial(const string& rutaArchivo);

    // Carga los intereses desde intereses.csv
    vector<Interes> cargarIntereses(const string& rutaArchivo);

    // Guarda los cursos registrados en cursos.csv
    void guardarCursos(const string& rutaArchivo, const vector<Curso>& cursos);

    // Guarda los prerrequisitos registrados en prerrequisitos.csv
    void guardarPrerrequisitos(const string& rutaArchivo, const vector<Prerrequisito>& prerrequisitos);

    // Guarda el historial academico registrado en historial.csv
    void guardarHistorial(const string& rutaArchivo, const vector<RegistroHistorial>& historial);

    // Guarda los intereses registrados en intereses.csv
    void guardarIntereses(const string& rutaArchivo, const vector<Interes>& intereses);
};

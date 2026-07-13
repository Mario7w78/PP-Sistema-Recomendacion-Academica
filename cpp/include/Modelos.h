#pragma once

#include <string>
#include <vector>

using namespace std;

// Areas presentes en la malla curricular de los datos predeterminados
inline const vector<string> AREAS_ACADEMICAS_VALIDAS = {
    "General", "Matematica", "General_Ingenieria", "General_Sistemas",
    "Software", "Procesos", "Datos", "IA", "TI"
};

// Verifica que el area pertenezca a las areas definidas por la malla curricular
inline bool esAreaAcademicaValida(const string& area) {
    for (const string& areaValida : AREAS_ACADEMICAS_VALIDAS) {
        if (area == areaValida) {
            return true;
        }
    }

    return false;
}

// Representa un curso del plan de estudios
struct Curso {
    string codigo;
    string nombre;
    string area;
    int creditos;
};

// Representa una relacion entre un curso y uno de sus prerrequisitos
struct Prerrequisito {
    string codigoCurso;
    string codigoPrerrequisito;
};

// Representa una nota registrada en el historial de un estudiante
struct RegistroHistorial {
    string estudiante;
    string codigoCurso;
    double nota;
};

// Representa un area academica de interes de un estudiante
struct Interes {
    string estudiante;
    string area;
};

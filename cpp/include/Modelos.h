#pragma once

#include <string>

using namespace std;

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

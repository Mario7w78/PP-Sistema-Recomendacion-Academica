#pragma once

#include "Modelos.h"

#include <vector>

using namespace std;

// Contiene la data inicial basada en la malla curricular y los planes de especialidad
class DatosPredeterminados {
public:
    // Devuelve los cursos iniciales clasificados por area academica
    static vector<Curso> obtenerCursos();

    // Devuelve las relaciones iniciales de prerrequisitos entre cursos
    static vector<Prerrequisito> obtenerPrerrequisitos();

    // Devuelve un historial de prueba para demostrar las consultas del sistema
    static vector<RegistroHistorial> obtenerHistorial();

    // Devuelve intereses de prueba para demostrar la integracion con Prolog
    static vector<Interes> obtenerIntereses();
};

#pragma once

#include "GestorAcademico.h"

#include <string>

using namespace std;

// Genera salidas de consola relacionadas con el rendimiento del estudiante
class ReporteAcademico {
public:
    // Muestra promedio, cantidad de cursos aprobados, desaprobados y extremos de notas
    static void mostrarReporteGeneral(const GestorAcademico& gestor, const string& estudiante);
};

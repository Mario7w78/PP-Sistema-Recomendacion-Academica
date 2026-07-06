#include "ReporteAcademico.h"

#include <iomanip>
#include <iostream>

using namespace std;

// Construye el reporte general solicitado por el enunciado del proyecto
void ReporteAcademico::mostrarReporteGeneral(const GestorAcademico& gestor, const string& estudiante) {
    vector<RegistroHistorial> historial = gestor.obtenerHistorialPorEstudiante(estudiante);

    if (historial.empty()) {
        cout << "No existe historial para el estudiante indicado\n";
        return;
    }

    vector<RegistroHistorial> aprobados = gestor.obtenerAprobados(estudiante);
    vector<RegistroHistorial> desaprobados = gestor.obtenerDesaprobados(estudiante);
    RegistroHistorial mayor = gestor.obtenerMayorNota(estudiante);
    RegistroHistorial menor = gestor.obtenerMenorNota(estudiante);

    cout << fixed << setprecision(2);
    cout << "\nREPORTE GENERAL\n";
    cout << "Estudiante: " << estudiante << "\n";
    cout << "Promedio general: " << gestor.calcularPromedio(estudiante) << "\n";
    cout << "Cursos aprobados: " << aprobados.size() << "\n";
    cout << "Cursos desaprobados: " << desaprobados.size() << "\n";
    cout << "Curso con mayor nota: " << gestor.buscarNombreCurso(mayor.codigoCurso) << " (" << mayor.nota << ")\n";
    cout << "Curso con menor nota: " << gestor.buscarNombreCurso(menor.codigoCurso) << " (" << menor.nota << ")\n";
}

#pragma once

#include "GestorAcademico.h"
#include "RepositorioCsv.h"

#include <string>

using namespace std;

// Controla el flujo principal del programa y conecta las clases del sistema
class SistemaAcademico {
private:
    GestorAcademico gestor;
    RepositorioCsv repositorio;

    string rutaCursos;
    string rutaPrerrequisitos;
    string rutaHistorial;
    string rutaIntereses;

    // Carga datos existentes desde los archivos CSV
    void cargarDesdeCsv();

    // Carga manualmente la data predeterminada y la guarda en CSV
    void cargarDatosPredeterminados();

    // Guarda toda la informacion actual en archivos CSV
    void guardarTodo();

    // Muestra el menu principal de operaciones
    void mostrarMenu();

    // Permite registrar un nuevo curso desde consola
    void registrarCurso();

    // Permite registrar una relacion de prerrequisito desde consola
    void registrarPrerrequisito();

    // Permite registrar una nota de estudiante desde consola
    void registrarNota();

    // Permite registrar un area de interes desde consola
    void registrarInteres();

    // Muestra todos los cursos disponibles
    void mostrarCursos();

    // Muestra el historial completo de un estudiante
    void mostrarHistorial();

    // Muestra cursos aprobados o desaprobados de un estudiante
    void mostrarCursosPorEstado(bool aprobados);

    // Muestra el reporte general de un estudiante
    void mostrarReporteGeneral();

public:
    // Configura las rutas de archivos CSV que usara el sistema
    SistemaAcademico();

    // Ejecuta el ciclo principal del menu
    void iniciar();
};

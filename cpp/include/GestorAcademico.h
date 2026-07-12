#pragma once

#include "Modelos.h"

#include <string>
#include <vector>

using namespace std;

// Administra la informacion en memoria y realiza las consultas academicas
class GestorAcademico {
private:
    vector<Curso> cursos;
    vector<Prerrequisito> prerrequisitos;
    vector<RegistroHistorial> historial;
    vector<Interes> intereses;

public:
    // Reemplaza la data en memoria con la data cargada desde CSV o desde datos predeterminados
    void cargarDatos(const vector<Curso>& nuevosCursos,
                     const vector<Prerrequisito>& nuevosPrerrequisitos,
                     const vector<RegistroHistorial>& nuevoHistorial,
                     const vector<Interes>& nuevosIntereses);

    // Agrega un curso al vector principal de cursos
    bool agregarCurso(const Curso& curso);

    // Agrega una relacion de prerrequisito si ambos cursos existen
    bool agregarPrerrequisito(const Prerrequisito& prerrequisito);

    // Agrega una nota al historial si el curso existe
    bool agregarRegistroHistorial(const RegistroHistorial& registro);

    // Agrega un area de interes para un estudiante si el area es valida
    bool agregarInteres(const Interes& interes);

    // Verifica si existe informacion minima cargada en el sistema
    bool estaVacio() const;

    // Verifica si un codigo pertenece a un curso registrado
    bool existeCurso(const string& codigoCurso) const;

    // Busca el nombre de un curso usando su codigo
    string buscarNombreCurso(const string& codigoCurso) const;

    // Devuelve todos los cursos registrados
    vector<Curso> obtenerCursos() const;

    // Devuelve todos los prerrequisitos registrados
    vector<Prerrequisito> obtenerPrerrequisitos() const;

    // Devuelve todo el historial academico registrado
    vector<RegistroHistorial> obtenerHistorial() const;

    // Devuelve todos los intereses registrados
    vector<Interes> obtenerIntereses() const;

    // Devuelve el historial de un estudiante especifico
    vector<RegistroHistorial> obtenerHistorialPorEstudiante(const string& estudiante) const;

    // Devuelve solo los cursos aprobados por un estudiante
    vector<RegistroHistorial> obtenerAprobados(const string& estudiante) const;

    // Devuelve solo los cursos desaprobados por un estudiante
    vector<RegistroHistorial> obtenerDesaprobados(const string& estudiante) const;

    // Calcula el promedio simple de notas de un estudiante
    double calcularPromedio(const string& estudiante) const;

    // Devuelve el registro con mayor nota de un estudiante
    RegistroHistorial obtenerMayorNota(const string& estudiante) const;

    // Devuelve el registro con menor nota de un estudiante
    RegistroHistorial obtenerMenorNota(const string& estudiante) const;
};

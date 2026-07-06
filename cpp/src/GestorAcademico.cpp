#include "GestorAcademico.h"

using namespace std;

// Reemplaza todos los vectores internos para trabajar sobre un solo conjunto coherente de datos
void GestorAcademico::cargarDatos(const vector<Curso>& nuevosCursos,
                                  const vector<Prerrequisito>& nuevosPrerrequisitos,
                                  const vector<RegistroHistorial>& nuevoHistorial,
                                  const vector<Interes>& nuevosIntereses) {
    cursos = nuevosCursos;
    prerrequisitos = nuevosPrerrequisitos;
    historial = nuevoHistorial;
    intereses = nuevosIntereses;
}

// Agrega un curso evitando codigos duplicados
bool GestorAcademico::agregarCurso(const Curso& curso) {
    if (existeCurso(curso.codigo)) {
        return false;
    }

    cursos.push_back(curso);
    return true;
}

// Agrega un prerrequisito solo si el curso y el prerrequisito ya existen
bool GestorAcademico::agregarPrerrequisito(const Prerrequisito& prerrequisito) {
    if (!existeCurso(prerrequisito.codigoCurso) || !existeCurso(prerrequisito.codigoPrerrequisito)) {
        return false;
    }

    prerrequisitos.push_back(prerrequisito);
    return true;
}

// Agrega una nota al historial verificando que el codigo del curso exista
bool GestorAcademico::agregarRegistroHistorial(const RegistroHistorial& registro) {
    if (!existeCurso(registro.codigoCurso)) {
        return false;
    }

    historial.push_back(registro);
    return true;
}

// Agrega un area de interes sin validar contra cursos porque puede usarse luego en Prolog
void GestorAcademico::agregarInteres(const Interes& interes) {
    intereses.push_back(interes);
}

// El sistema se considera vacio cuando no hay cursos cargados
bool GestorAcademico::estaVacio() const {
    return cursos.empty();
}

// Busca linealmente porque el proyecto pide uso simple de vectores y ciclos
bool GestorAcademico::existeCurso(const string& codigoCurso) const {
    for (const Curso& curso : cursos) {
        if (curso.codigo == codigoCurso) {
            return true;
        }
    }

    return false;
}

// Devuelve el nombre del curso para mostrar reportes mas claros al usuario
string GestorAcademico::buscarNombreCurso(const string& codigoCurso) const {
    for (const Curso& curso : cursos) {
        if (curso.codigo == codigoCurso) {
            return curso.nombre;
        }
    }

    return "Curso no encontrado";
}

// Entrega una copia del vector para que otras clases no modifiquen la data directamente
vector<Curso> GestorAcademico::obtenerCursos() const {
    return cursos;
}

// Entrega una copia de las relaciones de prerrequisitos registradas
vector<Prerrequisito> GestorAcademico::obtenerPrerrequisitos() const {
    return prerrequisitos;
}

// Entrega una copia del historial academico completo
vector<RegistroHistorial> GestorAcademico::obtenerHistorial() const {
    return historial;
}

// Entrega una copia de los intereses registrados
vector<Interes> GestorAcademico::obtenerIntereses() const {
    return intereses;
}

// Filtra el historial por identificador de estudiante usando un ciclo simple
vector<RegistroHistorial> GestorAcademico::obtenerHistorialPorEstudiante(const string& estudiante) const {
    vector<RegistroHistorial> resultado;

    for (const RegistroHistorial& registro : historial) {
        if (registro.estudiante == estudiante) {
            resultado.push_back(registro);
        }
    }

    return resultado;
}

// Filtra cursos aprobados aplicando la regla de nota mayor o igual a 11
vector<RegistroHistorial> GestorAcademico::obtenerAprobados(const string& estudiante) const {
    vector<RegistroHistorial> resultado;

    for (const RegistroHistorial& registro : historial) {
        if (registro.estudiante == estudiante && registro.nota >= 11) {
            resultado.push_back(registro);
        }
    }

    return resultado;
}

// Filtra cursos desaprobados aplicando la regla de nota menor a 11
vector<RegistroHistorial> GestorAcademico::obtenerDesaprobados(const string& estudiante) const {
    vector<RegistroHistorial> resultado;

    for (const RegistroHistorial& registro : historial) {
        if (registro.estudiante == estudiante && registro.nota < 11) {
            resultado.push_back(registro);
        }
    }

    return resultado;
}

// Calcula el promedio sumando las notas del estudiante y dividiendo entre su cantidad de cursos
 double GestorAcademico::calcularPromedio(const string& estudiante) const {
    double suma = 0;
    int cantidad = 0;

    for (const RegistroHistorial& registro : historial) {
        if (registro.estudiante == estudiante) {
            suma += registro.nota;
            cantidad++;
        }
    }

    if (cantidad == 0) {
        return 0;
    }

    return suma / cantidad;
}

// Obtiene el curso con mayor nota para el reporte general del estudiante
RegistroHistorial GestorAcademico::obtenerMayorNota(const string& estudiante) const {
    vector<RegistroHistorial> registros = obtenerHistorialPorEstudiante(estudiante);

    if (registros.empty()) {
        return {estudiante, "", 0};
    }

    RegistroHistorial mayor = registros[0];

    for (const RegistroHistorial& registro : registros) {
        if (registro.nota > mayor.nota) {
            mayor = registro;
        }
    }

    return mayor;
}

// Obtiene el curso con menor nota para el reporte general del estudiante
RegistroHistorial GestorAcademico::obtenerMenorNota(const string& estudiante) const {
    vector<RegistroHistorial> registros = obtenerHistorialPorEstudiante(estudiante);

    if (registros.empty()) {
        return {estudiante, "", 0};
    }

    RegistroHistorial menor = registros[0];

    for (const RegistroHistorial& registro : registros) {
        if (registro.nota < menor.nota) {
            menor = registro;
        }
    }

    return menor;
}

#include "SistemaAcademico.h"
#include "DatosPredeterminados.h"
#include "ReporteAcademico.h"
#include "Utilidades.h"

#include <iostream>

using namespace std;

// Define los nombres de los archivos CSV usados como integracion con Haskell y Prolog
SistemaAcademico::SistemaAcademico() {
    rutaCursos = "cursos.csv";
    rutaPrerrequisitos = "prerrequisitos.csv";
    rutaHistorial = "historial.csv";
    rutaIntereses = "intereses.csv";
}

// Carga los archivos existentes al iniciar el programa
void SistemaAcademico::cargarDesdeCsv() {
    vector<Curso> cursos = repositorio.cargarCursos(rutaCursos);
    vector<Prerrequisito> prerrequisitos = repositorio.cargarPrerrequisitos(rutaPrerrequisitos);
    vector<RegistroHistorial> historial = repositorio.cargarHistorial(rutaHistorial);
    vector<Interes> intereses = repositorio.cargarIntereses(rutaIntereses);

    gestor.cargarDatos(cursos, prerrequisitos, historial, intereses);
}

// Carga la data predeterminada solo cuando el usuario lo solicita desde el menu
void SistemaAcademico::cargarDatosPredeterminados() {
    if (!gestor.estaVacio()) {
        string respuesta = leerTextoNoVacio("Ya existen datos cargados. Desea reemplazarlos por los predeterminados? (s/n): ");

        if (respuesta != "s" && respuesta != "S") {
            cout << "No se cargaron los datos predeterminados\n";
            return;
        }
    }

    gestor.cargarDatos(
        DatosPredeterminados::obtenerCursos(),
        DatosPredeterminados::obtenerPrerrequisitos(),
        DatosPredeterminados::obtenerHistorial(),
        DatosPredeterminados::obtenerIntereses()
    );

    guardarTodo();
    cout << "Datos predeterminados cargados y guardados en CSV correctamente\n";
}

// Guarda los cuatro archivos CSV requeridos por el proyecto
void SistemaAcademico::guardarTodo() {
    repositorio.guardarCursos(rutaCursos, gestor.obtenerCursos());
    repositorio.guardarPrerrequisitos(rutaPrerrequisitos, gestor.obtenerPrerrequisitos());
    repositorio.guardarHistorial(rutaHistorial, gestor.obtenerHistorial());
    repositorio.guardarIntereses(rutaIntereses, gestor.obtenerIntereses());
}

// Muestra las opciones principales que evidencian el uso del paradigma imperativo
void SistemaAcademico::mostrarMenu() {
    cout << "\nSISTEMA INTELIGENTE DE RECOMENDACION ACADEMICA\n";
    cout << "1. Registrar curso\n";
    cout << "2. Registrar prerrequisito\n";
    cout << "3. Registrar nota de estudiante\n";
    cout << "4. Registrar area de interes\n";
    cout << "5. Mostrar cursos registrados\n";
    cout << "6. Mostrar historial de estudiante\n";
    cout << "7. Mostrar cursos aprobados\n";
    cout << "8. Mostrar cursos desaprobados\n";
    cout << "9. Mostrar reporte general\n";
    cout << "10. Cargar datos predeterminados\n";
    cout << "0. Salir\n";
}

// Lee los datos del curso y los agrega al gestor academico
void SistemaAcademico::registrarCurso() {
    Curso curso;

    cout << "\nAreas disponibles: General, Matematica, General_Ingenieria, General_Sistemas, Software, Procesos, Datos, IA, TI\n";
    curso.codigo = leerTextoNoVacio("Codigo del curso: ");
    curso.nombre = leerTextoNoVacio("Nombre del curso: ");
    curso.area = leerAreaAcademicaValida("Area academica: ");
    curso.creditos = leerEnteroEnRango("Creditos: ", 1, 8);

    if (gestor.agregarCurso(curso)) {
        guardarTodo();
        cout << "Curso registrado correctamente\n";
    } else {
        cout << "No se registro el curso porque el codigo ya existe\n";
    }
}

// Lee una relacion curso-prerrequisito y valida que ambos cursos existan
void SistemaAcademico::registrarPrerrequisito() {
    Prerrequisito prerrequisito;

    prerrequisito.codigoCurso = leerTextoNoVacio("Codigo del curso: ");
    prerrequisito.codigoPrerrequisito = leerTextoNoVacio("Codigo del prerrequisito: ");

    if (gestor.agregarPrerrequisito(prerrequisito)) {
        guardarTodo();
        cout << "Prerrequisito registrado correctamente\n";
    } else {
        cout << "No se registro el prerrequisito porque algun curso no existe\n";
    }
}

// Lee la nota obtenida por un estudiante y la guarda en el historial
void SistemaAcademico::registrarNota() {
    RegistroHistorial registro;

    registro.estudiante = leerTextoNoVacio("Identificador del estudiante: ");
    registro.codigoCurso = leerTextoNoVacio("Codigo del curso: ");
    registro.nota = leerDecimalEnRango("Nota obtenida: ", 0, 20);

    if (gestor.agregarRegistroHistorial(registro)) {
        guardarTodo();
        cout << "Nota registrada correctamente\n";
    } else {
        cout << "No se registro la nota porque el curso no existe\n";
    }
}

// Lee un area de interes y la guarda para que luego pueda usarse en recomendaciones
void SistemaAcademico::registrarInteres() {
    Interes interes;

    cout << "\nAreas disponibles: General, Matematica, General_Ingenieria, General_Sistemas, Software, Procesos, Datos, IA, TI\n";
    interes.estudiante = leerTextoNoVacio("Identificador del estudiante: ");
    interes.area = leerAreaAcademicaValida("Area de interes: ");

    if (gestor.agregarInteres(interes)) {
        guardarTodo();
        cout << "Interes registrado correctamente\n";
    } else {
        cout << "No se registro el interes porque el area no es valida\n";
    }
}

// Recorre todos los cursos y muestra codigo, nombre, area y creditos
void SistemaAcademico::mostrarCursos() {
    vector<Curso> cursos = gestor.obtenerCursos();

    cout << "\nCURSOS REGISTRADOS\n";

    if (cursos.empty()) {
        cout << "No hay cursos registrados\n";
        return;
    }

    for (const Curso& curso : cursos) {
        cout << curso.codigo << " | " << curso.nombre << " | " << curso.area << " | " << curso.creditos << " creditos\n";
    }
}

// Muestra todas las notas registradas para un estudiante
void SistemaAcademico::mostrarHistorial() {
    string estudiante = leerTextoNoVacio("Identificador del estudiante: ");
    vector<RegistroHistorial> registros = gestor.obtenerHistorialPorEstudiante(estudiante);

    if (registros.empty()) {
        cout << "No existe historial para el estudiante indicado\n";
        return;
    }

    cout << "\nHISTORIAL DE " << estudiante << "\n";

    for (const RegistroHistorial& registro : registros) {
        cout << registro.codigoCurso << " | " << gestor.buscarNombreCurso(registro.codigoCurso) << " | Nota: " << registro.nota << "\n";
    }
}

// Muestra cursos aprobados o desaprobados segun el parametro recibido
void SistemaAcademico::mostrarCursosPorEstado(bool aprobados) {
    string estudiante = leerTextoNoVacio("Identificador del estudiante: ");
    vector<RegistroHistorial> registros;

    if (aprobados) {
        registros = gestor.obtenerAprobados(estudiante);
        cout << "\nCURSOS APROBADOS\n";
    } else {
        registros = gestor.obtenerDesaprobados(estudiante);
        cout << "\nCURSOS DESAPROBADOS\n";
    }

    if (registros.empty()) {
        cout << "No hay cursos para mostrar\n";
        return;
    }

    for (const RegistroHistorial& registro : registros) {
        cout << registro.codigoCurso << " | " << gestor.buscarNombreCurso(registro.codigoCurso) << " | Nota: " << registro.nota << "\n";
    }
}

// Solicita un estudiante y delega la impresion del reporte a ReporteAcademico
void SistemaAcademico::mostrarReporteGeneral() {
    string estudiante = leerTextoNoVacio("Identificador del estudiante: ");
    ReporteAcademico::mostrarReporteGeneral(gestor, estudiante);
}

// Ejecuta el ciclo del menu hasta que el usuario decida salir
void SistemaAcademico::iniciar() {
    cargarDesdeCsv();

    int opcion;

    do {
        mostrarMenu();
        opcion = leerEnteroEnRango("Seleccione una opcion: ", 0, 10);

        switch (opcion) {
            case 1:
                registrarCurso();
                break;
            case 2:
                registrarPrerrequisito();
                break;
            case 3:
                registrarNota();
                break;
            case 4:
                registrarInteres();
                break;
            case 5:
                mostrarCursos();
                break;
            case 6:
                mostrarHistorial();
                break;
            case 7:
                mostrarCursosPorEstado(true);
                break;
            case 8:
                mostrarCursosPorEstado(false);
                break;
            case 9:
                mostrarReporteGeneral();
                break;
            case 10:
                cargarDatosPredeterminados();
                break;
            case 0:
                cout << "Saliendo del sistema\n";
                break;
        }
    } while (opcion != 0);
}

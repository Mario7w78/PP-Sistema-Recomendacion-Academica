:- use_module(library(csv)).
:- initialization(cargar_datos_inicial).

% Construye la ruta completa del CSV dentro de ../cpp.
ruta_csv(Nombre, Ruta) :-
    source_file(cargar_datos_inicial, Archivo),
    file_directory_name(Archivo, Directorio),
    atomic_list_concat([Directorio, '/../cpp/', Nombre], Ruta).

% Descarta la fila de encabezado del CSV.
limpiar_encabezado([_|Datos], Datos).

cargar_datos_inicial :-
    cargar_datos(_, _, _, _).

% Lee un CSV, elimina el encabezado y guarda cada fila como hecho.
leer_csv(Archivo, Predicado, Datos) :-
    ruta_csv(Archivo, Ruta),
    csv_read_file(Ruta, Filas, [functor(Predicado)]),
    limpiar_encabezado(Filas, DatosSinEncabezado),
    Datos = DatosSinEncabezado,
    maplist(assertz, DatosSinEncabezado).

% Recarga los hechos de los cuatro CSV en memoria.
cargar_datos(Cursos, Historial, Intereses, Prerrequisitos) :-
    retractall(curso(_, _, _, _)),
    retractall(historial(_, _, _)),
    retractall(interes(_, _)),
    retractall(prerrequisitos(_, _)),

    leer_csv('cursos.csv', curso, Cursos),
    leer_csv('historial.csv', historial, Historial),
    leer_csv('intereses.csv', interes, Intereses),
    leer_csv('prerrequisitos.csv', prerrequisitos, Prerrequisitos).

% Estudiante aprueba curso si su nota es >= 11.
aprobado(Estudiante, Curso) :-
    historial(Estudiante, Curso, Nota),
    Nota >= 11.

% Puede llevar un curso si aprobó sus prerrequisitos.
puede_llevar(Estudiante, Curso) :-
    prerrequisitos(Curso, Prerequisito),
    aprobado(Estudiante, Prerequisito).

recomendar_cursos(Estudiante, Cursos) :-
    findall(Curso, puede_llevar(Estudiante, Curso), Cursos).

curso_bloqueado(Estudiante, Cursos) :-
    findall(Curso,
        (prerrequisitos(Curso, Prerequisito), not(aprobado(Estudiante, Prerequisito))),
        Cursos).

% Busca cursos con las áreas de interés del estudiante.
recomendar_por_interes(Estudiante, Cursos) :-
    findall(Curso,
        (interes(Estudiante, Area), curso(Curso, _, Area, _)),
        Cursos). 
# Modulo C++ - Sistema Inteligente de Recomendacion Academica

Este modulo implementa la parte imperativa del proyecto usando C++

## Estructura

```text
modulo_cpp/
├── main.cpp
├── include/
│   ├── DatosPredeterminados.h
│   ├── GestorAcademico.h
│   ├── Modelos.h
│   ├── ReporteAcademico.h
│   ├── RepositorioCsv.h
│   ├── SistemaAcademico.h
│   └── Utilidades.h
└── src/
    ├── DatosPredeterminados.cpp
    ├── GestorAcademico.cpp
    ├── ReporteAcademico.cpp
    ├── RepositorioCsv.cpp
    ├── SistemaAcademico.cpp
    └── Utilidades.cpp
```

## Responsabilidad de cada clase

- `SistemaAcademico`: controla el menu y conecta las clases del sistema
- `GestorAcademico`: agrega datos y realiza consultas sobre cursos, notas e intereses
- `RepositorioCsv`: lee y guarda los cuatro archivos CSV
- `DatosPredeterminados`: carga cursos, prerrequisitos, historial e intereses iniciales
- `ReporteAcademico`: genera el reporte general de un estudiante
- `Utilidades`: contiene funciones de lectura de consola y separacion CSV

## Compilacion

Desde la carpeta `modulo_cpp`:

```bash
g++ -std=c++17 main.cpp src/*.cpp -Iinclude -o sistema
```

En Windows con MinGW:

```bash
g++ -std=c++17 main.cpp src/*.cpp -Iinclude -o sistema.exe
```

## Ejecucion

Linux o macOS:

```bash
./sistema
```

Windows:

```bash
sistema.exe
```

## Flujo del programa

Al iniciar, el programa intenta leer estos archivos si ya existen:

- `cursos.csv`
- `prerrequisitos.csv`
- `historial.csv`
- `intereses.csv`

Si no existen, el sistema empieza vacio y no crea ningun CSV automaticamente

Cada vez que se registra un curso, prerrequisito, nota o interes, el programa guarda automaticamente los cambios en los cuatro CSV

La opcion `10. Cargar datos predeterminados` carga cursos de la malla curricular y crea los CSV con esa data inicial

## Menu principal

```text
1. Registrar curso
2. Registrar prerrequisito
3. Registrar nota de estudiante
4. Registrar area de interes
5. Mostrar cursos registrados
6. Mostrar historial de estudiante
7. Mostrar cursos aprobados
8. Mostrar cursos desaprobados
9. Mostrar reporte general
10. Cargar datos predeterminados
0. Salir
```

## Areas usadas

- General
- Matematica
- General_Ingenieria
- General_Sistemas
- Software
- Procesos
- Datos
- IA
- TI

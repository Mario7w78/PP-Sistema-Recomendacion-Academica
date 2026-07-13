# PP-Sistema-Recomendacion-Academica

Proyecto de Paradigmas de Programación. Simula un sistema de recomendación académica implementado con tres paradigmas distintos, cada uno en su propio módulo:

- **cpp/** — Paradigma imperativo. Registra cursos, prerrequisitos, notas e intereses del estudiante, y guarda todo en archivos CSV.
- **haskell/** — Paradigma funcional. Lee `historial.csv` generado por el módulo C++ y calcula promedios, cursos aprobados/desaprobados y una recomendación según el rendimiento.
- **prolog/** — Paradigma lógico. Consulta los CSV generados por C++ para recomendar cursos disponibles, detectar cursos bloqueados por prerrequisitos y sugerir cursos por área de interés.

Cada carpeta tiene su propio `README.md` con instrucciones detalladas de compilación y ejecución.

## Flujo general

1. Ejecutar el módulo **C++** primero: genera y mantiene los archivos `cursos.csv`, `prerrequisitos.csv`, `historial.csv` e `intereses.csv` (usar la opción "Cargar datos predeterminados" si se quiere partir con datos de ejemplo).
2. Ejecutar el módulo **Haskell** para ver el análisis y recomendación del estudiante, en base al `historial.csv` generado.
3. Ejecutar el módulo **Prolog** para hacer consultas lógicas sobre cursos disponibles, bloqueados o recomendados por interés.

Los módulos Haskell y Prolog dependen de que los CSV ya existan en `cpp/`, así que el orden importa: sin datos generados por C++ no hay nada que analizar ni consultar.

## Cosas a considerar

- Los tres módulos comparten los mismos archivos CSV como fuente de datos; si se modifican manualmente hay que respetar el formato que usa el módulo C++.
- Cada vez que se registra algo nuevo desde el módulo C++, los CSV se sobrescriben automáticamente. Si Haskell o Prolog ya estaban abiertos, hay que volver a ejecutarlos (o recargar datos en Prolog) para ver los cambios.
- El módulo Haskell asume que se ejecuta desde la carpeta `haskell/` y busca los CSV en `../cpp/`.
- El módulo Prolog asume que los CSV están en `../cpp/` respecto a `prolog/`.
- Los binarios (`.exe`, `.dll`, `.hi`, `.o`) están incluidos para conveniencia, pero pueden regenerarse siguiendo las instrucciones de compilación de cada README.

## Requisitos

- Compilador C++ compatible con C++17 (g++/MinGW en Windows).
- GHC (Glasgow Haskell Compiler) para el módulo funcional.
- SWI-Prolog para el módulo lógico.

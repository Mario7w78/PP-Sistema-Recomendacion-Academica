# Módulo Haskell — Sistema de Recomendación Académica

Módulo funcional del proyecto. Lee el archivo `historial.csv` generado por el módulo C++ y genera un
resumen académico del estudiante con recomendaciones según su rendimiento.

## Requisitos

- GHC (Glasgow Haskell Compiler) 8.0 o superior
- Solo usa paquetes de `base` (no requiere Cabal ni Stack)

## Estructura del módulo

```
sistema_academico/
├── cpp/                  # Módulo C++ (imperativo)
│   ├── main.cpp
│   ├── src/
│   ├── include/
│   └── ...
└── haskell/              # Módulo Haskell (funcional)
    ├── Main.hs           # Programa principal (punto de entrada)
    ├── src/
    │   ├── Tipos.hs      # Definición del tipo Registro
    │   ├── Lectura.hs    # Lectura de CSV con split recursivo
    │   ├── Analisis.hs   # Funciones de análisis (promedio, filtros)
    │   └── Recomendacion.hs # Recomendación textual
    └── README.md
```

## Compilación

Ejecutar desde el directorio `sistema_academico/haskell/`:

```bash
cd haskell
ghc -Wall -isrc Main.hs -o modulo_haskell
```

Esto genera el ejecutable `modulo_haskell.exe`.

## Ejecución

### Desde el ejecutable compilado:

```bash
cd sistema_academico/haskell
modulo_haskell.exe
```

### Sin compilar (interpretado):

```bash
cd sistema_academico/haskell
runghc -isrc Main.hs
```

> **Importante**: El programa debe ejecutarse desde el directorio `haskell/`. Busca el archivo
> `historial.csv` en la carpeta hermana `cpp/` (`../cpp/historial.csv`).
> Si los CSV están en otra ubicación, modifica la variable `rutaHistorial` en `Main.hs`.

## Flujo de trabajo con C++ y Prolog

1. Ejecuta el programa C++ para generar los archivos CSV (`cursos.csv`, `prerrequisitos.csv`,
   `historial.csv`, `intereses.csv`) desde `cpp/`.
2. El módulo Haskell lee `historial.csv` desde la carpeta hermana `cpp/`.
3. Ejecuta este módulo Haskell desde `haskell/` para ver el análisis del estudiante.
4. (Opcional) Ejecuta el módulo Prolog para consultas lógicas.

## Correspondencia con el enunciado

| Punto | Descripción | Archivo |
|-------|-------------|---------|
| (a) | Lectura de historial.csv | `Lectura.hs` — `leerHistorial` |
| (b) | Definición de tipos | `Tipos.hs` — tipo `Registro` |
| (c) | Calcular promedio | `Analisis.hs` — `promedio` |
| (d) | Cursos aprobados (nota >= 11) | `Analisis.hs` — `aprobados` |
| (e) | Cursos desaprobados (nota < 11) | `Analisis.hs` — `desaprobados` |
| (f) | Clasificar rendimiento (Alto/Medio/Bajo) | `Analisis.hs` — `clasificarRendimiento` |
| (g) | Recomendación según rendimiento | `Recomendacion.hs` — `recomendar` |
| (h) | Conteo de cursos aprobados/desaprobados | `Analisis.hs` (usando `length`) |
| (i) | Resumen del estudiante | `Main.hs` — salida formateada |

## Evidencias del paradigma funcional

- **Tipos propios**: `Registro` con sus campos (`Tipos.hs`)
- **Funciones puras**: `promedio`, `aprobados`, `desaprobados` (`Analisis.hs`)
- **Recursión explícita**: `splitComa` para dividir CSV (`Lectura.hs`)
- **Funciones de orden superior**: `filter` en `aprobados`, `desaprobados`, `porEstudiante`;
  `foldl'` en `promedio`; `map` en `codigosCursos` (`Analisis.hs`)
- **Pattern matching**: en `recomendar`, `clasificarRendimiento`, `splitComa` (`Recomendacion.hs`,
  `Analisis.hs`, `Lectura.hs`)
- **Manejo de errores sin excepciones**: uso de `Maybe` y `Either` en la lectura de CSV (`Lectura.hs`)

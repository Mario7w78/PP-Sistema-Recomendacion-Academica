# Módulo Prolog — Sistema de Recomendación Académica

Este módulo usa SWI-Prolog para consultar los datos generados en `cpp/` y recomendar cursos.

## Requisitos

- SWI-Prolog instalado en Windows
- Archivos CSV en la carpeta `cpp/`
- El archivo principal es `prolog/swish.pl`

## Estructura del módulo

```text
prolog/
├── swish.pl
├── iniciar_prolog.bat
└── README.md
```

## Cómo ejecutar

1. Abre una terminal en la carpeta `prolog/`.
2. Ejecuta el lanzador:

```powershell
cd prolog
.\iniciar_prolog.bat
```

3. Si no se carga automáticamente, en la consola de Prolog usa:

```prolog
?- consult('swish.pl').
```

4. Carga los datos desde los CSV:

```prolog
?- cargar_datos(Cursos, Historial, Intereses, Prerrequisitos).
```

## Consultas básicas

- Cargar datos:

```prolog
?- cargar_datos(Cursos, Historial, Intereses, Prerrequisitos).
```

- Cursos que puede llevar un estudiante:

```prolog
?- recomendar_cursos(estudiante1, Cursos).
```

- Cursos bloqueados por prerrequisitos:

```prolog
?- curso_bloqueado(estudiante1, Cursos).
```

- Cursos recomendados por interés:

```prolog
?- recomendar_por_interes(estudiante1, Cursos).
```

## Notas

- El módulo Prolog usa los CSV de `../cpp/`.
- Si modificas los CSV, vuelve a ejecutar `cargar_datos/4`.
- Los predicados principales son:
  - `curso/4`
  - `historial/3`
  - `interes/2`
  - `prerrequisitos/2`

## Flujo de uso

1. Genera o actualiza los CSV desde el módulo C++.
2. Abre `prolog/iniciar_prolog.bat`.
3. Ejecuta las consultas en SWI-Prolog.

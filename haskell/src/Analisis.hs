-- | Analisis.hs
-- Funciones puras para analizar el historial academico del estudiante.
-- Demuestra el uso de filter, fold, map y funciones de orden superior.
-- Corresponde a los puntos (c), (d), (e), (f) y (h) del enunciado:
--   (c) Calcular promedio general
--   (d) Filtrar cursos aprobados
--   (e) Filtrar cursos desaprobados
--   (f) Clasificar rendimiento
--   (h) Conteo de cursos aprobados y desaprobados
module Analisis
  ( porEstudiante
  , promedio
  , aprobados
  , desaprobados
  , clasificarRendimiento
  , codigosCursos
  , mostrarAprobados
  , mostrarDesaprobados
  ) where

import Tipos (Registro(..))
import Data.Char (toLower)

-- | Filtra los registros que pertenecen a un estudiante especifico.
-- Usa filter (funcion de orden superior).
porEstudiante :: String -> [Registro] -> [Registro]
porEstudiante est = filter (\r -> map toLower (estudiante r) == map toLower est)
-- Nota: comparacion sin distincion de mayusculas/minusculas


-- | Calcula el promedio general de notas a partir de una lista de registros.
-- Usa foldl' (fold) para sumar las notas de forma eficiente.
-- Si la lista esta vacia, devuelve 0 para evitar division entre cero.
promedio :: [Registro] -> Double
promedio [] = 0.0
promedio registros = suma / fromIntegral cantidad
  where
    -- foldl' suma todas las notas acumulativamente
    suma    = foldl' (\acc r -> acc + nota r) 0.0 registros
    cantidad = length registros


-- | Filtra los cursos aprobados (nota >= 11)
-- Usa filter explicitamente, como requiere el enunciado.
aprobados :: [Registro] -> [Registro]
aprobados = filter (\r -> nota r >= 11.0)


-- | Filtra los cursos desaprobados (nota < 11)
-- Usa filter explicitamente, como requiere el enunciado.
desaprobados :: [Registro] -> [Registro]
desaprobados = filter (\r -> nota r < 11.0)


-- | Clasifica el rendimiento del estudiante segun su promedio.
-- Corresponde al punto (f) del enunciado:
--   Alto   -> promedio >= 16
--   Medio  -> 13 <= promedio < 16
--   Bajo   -> promedio < 13
clasificarRendimiento :: Double -> String
clasificarRendimiento prom
    | prom >= 16.0 = "Alto"
    | prom >= 13.0 = "Medio"
    | otherwise    = "Bajo"


-- | Extrae los codigos de curso de una lista de registros.
codigosCursos :: [Registro] -> [String]
codigosCursos = map curso


-- | Concatena los codigos de cursos aprobados separados por coma.
mostrarAprobados :: [Registro] -> String
mostrarAprobados = mostrarCursos . codigosCursos . aprobados


-- | Concatena los codigos de cursos desaprobados separados por coma.
mostrarDesaprobados :: [Registro] -> String
mostrarDesaprobados = mostrarCursos . codigosCursos . desaprobados


-- | Concatena una lista de Strings separados por ", "
mostrarCursos :: [String] -> String
mostrarCursos [] = "Ninguno"
mostrarCursos cs = foldl1 (\acc c -> acc ++ ", " ++ c) cs


-- Nota: foldl' esta disponible directamente en Prelude desde GHC 8.x+,
-- asi que no necesitamos definirlo manualmente. Evita la dependencia de Data.List.

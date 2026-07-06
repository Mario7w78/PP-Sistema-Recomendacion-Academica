-- | Main.hs
-- Programa principal del modulo Haskell del Sistema de Recomendacion Academica.
--
-- Funcionamiento:
--   1. Solicita al usuario el identificador del estudiante por consola.
--   2. Lee el archivo historial.csv generado por el modulo C++.
--   3. Filtra los registros del estudiante ingresado.
--   4. Calcula promedio, cursos aprobados/desaprobados, rendimiento y recomendacion.
--   5. Muestra el resumen academico en el formato especificado por el enunciado.
--
-- Corresponde al punto (i) del enunciado: mostrar el resumen del estudiante.
module Main where

import System.IO (stdout, hFlush)

import Lectura (leerHistorial)
import Analisis (porEstudiante, promedio, aprobados, desaprobados,
                 clasificarRendimiento, mostrarAprobados, mostrarDesaprobados)
import Recomendacion (recomendar)


-- | Ruta al archivo historial.csv generado por el modulo C++.
-- Se asume que el programa se ejecuta desde el directorio 'haskell/'
-- y que el C++ genera los CSVs en 'cpp/' (la carpeta hermana).
rutaHistorial :: FilePath
rutaHistorial = "..\\cpp\\historial.csv"


-- | Punto de entrada del programa.
-- Lee el identificador del estudiante desde consola y muestra el resumen academico.
main :: IO ()
main = do
    -- Mostrar encabezado del sistema
    putStrLn "=========================================="
    putStrLn " SISTEMA DE RECOMENDACION ACADEMICA"
    putStrLn " Modulo Haskell - Analisis de Rendimiento"
    putStrLn "=========================================="
    putStrLn ""

    -- Solicitar identificador del estudiante (interactivo, como el menu de C++)
    putStr "Ingrese el identificador del estudiante: "
    hFlush stdout  -- Forzar la salida del prompt antes de leer
    identificador <- getLine

    -- Validar que el usuario haya ingresado algo
    if null identificador
        then do
            putStrLn "No se ingreso ningun identificador. Saliendo..."
            return ()
        else do
            -- Leer el historial desde el archivo CSV
            putStrLn $ "Leyendo: " ++ rutaHistorial
            todosRegistros <- leerHistorial rutaHistorial

            if null todosRegistros
                then do
                    -- Si no hay registros, ya se mostro el error en leerHistorial
                    putStrLn "No hay datos disponibles. Finalizando."
                else do
                    -- Filtrar registros del estudiante solicitado
                    let registrosEst = porEstudiante identificador todosRegistros

                    -- Verificar si el estudiante existe en el historial
                    if null registrosEst
                        then do
                            putStrLn ""
                            putStrLn $ "El estudiante '" ++ identificador ++ "' no tiene registros en el historial."
                            putStrLn "Verifique el identificador e intente nuevamente."
                        else do
                            -- Calcular metricas academicas
                            let prom           = promedio registrosEst
                            let rendimiento    = clasificarRendimiento prom
                            let recomendacion  = recomendar rendimiento
                            let aprobadosStr   = mostrarAprobados registrosEst
                            let desaprobadosStr = mostrarDesaprobados registrosEst
                            let countAprob     = length (aprobados registrosEst)
                            let countDesaprob  = length (desaprobados registrosEst)

                            -- Mostrar resumen en el formato exacto del enunciado
                            putStrLn ""
                            putStrLn "------------------------------------------"
                            putStrLn "         RESUMEN ACADEMICO"
                            putStrLn "------------------------------------------"
                            putStrLn $ "Estudiante: " ++ identificador
                            putStrLn $ "Promedio: "   ++ mostrarPromedio prom
                            putStrLn $ "Cursos aprobados: "   ++ aprobadosStr
                            putStrLn $ "Cursos desaprobados: " ++ desaprobadosStr
                            putStrLn $ "Rendimiento: " ++ rendimiento
                            putStrLn $ "Recomendacion: " ++ recomendacion
                            putStrLn "------------------------------------------"
                            putStrLn $ "(Aprobados: " ++ show countAprob
                                    ++ " | Desaprobados: " ++ show countDesaprob ++ ")"
                            putStrLn "=========================================="


-- | Muestra el promedio formateado con un decimal.
-- Ejemplo: 12.0 en vez de 12.0 o 12.0000000000001
mostrarPromedio :: Double -> String
mostrarPromedio prom = show (round10 / 10.0)
  where
    round10 :: Double
    round10 = fromIntegral (round (prom * 10) :: Int)


-- Nota sobre el flujo del programa:
-- 1. Entrada interactiva (getLine): el usuario ingresa el ID del estudiante
-- 2. Lectura de CSV con manejo de errores (Lectura.leerHistorial)
-- 3. Filtrado puro con filter (Analisis.porEstudiante)
-- 4. Calculo de promedio con fold (Analisis.promedio)
-- 5. Clasificacion y recomendacion (Analisis.clasificarRendimiento, Recomendacion.recomendar)
-- 6. Salida formateada

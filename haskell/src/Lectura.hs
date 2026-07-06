-- | Lectura.hs
-- Lectura del archivo historial.csv usando recursion para el split por comas.
-- Corresponde a los puntos (a) y (b) del enunciado:
--   (a) Lectura del archivo historial.csv
--   (b) Demostracion de recursion (splitComa)
module Lectura
  ( leerHistorial
  , splitComa
  ) where

import Tipos (Registro(..))
import System.IO (IOMode(ReadMode), Handle, hGetContents, hClose, openFile)
import System.IO.Error (isDoesNotExistError)
import Control.Exception (try, IOException)

-- | Parte una cadena en subcadenas separadas por coma usando recursion explícita.
-- Esta funcion demuestra el uso de recursion que solicita el enunciado.
-- Ejemplo: splitComa "a,b,c" == ["a","b","c"]
splitComa :: String -> [String]
splitComa "" = [""]       -- Caso base: cadena vacia -> lista con string vacio
splitComa cs = case break (== ',') cs of
    -- break parte la cadena en dos: el prefijo antes de la coma y el resto
    (campo, ',' : resto) -> campo : splitComa resto
    (campo, _)           -> [campo]  -- No hay mas comas, ultimo campo


-- | Convierte una linea de texto (sin cabecera) en un Registro.
-- Formato esperado: estudiante,codigoCurso,nota
-- Ejemplo: "estudiante1,CS101,15" -> Registro "estudiante1" "CS101" 15.0
parsearLinea :: String -> Maybe Registro
parsearLinea linea = case splitComa linea of
    -- Esperamos exactamente 3 campos: estudiante, curso, nota
    [est, cur, nt] -> case reads nt of
        [(n, "")] -> Just (Registro est cur n)
        _         -> Nothing  -- La nota no es un numero valido
    _ -> Nothing  -- La linea no tiene 3 campos


-- | Lee el archivo historial.csv y devuelve una lista de Registros.
-- Descarta automaticamente la primera linea (cabecera).
-- Si el archivo no existe, muestra un mensaje de error claro y devuelve [].
-- Si hay lineas vacias al final, las ignora silenciosamente.
leerHistorial :: FilePath -> IO [Registro]
leerHistorial ruta = do
    -- Intentamos abrir el archivo; si no existe, manejamos el error
    resultado <- try (openFile ruta ReadMode) :: IO (Either IOException Handle)
    case resultado of
        Left err
            -- Error especifico: archivo no encontrado
            | isDoesNotExistError err -> do
                putStrLn $ "ERROR: No se encontro el archivo '" ++ ruta ++ "'."
                putStrLn "Asegurate de haber ejecutado primero el programa C++ para generar los archivos CSV."
                putStrLn "O verifica la ruta del archivo."
                return []
            -- Cualquier otro error de E/S
            | otherwise -> do
                putStrLn $ "ERROR DE LECTURA: " ++ show err
                return []
        Right manejador -> do
            contenido <- hGetContents manejador
            -- Procesamos el contenido( lazy IO: evaluar antes de cerrar)
            let lineas = lines contenido
            -- Descartamos cabecera (primera linea) y procesamos el resto
            let cuerpo = drop 1 lineas
            -- Filtramos lineas vacias y parseamos cada linea
            let registros = mapMaybe parsearLinea (filter (not . null) cuerpo)
            -- Forzamos la evaluacion antes de cerrar (lazy IO)
            length registros `seq` hClose manejador
            return registros


-- | Version de mapMaybe para evitar dependencias externas.
-- Filtra los Nothing y extrae los Just de una lista de Maybe.
mapMaybe :: (a -> Maybe b) -> [a] -> [b]
mapMaybe _ [] = []
mapMaybe f (x:xs) = case f x of
    Just y  -> y : mapMaybe f xs
    Nothing -> mapMaybe f xs

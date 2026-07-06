-- | Tipos.hs
-- Definicion de tipos de datos para el Sistema de Recomendacion Academica.
-- Corresponde al punto (b) del enunciado: uso de tipos propios para representar notas.
module Tipos where

-- | Representa un registro del historial academico de un estudiante.
-- Cada registro contiene el identificador del estudiante, el codigo del curso
-- y la nota obtenida (escala 0-20).
data Registro = Registro
  { estudiante :: String  -- ^ Identificador del estudiante (ej: "estudiante1")
  , curso      :: String  -- ^ Codigo del curso (ej: "CS101")
  , nota       :: Double  -- ^ Nota obtenida (aprobado si >= 11)
  } deriving (Show, Eq)

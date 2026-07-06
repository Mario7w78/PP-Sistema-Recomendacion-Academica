-- | Recomendacion.hs
-- Genera una recomendacion textual segun el rendimiento academico del estudiante.
-- Corresponde al punto (g) del enunciado:
--   (g) Funcion para generar una recomendacion segun rendimiento
module Recomendacion
  ( recomendar
  ) where

-- | Genera una recomendacion textual basada en la clasificacion de rendimiento.
-- Los textos para "Alto" y "Bajo" siguen exactamente los ejemplos del enunciado.
-- Para "Medio" se genera un texto coherente con la situacion intermedia.
recomendar :: String -> String
recomendar "Alto"   = "El estudiante tiene buen rendimiento. Puede llevar cursos de mayor dificultad."
recomendar "Medio"  = "El estudiante tiene un rendimiento aceptable. Se recomienda reforzar areas debiles antes de avanzar."
recomendar "Bajo"   = "Se recomienda reforzar cursos base antes de llevar cursos avanzados."
recomendar _        = "No se puede generar una recomendacion."

-- Nota: Usamos pattern matching, una caracteristica clave de la programacion
-- funcional en Haskell, para mapear cada nivel de rendimiento a su texto.

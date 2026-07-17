# IMPROVEMENT_ROADMAP — XMLDocument-TreeBuilder

Backlog priorizado. Impacto/Esfuerzo: Alto/Medio/Bajo.

## Quick Wins

| # | Mejora | Impacto | Esfuerzo | Prioridad |
|---|---|---|---|---|
| 1 | Commitear el untracking de `xml_builder.exe` y el fix del link de imagen (aplicados en esta revisión) | Medio | Bajo | P0 |
| 2 | GitHub Topics: `cpp`, `data-structures`, `splay-tree`, `xml`, `header-only` + descripción que mencione el splay tree | Medio | Bajo | P1 |
| 3 | Destacar el splay tree en el README (hoy ni lo menciona — es el mayor activo técnico del repo) | Alto | Bajo | P0 |

## Mejoras técnicas

| # | Mejora | Impacto | Esfuerzo | Prioridad |
|---|---|---|---|---|
| 4 | Convertir `main.cpp` en suite de asserts (crear árbol → editar en 4 modos → serializar → comparar golden string) y ejecutarla en CI | Alto | Bajo | P1 |
| 5 | Job de CI en Linux con g++ (el README ya documenta ese comando) además del MSVC actual | Medio | Bajo | P1 |
| 6 | Chequeo de límites en los buffers de `buildXMLString`/`buildTreeView` (o tamaño calculado dinámicamente) | Medio | Medio | P2 |

## Mejoras arquitectónicas

| # | Mejora | Impacto | Esfuerzo | Prioridad |
|---|---|---|---|---|
| 7 | Documentar la complejidad amortizada del splay en comentario de cabecera (material de entrevista) | Bajo | Bajo | P2 |

## Mejoras de GitHub

Ya presentes: badge CI, LICENSE, `.gitignore` con `*.exe`, enunciado en docs. Faltan: Topics (item 2), README que venda el splay tree (item 3).

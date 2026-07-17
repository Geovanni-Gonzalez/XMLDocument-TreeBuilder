# TECHNICAL_REVIEW — XMLDocument-TreeBuilder

Fecha de revisión: 2026-07-16
Método: análisis estático, enunciado (`docs/Enunciado_ArchivosXML_PY03.md`), CI y git. Sin ejecución en esta pasada; CI compila con MSVC (`cl /W4`).

## 1. Comprensión del proyecto

Librería C++ header-only (~890 LOC) para construir documentos XML bien formados en memoria: árbol de nodos con atributos, serialización indentada a archivo, y — el requisito distintivo del enunciado — un **árbol splay implementado desde cero** para la búsqueda de nodos por id. Sin STL de strings: `StringLib.hpp` propio (len/copy/cmp/dup/cat/find/replace sobre `char*`).

## 2. Cumplimiento del enunciado

| Requisito | Estado | Evidencia |
|---|---|---|
| Clase `XMLDocument` en `XMLDocument.hpp`, incluible como header | ✅ | Header-only, plantilla pública respetada (constantes `ADD/OVR/APD`) |
| Librería sin I/O de consola (solo parámetros y retornos bool) | ✅ | Métodos retornan `bool`/buffers; demo separada en `main.cpp` (excluida de evaluación por el enunciado) |
| Insertar raíz, seleccionar, agregar hijo, eliminar | 🟦 | `Select(id)`, `AddChild`, `deleteSplay` + eliminación en árbol |
| Editar atributos/contenido en 4 modos (agregar/adjuntar/sobreescribir/borrar) | ✅ estático | `EditAttribute(key, value, mode)`, `EditContent` — los 4 modos con manejo manual de `malloc`/concatenación |
| **Subárbol splay (biselado)** | ✅ estático | `SplayNode`, `rotate`, `splay`, `insertSplay`, `deleteSplay` en `XMLDocument.hpp` |
| Visualizar subárbol / nodo / previsualizar XML | 🟦 | `buildTreeView`, `buildXMLString` (indentación, BEG/END de contenido) |
| Guardar a archivo | 🟦 | serialización a buffer + escritura |

## 3. Fortalezas

1. **Splay tree a mano** (rotaciones zig/zig-zig/zig-zag vía `rotate`+`splay`) — estructura de datos avanzada poco común en portafolios.
2. Cumplimiento estricto de un contrato de API impuesto (plantilla pública, sin I/O) — trabajo "contra especificación", como en la industria.
3. Gestión manual de memoria consistente: destructores en `Attribute`/`XMLNode`, `free`/`malloc` pareados, `StringLib::dup` para ownership.
4. CI en MSVC con `/W4` (warnings altos).

## 4. Debilidades y riesgos

| Hallazgo | Severidad | Nota |
|---|---|---|
| Buffers de serialización de tamaño fijo (`char buffer[]` + `pos`) sin chequeo de desborde visible | Media | Riesgo clásico; documentar límite o crecer dinámicamente |
| Sin tests automatizados (la demo `main.cpp` no asevera) | Media | Asserts sobre la librería serían baratos |
| ~~`xml_builder.exe` trackeado~~ | — | Corregido: `git rm --cached` (el patrón `*.exe` ya estaba en `.gitignore`) |
| CI solo Windows/MSVC; no compila en g++ como sugiere el README | Baja | Añadir job Linux |

## 5. Evaluación profesional

- Nivel demostrado: **Mid en estructuras de datos C++**. El splay tree y el contrato de API elevan el nivel; la falta de tests y los buffers fijos lo mantienen fuera de Mid+.
- Rol en el portafolio: junto a VisualizadorDeGrafos y LibreriaString forma el bloque "C++ y estructuras de datos desde cero".

## 6. Recomendaciones

Ver `IMPROVEMENT_ROADMAP.md`. P1: asserts + job de CI Linux.

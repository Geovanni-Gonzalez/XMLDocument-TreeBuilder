# CV_EVIDENCE — XMLDocument-TreeBuilder

Verifiable, interview-defensible material. All claims map to files in this repository.

## Resume bullets (pick & adapt)

- Built a header-only C++ library for constructing well-formed XML documents in memory against a fixed public-API specification: node tree with attributes, four-mode content/attribute editing (prepend/append/overwrite/delete-occurrences), indented serialization, and file export — no console I/O, boolean-contract returns.
- Implemented a **splay tree from scratch** (parent-pointer rotations, zig/zig-zig/zig-zag splaying, insert/delete) for amortized-efficient node lookup by id.
- Wrote a minimal C-string library (`len/copy/cmp/dup/cat/find/replace`) and managed all ownership manually with paired malloc/free and destructors — no std::string, per assignment constraints.

## Skills matrix

| Skill | Evidence | Depth | Confidence |
|---|---|---|---|
| Advanced data structures (splay tree) | `XMLDocument.hpp` → `SplayNode`, `rotate`, `splay`, `insertSplay`, `deleteSplay` | Medium-Deep | High |
| Manual memory management / ownership | `Attribute`/`XMLNode` destructors, `StringLib::dup` | Medium | High |
| API design against a spec | Public template compliance (`ADD/OVR/APD` modes, bool contracts) | Medium | High |
| C-string manipulation | `StringLib.hpp` (7 primitives) | Medium | High |
| Tree algorithms & serialization | `buildXMLString`, `buildTreeView` (recursive, indented) | Medium | High |

## What this project proves

- First appearance of: **self-balancing tree (splay)**, header-only library design, API-contract compliance.
- Reinforces: C++, manual memory, linked lists (shared with VisualizadorDeGrafos, LibreriaString).
- Interview talking point: explain splay rotations and amortized complexity on a whiteboard with your own code as reference.

## ATS keywords

C++, data structures, splay tree, self-balancing trees, binary search tree, rotations, amortized analysis, XML, serialization, header-only library, API design, memory management, linked lists, C strings, MSVC, GitHub Actions.

# XMLDocument-TreeBuilder 🏗️

Librería de alto rendimiento en C++ (C++98) diseñada para la creación, manipulación y exportación de documentos XML bien formados.

## 🌟 Características Destacadas

- **Motor Splay Tree**: Búsqueda de nodos indexada y optimizada mediante balanceo biselado.
- **Sin Dependencias**: Implementación propia de `StringLib` (gestión de C-Strings) y `LinkedList` dinámicas.
- **Edición Versátil**: Modos de edición avanzada para atributos y contenido (ADD, APD, OVR, DEL).
- **Exportación Técnica**: Generación de XML indentado y vistas de árbol jerárquicas ASCII.

## 🛠️ Requisitos Técnico

- **Estándar**: C++98.
- **Compatibilidad**: Debian 10+ (GCC), Borland C++.
- **Memoria**: Gestión dinámica manual (No STL).

## 🚀 Inicio Rápido

Compilación de la librería con el driver de prueba:

```bash
g++ main.cpp -o xml_builder.exe
./xml_builder.exe
```

## 📂 Archivos Principales

- `XMLDocument.hpp`: Controlador principal y lógica Splay.
- `XMLNode.hpp`: Estructuras de datos de nodos y atributos.
- `StringLib.hpp`: Utilidades de cadena personalizadas.
- `LinkedList.hpp`: Listas enlazadas dinámicas.

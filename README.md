# XMLDocument TreeBuilder

[![CI](https://github.com/Geovanni-Gonzalez/XMLDocument-TreeBuilder/actions/workflows/ci.yml/badge.svg)](https://github.com/Geovanni-Gonzalez/XMLDocument-TreeBuilder/actions/workflows/ci.yml)

## Descripción
Librería C++ header-only para construir documentos XML bien formados en memoria: árbol de nodos con atributos, edición en 4 modos (agregar/adjuntar/sobreescribir/borrar), serialización indentada y un **árbol splay implementado desde cero** (rotaciones y splaying con puntero a padre) para búsqueda de nodos por id. Sin `std::string`: incluye una librería propia de C-strings (`StringLib.hpp`).

## Objetivo
Practicar estructuras dinámicas, árboles y documentos jerarquicos.

## Tecnologías utilizadas
- C++
- Árboles
- Listas enlazadas
- POO

## Funcionalidades principales
- XMLDocument
- XMLNode
- LinkedList propia
- StringLib auxiliar
- main.cpp demo

## Mi rol
Implementé estructuras principales para construir y manipular XML en memoria.

## Aprendizajes clave
- Jerarquias
- Listas enlazadas
- Composicion de clases
- Memoria dinámica

## Instalación y ejecución
```bash
cd XMLDocument-TreeBuilder
g++ main.cpp -o xml_builder.exe
./xml_builder.exe
```

## Estructura del proyecto
- XMLDocument.hpp/XMLNode.hpp: modelo
- LinkedList.hpp: lista
- StringLib.hpp/utils.h: apoyo
- main.cpp: demo

## Capturas o demo
![Captura principal](docs/img/principalImage.png)

## Estado del proyecto
Proyecto académico funcional.

## Valor técnico demostrado
Demuestra estructuras de datos en C++ y representación jerarquica sin librerías externas.

## Mejoras futuras
- Agregar parser XML
- Serializar a XML
- Pruebas unitarias

## Autor
Geovanni González  
Estudiante de Ingeniería en Computación  
GitHub: [Geovanni-Gonzalez](https://github.com/Geovanni-Gonzalez)











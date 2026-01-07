#ifndef XMLNODE_HPP
#define XMLNODE_HPP

#include "StringLib.hpp"
#include "LinkedList.hpp"

// Representa un atributo XML (Pareja Clave-Valor)
struct Attribute {
    char* key;
    char* value;

    Attribute(const char* k, const char* v) {
        key = StringLib::dup(k);
        value = StringLib::dup(v);
    }

    ~Attribute() {
        if (key) free(key);
        if (value) free(value);
    }
};

// Representa un nodo en la estructura jerárquica XML
struct XMLNode {
    int id;
    char* name;
    char* content;
    LinkedList<Attribute*> attributes;
    LinkedList<XMLNode*> children;
    XMLNode* parent;
    bool contentAtStart; // True para BEG (antes de los hijos), False para END (después)

    XMLNode(int nodeId, const char* tagName) {
        id = nodeId;
        name = StringLib::dup(tagName);
        content = NULL;
        parent = NULL;
        contentAtStart = true; // Por defecto BEG
    }

    XMLNode(int nodeId, const char* tagName, const char* tagContent) {
        id = nodeId;
        name = StringLib::dup(tagName);
        content = StringLib::dup(tagContent);
        parent = NULL;
        contentAtStart = true;
    }

    ~XMLNode() {
        if (name) free(name);
        if (content) free(content);
        
        // Limpiar atributos
        Node<Attribute*>* attrCurr = attributes.getHead();
        while (attrCurr) {
            delete attrCurr->data;
            attrCurr = attrCurr->next;
        }
        attributes.clear();

        // Limpiar hijos (recursivo)
        Node<XMLNode*>* childCurr = children.getHead();
        while (childCurr) {
            delete childCurr->data;
            childCurr = childCurr->next;
        }
        children.clear();
    }
};

#endif

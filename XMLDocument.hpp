#ifndef XMLDOCUMENT_HPP
#define XMLDOCUMENT_HPP

#include "XMLNode.hpp"
#include <stdio.h> // Para Save (FILE*)

class XMLDocument {
public:
    static const int ADD = 100;
    static const int OVR = 200;
    static const int APD = 300;
    static const int DEL = 400;
    static const int BEG = 10;
    static const int END = 20;

private:
    XMLNode* root;
    XMLNode* selected;
    int idCounter;

    // --- LÓGICA DE BÚSQUEDA SPLAY ---
    struct SplayNode {
        int id;
        XMLNode* xml;
        SplayNode *left, *right, *parent;
        SplayNode(int i, XMLNode* x) : id(i), xml(x), left(NULL), right(NULL), parent(NULL) {}
    };

    SplayNode* splayRoot;

    // Rotación de nodo para el árbol splay
    void rotate(SplayNode* x) {
        SplayNode* y = x->parent;
        SplayNode* z = y->parent;
        if (z) {
            if (z->left == y) z->left = x;
            else z->right = x;
        }
        x->parent = z;
        if (y->left == x) {
            y->left = x->right;
            if (x->right) x->right->parent = y;
            x->right = y;
        } else {
            y->right = x->left;
            if (x->left) x->left->parent = y;
            x->left = y;
        }
        y->parent = x;
    }

    // Lleva el nodo x a la raíz del árbol de búsqueda
    void splay(SplayNode* x) {
        if (!x) return;
        while (x->parent) {
            SplayNode* y = x->parent;
            SplayNode* z = y->parent;
            if (z) {
                if ((z->left == y) == (y->left == x)) rotate(y);
                else rotate(x);
            }
            rotate(x);
        }
        splayRoot = x;
    }

    // Inserta un nuevo nodo en el índice splay
    void insertSplay(int id, XMLNode* xml) {
        if (!splayRoot) {
            splayRoot = new SplayNode(id, xml);
            return;
        }
        SplayNode* curr = splayRoot;
        SplayNode* p = NULL;
        while (curr) {
            p = curr;
            if (id < curr->id) curr = curr->left;
            else curr = curr->right;
        }
        SplayNode* newNode = new SplayNode(id, xml);
        newNode->parent = p;
        if (id < p->id) p->left = newNode;
        else p->right = newNode;
        splay(newNode);
    }

    // Busca un nodo por ID y lo splayea a la raíz
    SplayNode* findSplay(int id) {
        SplayNode* curr = splayRoot;
        while (curr) {
            if (id == curr->id) {
                splay(curr);
                return curr;
            }
            if (id < curr->id) curr = curr->left;
            else curr = curr->right;
        }
        return NULL;
    }

    // Elimina un nodo del índice splay por su ID
    void deleteSplay(int id) {
        SplayNode* node = findSplay(id);
        if (!node) return;
        SplayNode* L = node->left;
        SplayNode* R = node->right;
        if (L) L->parent = NULL;
        if (R) R->parent = NULL;
        delete node;
        if (!L) splayRoot = R;
        else {
            splayRoot = L;
            SplayNode* maxL = L;
            while (maxL->right) maxL = maxL->right;
            splay(maxL);
            splayRoot->right = R;
            if (R) R->parent = splayRoot;
        }
    }

    // Limpia recursivamente los nodos splay
    void clearSplay(SplayNode* node) {
        if (!node) return;
        clearSplay(node->left);
        clearSplay(node->right);
        delete node;
    }

    // --- AYUDANTES DE VISUALIZACIÓN ---
    // Construye la cadena XML de forma recursiva
    void buildXMLString(XMLNode* node, char* buffer, int& pos, int indent) {
        if (!node) return;

        // Sangría
        for (int i = 0; i < indent; i++) { buffer[pos++] = ' '; buffer[pos++] = ' '; }

        // Apertura de etiqueta
        buffer[pos++] = '<';
        StringLib::copy(buffer + pos, node->name);
        pos += StringLib::len(node->name);

        // Atributos
        Node<Attribute*>* attr = node->attributes.getHead();
        while (attr) {
            buffer[pos++] = ' ';
            StringLib::copy(buffer + pos, attr->data->key);
            pos += StringLib::len(attr->data->key);
            buffer[pos++] = '='; buffer[pos++] = '"';
            StringLib::copy(buffer + pos, attr->data->value);
            pos += StringLib::len(attr->data->value);
            buffer[pos++] = '"';
            attr = attr->next;
        }
        buffer[pos++] = '>';

        // Contenido al inicio
        if (node->contentAtStart && node->content) {
            StringLib::copy(buffer + pos, node->content);
            pos += StringLib::len(node->content);
        }

        // Hijos
        if (node->children.count() > 0) {
            buffer[pos++] = '\n';
            Node<XMLNode*>* child = node->children.getHead();
            while (child) {
                buildXMLString(child->data, buffer, pos, indent + 1);
                child = child->next;
            }
            for (int i = 0; i < indent; i++) { buffer[pos++] = ' '; buffer[pos++] = ' '; }
        }

        // Contenido al final
        if (!node->contentAtStart && node->content) {
            StringLib::copy(buffer + pos, node->content);
            pos += StringLib::len(node->content);
        }

        // Cierre de etiqueta
        buffer[pos++] = '<'; buffer[pos++] = '/';
        StringLib::copy(buffer + pos, node->name);
        pos += StringLib::len(node->name);
        buffer[pos++] = '>'; buffer[pos++] = '\n';
        buffer[pos] = '\0';
    }

    // Construye la vista de árbol ASCII
    void buildTreeView(XMLNode* node, char* buffer, int& pos, int indent) {
        if (!node) return;
        for (int i = 0; i < indent; i++) { buffer[pos++] = ' '; buffer[pos++] = ' '; buffer[pos++] = '|'; }
        buffer[pos++] = '-';
        StringLib::copy(buffer + pos, node->name);
        pos += StringLib::len(node->name);
        buffer[pos++] = ' '; buffer[pos++] = '(';
        char idStr[16]; sprintf(idStr, "%d", node->id);
        StringLib::copy(buffer + pos, idStr);
        pos += StringLib::len(idStr);
        buffer[pos++] = ')'; buffer[pos++] = '\n';
        
        Node<XMLNode*>* child = node->children.getHead();
        while (child) {
            buildTreeView(child->data, buffer, pos, indent + 1);
            child = child->next;
        }
    }

public:
    XMLDocument() : root(NULL), selected(NULL), idCounter(1), splayRoot(NULL) {}

    ~XMLDocument() {
        if (root) delete root;
        clearSplay(splayRoot);
    }

    // Inserta un nuevo nodo raíz
    int Root(char *name) {
        if (root) return -1;
        root = new XMLNode(idCounter++, name);
        selected = root;
        insertSplay(root->id, root);
        return root->id;
    }

    // Selecciona un nodo del documento por su ID
    bool Select(int id) {
        SplayNode* found = findSplay(id);
        if (found) { selected = found->xml; return true; }
        return false;
    }

    // Agrega un nodo hijo al nodo seleccionado
    int Child(char *name) {
        if (!selected) return -1;
        XMLNode* n = new XMLNode(idCounter++, name);
        n->parent = selected;
        selected->children.add(n);
        insertSplay(n->id, n);
        return n->id;
    }

    // Agrega un nodo hijo con contenido al nodo seleccionado
    int Child(char *name, char *content) {
        if (!selected) return -1;
        XMLNode* n = new XMLNode(idCounter++, name, content);
        n->parent = selected;
        selected->children.add(n);
        insertSplay(n->id, n);
        return n->id;
    }

    // Edita atributos del nodo seleccionado
    bool EditAttribute(char *key, char *value, int mode) {
        if (!selected) return false;
        Node<Attribute*>* curr = selected->attributes.getHead();
        Attribute* attr = NULL;
        while (curr) {
            if (StringLib::cmp(curr->data->key, key) == 0) { attr = curr->data; break; }
            curr = curr->next;
        }

        if (mode != DEL) {
            if (!attr) {
                attr = new Attribute(key, value);
                selected->attributes.add(attr);
            } else {
                char* old = attr->value;
                if (mode == ADD) {
                    attr->value = (char*)malloc(StringLib::len(value) + StringLib::len(old) + 1);
                    StringLib::copy(attr->value, value); StringLib::cat(attr->value, old);
                } else if (mode == APD) {
                    attr->value = (char*)malloc(StringLib::len(value) + StringLib::len(old) + 1);
                    StringLib::copy(attr->value, old); StringLib::cat(attr->value, value);
                } else if (mode == OVR) {
                    attr->value = StringLib::dup(value);
                }
                free(old);
            }
        } else {
            if (!attr) return false;
            char* newVal = StringLib::replace(attr->value, value, "");
            free(attr->value); attr->value = newVal;
        }
        return true;
    }

    // Edita contenido del nodo seleccionado
    bool EditContent(char *content, int mode) {
        if (!selected) return false;
        if (mode != DEL) {
            if (!selected->content) { selected->content = StringLib::dup(content); }
            else {
                char* old = selected->content;
                if (mode == ADD) {
                    selected->content = (char*)malloc(StringLib::len(content) + StringLib::len(old) + 1);
                    StringLib::copy(selected->content, content); StringLib::cat(selected->content, old);
                } else if (mode == APD) {
                    selected->content = (char*)malloc(StringLib::len(content) + StringLib::len(old) + 1);
                    StringLib::copy(selected->content, old); StringLib::cat(selected->content, content);
                } else if (mode == OVR) { selected->content = StringLib::dup(content); }
                free(old);
            }
        } else {
            if (!selected->content) return false;
            char* newVal = StringLib::replace(selected->content, content, "");
            free(selected->content); selected->content = newVal;
        }
        return true;
    }

    // Modifica el modo de visualización del contenido (BEG/END)
    bool SwitchContentPosition() {
        if (!selected) return false;
        selected->contentAtStart = !selected->contentAtStart;
        return true;
    }

    // Configura el nodo seleccionado como raíz de un subárbol balanceado biselado
    bool SetBalanced() {
        if (!selected) return false;
        SplayNode* node = findSplay(selected->id);
        if (node) { splay(node); return true; }
        return false;
    }

    // Elimina el nodo seleccionado
    bool Delete() {
        if (!selected || !root) return false;
        int tid = selected->id; deleteSplay(tid);
        if (selected == root) { delete root; root = NULL; selected = NULL; return true; }
        XMLNode* p = selected->parent;
        if (p) { p->children.remove(selected); delete selected; selected = p; return true; }
        return false;
    }

    // Visualiza el subárbol
    char* ViewTree() {
        if (!root) return StringLib::dup("Documento Vacío");
        char* b = (char*)malloc(20000); int p = 0;
        buildTreeView(root, b, p, 0); b[p] = '\0'; return b;
    }

    // Visualiza el nodo seleccionado
    char* ViewNode() {
        if (!selected) return StringLib::dup("Sin selección");
        char b[1024];
        sprintf(b, "ID: %d, Nombre: %s, Contenido: %s, Hijos: %d, Posición: %s", 
                selected->id, selected->name, selected->content ? selected->content : "Ninguno", 
                selected->children.count(), selected->contentAtStart ? "INICIO" : "FINAL");
        return StringLib::dup(b);
    }

    // Previsualiza el XML
    char* ViewXML() {
        if (!root) return StringLib::dup("");
        char* b = (char*)malloc(30000); int p = 0;
        buildXMLString(root, b, p, 0); return b;
    }

    // Guarda el árbol en un archivo
    bool Save(char *filename) {
        if (!root) return false;
        char* x = ViewXML(); FILE* f = fopen(filename, "w");
        if (f) { fprintf(f, "%s", x); fclose(f); free(x); return true; }
        free(x); return false;
    }
};

#endif

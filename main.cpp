#include <iostream>
#include "XMLDocument.hpp"
#include "utils.h"

// Imprime el menú de opciones con estilo profesional
void printMenu(XMLDocument& doc) {
    UI::clear_screen();
    UI::print_header("   XML DOC TREE-BUILDER v2.0 - PREMIUM EDITION");
    
    // Mostrar estado actual
    char* info = doc.ViewNode();
    UI::color_bold();
    std::cout << "  ESTADO ACTUAL: ";
    UI::color_reset();
    std::cout << info << std::endl;
    free(info);
    
    std::cout << "\n  Seleccione una operación:" << std::endl;
    UI::color_cyan();
    std::cout << "  ┌────────────────────────────┐  ┌────────────────────────────┐" << std::endl;
    std::cout << "  │ 1. 📂 Crear Raíz           │  │ 2. ➕ Agregar Hijo         │" << std::endl;
    std::cout << "  │ 3. 🖱️  Seleccionar por ID   │  │ 4. 🏷️  Editar Atributo     │" << std::endl;
    std::cout << "  │ 5. ✍️  Editar Contenido     │  │ 6. 🔄 Cambiar Posición     │" << std::endl;
    std::cout << "  │ 7. 🗑️  Eliminar Nodo        │  │ 8. 🔍 Ver Info Detallada   │" << std::endl;
    std::cout << "  │ 9. 📜 Ver XML Completo     │  │ 10.🌳 Ver Árbol Visual     │" << std::endl;
    std::cout << "  │ 11.⚖️  Balancear (Splay)    │  │ 12.💾 Guardar en Archivo   │" << std::endl;
    std::cout << "  └────────────────────────────┘  └────────────────────────────┘" << std::endl;
    UI::color_red();
    std::cout << "  [ 0. Salir ]" << std::endl;
    UI::color_reset();
    std::cout << "\n  >> Opción: ";
}

int main() {
    UI::setup_console();
    XMLDocument doc;
    int choice;
    char buf1[256], buf2[256];
    int id, mode;

    while (true) {
        printMenu(doc);
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        if (choice == 0) break;

        std::cout << std::endl;
        switch (choice) {
            case 1:
                UI::color_yellow();
                std::cout << "  >> Nombre de la nueva raíz: ";
                UI::color_reset();
                std::cin >> buf1;
                id = doc.Root(buf1);
                if (id != -1) UI::print_success("Raíz creada correctamente.");
                else UI::print_error("El documento ya posee una raíz.");
                break;
            case 2:
                UI::color_yellow();
                std::cout << "  >> Título del nodo hijo: ";
                UI::color_reset();
                std::cin >> buf1;
                UI::color_yellow();
                std::cout << "  >> Contenido (usa '-' para saltar): ";
                UI::color_reset();
                std::cin >> buf2;
                if (buf2[0] == '-') id = doc.Child(buf1);
                else id = doc.Child(buf1, buf2);
                if (id != -1) UI::print_success("Nodo hijo insertado con éxito.");
                else UI::print_error("No hay un nodo seleccionado actualmente.");
                break;
            case 3:
                UI::color_yellow();
                std::cout << "  >> ID del nodo a seleccionar: ";
                UI::color_reset();
                std::cin >> id;
                if (doc.Select(id)) UI::print_success("Nodo seleccionado como activo.");
                else UI::print_error("El ID especificado no existe.");
                break;
            case 4:
                UI::color_yellow();
                std::cout << "  >> Clave: "; std::cin >> buf1;
                std::cout << "  >> Valor: "; std::cin >> buf2;
                std::cout << "  >> Modo (100:Add, 200:Ovr): "; 
                UI::color_reset();
                std::cin >> mode;
                if (doc.EditAttribute(buf1, buf2, mode)) UI::print_success("Atributo modificado.");
                else UI::print_error("Error al editar atributo.");
                break;
            case 5:
                UI::color_yellow();
                std::cout << "  >> Nuevo Contenido: "; std::cin >> buf1;
                std::cout << "  >> Modo (100:Add, 200:Ovr, 300:Apd, 400:Del): ";
                UI::color_reset();
                std::cin >> mode;
                if (doc.EditContent(buf1, mode)) UI::print_success("Contenido actualizado.");
                else UI::print_error("Error al actualizar contenido.");
                break;
            case 6:
                if (doc.SwitchContentPosition()) UI::print_success("Ubicación del contenido invertida.");
                else UI::print_error("Fallo al cambiar posición.");
                break;
            case 7:
                if (doc.Delete()) UI::print_success("Nodo y su descendencia eliminados.");
                else UI::print_error("No hay selección válida para borrar.");
                break;
            case 8:
                {
                    char* info = doc.ViewNode();
                    UI::print_info(info);
                    free(info);
                }
                break;
            case 9:
                {
                    UI::color_cyan();
                    std::cout << "--- PREVISUALIZACIÓN XML ---" << std::endl;
                    UI::color_reset();
                    char* xml = doc.ViewXML();
                    std::cout << xml << std::endl;
                    free(xml);
                }
                break;
            case 10:
                {
                    UI::color_cyan();
                    std::cout << "--- ESTRUCTURA DE ÁRBOL ---" << std::endl;
                    UI::color_reset();
                    char* tree = doc.ViewTree();
                    std::cout << tree << std::endl;
                    free(tree);
                }
                break;
            case 11:
                if (doc.SetBalanced()) UI::print_success("Biselado (Splay) aplicado a la raíz.");
                else UI::print_error("No hay un nodo seleccionado.");
                break;
            case 12:
                UI::color_yellow();
                std::cout << "  >> Nombre del archivo XML: ";
                UI::color_reset();
                std::cin >> buf1;
                UI::loading_bar();
                if (doc.Save(buf1)) UI::print_success("Documento exportado exitosamente.");
                else UI::print_error("Error al escribir en el disco.");
                break;
        }
        std::cout << "\n  Presione ENTER para continuar...";
        std::cin.ignore(1000, '\n');
        std::cin.get();
    }

    return 0;
}

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <windows.h>

namespace UI {
    // Configura la consola para UTF-8 y colores ANSI
    inline void setup_console() {
        SetConsoleOutputCP(65001); // UTF-8
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }

    // Colores ANSI
    inline void color_cyan() { std::cout << "\033[36m"; }
    inline void color_green() { std::cout << "\033[32m"; }
    inline void color_red() { std::cout << "\033[31m"; }
    inline void color_yellow() { std::cout << "\033[33m"; }
    inline void color_reset() { std::cout << "\033[0m"; }
    inline void color_bold() { std::cout << "\033[1m"; }

    inline void clear_screen() {
        std::cout << "\033[2J\033[H";
    }

    inline void print_header(const char* title) {
        color_cyan();
        std::cout << "╔══════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║ ";
        color_bold();
        std::cout << title;
        color_reset();
        color_cyan();
        
        // Calcular padding manual para evitar errores de alineación
        int text_len = 0;
        const unsigned char* p = (const unsigned char*)title;
        while (*p) {
            // Contar caracteres UTF-8 de forma básica (no bytes)
            if ((*p & 0xc0) != 0x80) text_len++;
            p++;
        }
        
        int total_width = 60;
        int padding = total_width - text_len;
        for(int i=0; i < padding; i++) std::cout << " ";
        std::cout << " ║" << std::endl;
        std::cout << "╚══════════════════════════════════════════════════════════════╝" << std::endl;
        color_reset();
    }

    inline void print_success(const char* msg) {
        color_green();
        std::cout << "  [✔] " << msg << std::endl;
        color_reset();
    }

    inline void print_error(const char* msg) {
        color_red();
        std::cout << "  [✘] " << msg << std::endl;
        color_reset();
    }

    inline void print_info(const char* msg) {
        color_yellow();
        std::cout << "  [ℹ] " << msg << std::endl;
        color_reset();
    }

    inline void loading_bar(int steps = 10) {
        color_yellow();
        std::cout << "  Procesando: [";
        for(int i=0; i<steps; i++) {
            std::cout << "■";
            Sleep(50);
        }
        std::cout << "] Completado!" << std::endl;
        color_reset();
    }
}

#endif

#ifndef STRINGLIB_HPP
#define STRINGLIB_HPP

#include <stdlib.h>

namespace StringLib {

    // Retorna la longitud de una cadena
    inline int len(const char* str) {
        if (!str) return 0;
        int l = 0;
        while (str[l] != '\0') l++;
        return l;
    }

    // Copia la cadena fuente al destino
    inline char* copy(char* dest, const char* src) {
        if (!dest || !src) return dest;
        int i = 0;
        while (src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
        return dest;
    }

    // Compara dos cadenas (estilo strcmp)
    inline int cmp(const char* s1, const char* s2) {
        if (!s1 || !s2) return (s1 == s2) ? 0 : (s1 ? 1 : -1);
        while (*s1 && (*s1 == *s2)) {
            s1++;
            s2++;
        }
        return *(const unsigned char*)s1 - *(const unsigned char*)s2;
    }

    // Duplica una cadena en memoria dinámica
    inline char* dup(const char* src) {
        if (!src) return NULL;
        int l = len(src);
        char* d = (char*)malloc(l + 1);
        if (d) copy(d, src);
        return d;
    }

    // Concatena la cadena fuente al final del destino
    inline char* cat(char* dest, const char* src) {
        if (!dest || !src) return dest;
        char* ptr = dest;
        while (*ptr != '\0') ptr++;
        copy(ptr, src);
        return dest;
    }

    // Busca la primera aparición de needle en haystack
    inline char* find(const char* haystack, const char* needle) {
        if (!haystack || !needle) return NULL;
        if (!*needle) return (char*)haystack;
        for (; *haystack; haystack++) {
            if (*haystack == *needle) {
                const char *h = haystack, *n = needle;
                while (*h && *n && *h == *n) {
                    h++;
                    n++;
                }
                if (!*n) return (char*)haystack;
            }
        }
        return NULL;
    }

    // Reemplaza todas las ocurrencias de target por replacement en original
    inline char* replace(const char* original, const char* target, const char* replacement) {
        if (!original || !target || !replacement) return dup(original);
        
        int origLen = len(original);
        int targetLen = len(target);
        if (targetLen == 0) return dup(original);
        int replLen = len(replacement);

        // Contar ocurrencias
        int count = 0;
        const char* tmp = original;
        while ((tmp = find(tmp, target))) {
            count++;
            tmp += targetLen;
        }

        int resultLen = origLen + count * (replLen - targetLen);
        char* result = (char*)malloc(resultLen + 1);
        if (!result) return NULL;

        char* ptr = result;
        while (*original) {
            const char* found = find(original, target);
            if (original == found) {
                copy(ptr, replacement);
                ptr += replLen;
                original += targetLen;
            } else {
                *ptr++ = *original++;
            }
        }
        *ptr = '\0';
        return result;
    }
}

#endif

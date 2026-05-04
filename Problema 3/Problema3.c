#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    const char* clave;
    const char* valor;
} Diccionario;

Diccionario* obtenerDiccionario(int* size) {
    static Diccionario diccionario[] = {
        {"int", "entero"}, {"char", "caracter"}, {"float", "flotante"},
        {"double", "doble"}, {"if", "si"}, {"else", "sino"},
        {"while", "mientras"}, {"for", "para"}, {"return", "retornar"},
        {"void", "vacio"}, {"switch", "segun"}, {"case", "caso"},
        {"break", "romper"}, {"default", "defecto"}, {"do", "hacer"}
    };
    *size = sizeof(diccionario) / sizeof(diccionario[0]);
    return diccionario;
}

const char* buscarDiccionario(Diccionario* dic, int size, const char* palabra) {
    for (int i = 0; i < size; i++) {
        if (strcmp(dic[i].clave, palabra) == 0) {
            return dic[i].valor;
        }
    }
    return NULL;
}

void traducirPrograma(const char* programaC) {
    int dicSize;
    Diccionario* diccionario = obtenerDiccionario(&dicSize);

    printf("\n--- Codigo Traducido ---\n");

    char* copia = strdup(programaC);
    if (!copia) {
        fprintf(stderr, "Error al asignar memoria\n");
        return;
    }

    char* token = strtok(copia, " \t\n");
    while (token != NULL) {
        char limpia[256];
        int idx = 0;
        for (int i = 0; token[i] != '\0' && idx < 255; i++) {
            if (isalpha((unsigned char)token[i])) {
                limpia[idx++] = token[i];
            }
        }
        limpia[idx] = '\0';

        const char* traduccion = buscarDiccionario(diccionario, dicSize, limpia);
        if (traduccion) {
            printf("**%s** ", traduccion);
        } else {
            printf("%s ", token);
        }

        if (strchr(token, ';') != NULL || strchr(token, '{') != NULL) {
            printf("\n");
        }

        token = strtok(NULL, " \t\n");
    }

    free(copia);
}

int main() {
    char* codigoC = strdup(
        "int main() {\n"
        "    int a = 5;\n"
        "    int b = 10;\n"
        "    int suma = a + b;\n"
        "    printf(\"La suma es: %d\", suma);\n"
        "    return 0;\n"
        "}\n"
    );
    if (!codigoC) {
        fprintf(stderr, "Error al asignar memoria\n");
        return 1;
    }

    printf("--- Analizador Lexico (C a Espanol) ---\n");
    printf("Codigo original cargado en memoria:\n");
    printf("%s\n", codigoC);

    traducirPrograma(codigoC);

    free(codigoC);

    return 0;
}

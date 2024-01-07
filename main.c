#include <stdio.h>
#include <string.h>
#include "arbol.h"

int main() {

    Nodo* nodo_actual = crear_nodo(NULL, "Directorio", "C:");

    char comando_s[10000];
    char input1[100];
    char input2[10000];
    char input3[10000];

    while(1){
        fgets(comando_s, 1000, stdin);
        int cantidad = sscanf(comando_s, "%s %s %[a-zA-Z0-9. ]*", input1, input2, input3);
        if (cantidad == 1 && strcmp(input1, "exit") == 0){break;}

        else if(cantidad == 2 && strcmp(input1, "mkdir") == 0){
            mkdir(nodo_actual, input2);
        }

        else if(cantidad == 2 && strcmp(input1, "cd") == 0){
            if(strcmp(input2, "..") == 0){
                nodo_actual = dos_puntos_ve_(nodo_actual);
            }
            else{
            nodo_actual = cd(nodo_actual, input2);
            }
        }

        else if(cantidad == 2 && strcmp(input1, "touch") == 0){
            touch(nodo_actual, input2);
        }

        else if(cantidad == 3 && strcmp(input1, "write") == 0){
            write(nodo_actual, input2, input3);
        }

        else if(cantidad == 1 && strcmp(input1, "ls") == 0){
            ls(nodo_actual);
        }

        else if(cantidad == 2 && strcmp(input1, "cat") == 0){
            cat(nodo_actual, input2);
        }

        else if(cantidad == 2 && strcmp(input1, "ls") == 0){
            ls_dir(nodo_actual, input2);
        }
        else if(cantidad == 3 && strcmp(input1, "mapdir") == 0){
            if(strcmp(input2, "touch") == 0){mapdir(nodo_actual, touch, input3);}
            if(strcmp(input2, "ls") == 0){ mapdir(nodo_actual, ls_dir, input3);}
            if(strcmp(input2, "mkdir") == 0){ mapdir(nodo_actual, mkdir, input3);}
        }
    }

    liberar_memoria(nodo_actual);

    return 0;
}

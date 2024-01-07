#include "arbol.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>

/*
Crea una nueva lista utilizando memoria dinámica.

    Parametros:
        largo_maximo_inicial (int): Largo inicial de la lista a generar.

    Retorno:
        nueva_lista (Lista*): Retorna una nueva lista ya inicializada con el largo inicial dado.
*/
Lista* crear_lista(int largo_maximo_inicial){
    Lista* nueva_lista = (Lista*)malloc(sizeof(Lista));

    nueva_lista->largo_maximo = largo_maximo_inicial;
    nueva_lista->largo_actual = 0;
    nueva_lista->arreglo = (Nodo*) malloc(largo_maximo_inicial * sizeof(Nodo));
    return nueva_lista;
}


/*
Inserta un nodo dado a una lista dada.

    Parametros:
        lista (Lista*): Lista en la que se quiere insertar el nodo.
        nodo (Nodo*): Nodo que se quiere insertar en la lista.

    Retorno:
        (void): Sin retorno.
*/
void insertar_lista(Lista* lista, struct Nodo nodo){

    lista->arreglo[lista->largo_actual] = nodo;

    if(lista->largo_actual >= lista->largo_maximo){
        lista->largo_maximo = lista->largo_maximo * 2;
    }

    lista->largo_actual++;
}


/*
Crea un nuevo nodo utilizando memoria dinámica y lo deja como hijo del nodo padre entregado.

    Parametros:
        padre (Nodo*): Nodo padre del nuevo nodo creado.
        tipo (char*): string del tipo de contenido que tendrá el nuevo nodo.
        nombre (char*): string del nombre del archivo o directorio generado.

    Retorno:
        nuevo_nodo (Nodo*): El nuevo nodo generado con los parámetros dados.
*/
Nodo* crear_nodo(Nodo* padre, char* tipo, char* nombre){
    Nodo* nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));

    if(strcmp(tipo, "Archivo") == 0){
        Archivo* nuevo_archivo = (Archivo*) malloc(sizeof(Archivo));
        strcpy(nuevo_archivo->nombre, nombre);
        strcpy(nuevo_nodo->tipo, tipo);
        nuevo_nodo->contenido = nuevo_archivo;
        nuevo_nodo->padre = padre;
    }

    else if(strcmp(tipo, "Directorio") == 0){
        Directorio* nuevo_directorio = (Directorio*) malloc(sizeof(Directorio));
        strcpy(nuevo_directorio->nombre, nombre);
        nuevo_directorio->hijos = crear_lista(100);
        strcpy(nuevo_nodo->tipo, tipo);
        nuevo_nodo->contenido = nuevo_directorio;
        nuevo_nodo->padre = padre;
    }

    return nuevo_nodo;
}


/*
Crea un nuevo archivo y lo agrega como hijo del nodo tipo directorio entregado.

    Parametros:
        actual (Nodo*): Nodo actual tipo directorio al que se le agregará el nuevo archivo generado.
        nombre_archivo (char*): string del nombre del nuevo archivo generado.

    Retorno:
        (void): Sin retorno.
*/
void touch(Nodo* actual, char* nombre_archivo){
    Nodo* archivo = crear_nodo(actual ,"Archivo", nombre_archivo);

    Directorio* directorio_actual = actual->contenido;
    Lista* hijos_actual = directorio_actual->hijos;
    insertar_lista(hijos_actual, *archivo);
}


/*
Crea un nuevo directorio y lo agrega como hijo del nodo tipo directorio entregado.

    Parametros:
        actual (Nodo*): Nodo actual tipo directorio al que se le agregará el nuevo directorio generado.
        nombre_archivo (char*): string del nombre del nuevo directorio generado.

    Retorno:
        (void): Sin retorno.
*/
void mkdir(Nodo* actual, char* nombre_directorio){
    Nodo* directorio = crear_nodo(actual, "Directorio", nombre_directorio);

    Directorio* directorio_actual = actual->contenido;
    Lista* hijos_actual = directorio_actual->hijos;
    insertar_lista(hijos_actual, *directorio);
}


/*
Busca un nodo directorio a partir de su nombre y lo retorna.

    Parametros:
        actual (Directorio*): Directorio actual en el que se busca el directorio a partir de su nombre.
        nombre (char*): string del nombre del directorio que se busca.

    Retorno:
        arreglo_hijos (Nodo*): Nodo directorio encontrado a partir del nombre.
        NULL: En caso de que no se encuentre el directorio a partir del nombre dado.
*/
Nodo* buscar_directorio(Directorio* actual, char* nombre){
    Lista* hijos_actual = actual->hijos;

    for(int i = 0; i < hijos_actual->largo_actual; i++){
        Nodo* arreglo_hijos = &hijos_actual->arreglo[i];
       if(strcmp(arreglo_hijos->tipo, "Directorio") == 0){
           Directorio* directorio_buscar = arreglo_hijos->contenido;
           if(strcmp(directorio_buscar->nombre, nombre) == 0){
               return arreglo_hijos;
           }
       }
    }
    return NULL;
}


/*
Busca un nodo archivo a partir de su nombre y lo retorna.

    Parametros:
        actual (Directorio*): Directorio actual en el que se busca el archivo a partir de su nombre.
        nombre (char*): string del nombre del archivo que se busca.

    Retorno:
        arreglo_hijos (Nodo*): Nodo archivo encontrado a partir del nombre.
        NULL: En caso de que no se encuentre el directorio a partir del nombre dado.
*/
Nodo* buscar_archivo(Directorio* actual, char* nombre){
    Lista* hijos_actual = actual->hijos;
    for(int i = 0; i < hijos_actual->largo_actual; i++){
        Nodo* arreglo_hijos = &hijos_actual->arreglo[i];
        if(strcmp(arreglo_hijos->tipo, "Archivo") == 0){
            Archivo* archivo_buscar = arreglo_hijos->contenido;
            if(strcmp(archivo_buscar->nombre, nombre) == 0){
                return arreglo_hijos;
            }
        }
    }
    return NULL;
}


/*
A partir de un nombre dado, se busca un nodo tipo archivo en un nodo directorio actual y se le cambia el contenido.

    Parametros:
        actual (Nodo*): Nodo directorio actual en el que se busca el archivo.
        nombre_archivo (char*): string del nombre del archivo al que se le cambia el contenido.
        contenido (char*): string del contenido que se quiere escribir en el archivo.

    Retorno:
        (void): Sin retorno.
*/
void write(Nodo* actual, char* nombre_archivo, char* contenido){
    Directorio* directorio_actual = actual->contenido;
    Nodo* nodo_archivo = buscar_archivo(directorio_actual, nombre_archivo);
    Archivo* archivo_cambio =  nodo_archivo->contenido;
    strcpy(archivo_cambio->contenido, contenido);
}


/*
A partir de un nombre dado, se busca un nodo tipo archivo en un nodo directorio actual y se imprime su contenido.

    Parametros:
        actual (Nodo*): Nodo directorio actual en el que se busca el archivo.
        nombre_archivo (char*): string del nombre del archivo al que se le imprime el contenido.

    Retorno:
        (void): Sin retorno.
*/
void cat(Nodo* actual, char* nombre_archivo){
    Directorio* directorio_actual = actual->contenido;
    Nodo* nodo_archivo = buscar_archivo(directorio_actual, nombre_archivo);

    Archivo* archivo_imprimir = nodo_archivo->contenido;
    char* contenido_archivo = archivo_imprimir->contenido;
    printf("%s\n", contenido_archivo);
}


/*
Imprime todos los hijos del nodo tipo directorio actual.

    Parametros:
        actual (Nodo*): Nodo directorio actual del cual se van a imprimir sus hijos.

    Retorno:
        (void): Sin retorno.
*/
void ls(Nodo* actual){
    Directorio* directorio_actual = actual->contenido;
    Lista* hijos_actual = directorio_actual->hijos;

    for(int i = 0; i < hijos_actual->largo_actual; i++){
        Nodo* arreglo_actual = &hijos_actual->arreglo[i];

        if(strcmp(arreglo_actual->tipo, "Archivo") == 0){
            Archivo* archivo_actual = arreglo_actual->contenido;
            char* nombre_archivo = archivo_actual->nombre;
            printf("%s\n", nombre_archivo);
        }

        else if(strcmp(arreglo_actual->tipo, "Directorio") == 0){
            Directorio* directorio_actual_arreglo = arreglo_actual->contenido;
            char* nombre_directorio = directorio_actual_arreglo->nombre;
            printf("%s\n", nombre_directorio);
        }
    }
}


/*
Imprime todos los hijos del nodo tipo directorio seleccionado en el actual mediante su nombre.

    Parametros:
        actual (Nodo*): Nodo directorio actual del cual se va a buscar el directorio a imprimir.
        nombre_directorio (char*): string del nombre del directorio del cual se le imprime sus hijos.

    Retorno:
        (void): Sin retorno.
*/
void ls_dir(Nodo* actual, char* nombre_directorio){
    if(strcmp(nombre_directorio, ".") == 0){ ls(actual); return;}

    Directorio* directorio_actual = actual->contenido;
    Nodo* nodo_buscado = buscar_directorio(directorio_actual, nombre_directorio);

    ls(nodo_buscado);
}


/*
Funcion utilizada para la instruccion "cd".
Cambia el nodo actual a un nodo hijo seleccionado por su nombre.

    Parametros:
        actual (Nodo*): Nodo actual en el que se busca el directorio hijo a partir de su nombre.
        nombre_nuevo_actual (char*): string del nombre del directorio que será el nuevo actual.

    Retorno:
        nodo_nuevo_actual (Nodo*): Nodo tipo directorio que será el nuevo nodo_actual en el main.
*/
Nodo* cd(Nodo* actual, char* nombre_nuevo_actual){
    Directorio* directorio_actual = actual->contenido;
    Nodo* nodo_nuevo_actual = buscar_directorio(directorio_actual, nombre_nuevo_actual);
    return nodo_nuevo_actual;
}


/*
Funcion utilizada para la instruccion "cd".
Cambia el nodo actual al nodo padre de este.

    Parametros:
        actual (Nodo*): Nodo actual en el que se busca el directorio padre.

    Retorno:
        padre (Nodo*): Nodo padre del actual.
*/
Nodo* dos_puntos_ve_(Nodo* actual){
    Nodo* padre = actual->padre;
    return padre;
}


/*
Aplica una instruccion dada a todos los subdirectorios del nodo directorio actual.

    Parametros:
        actual (Nodo*): Nodo actual al que se le ejecutará la instruccion dada a sus directorios hijos.
        instruccion (Nodo*, char*): Instruccion dada que se ejecutara en los directorios hijos del nodo actual.
        parametro_instruccion (char*): Parametro que se le da a la instruccion dada.
    Retorno:
        (void): Sin retorno.
*/
void mapdir(Nodo* actual, void (*instruccion)(Nodo*, char*), char* parametro_instruccion){
    Directorio* directorio_actual = actual->contenido;
    Lista* lista_actual = directorio_actual->hijos;

    for(int i = 0; i < lista_actual->largo_actual; i++){
        Nodo* nodo_lista = &lista_actual->arreglo[i];
        if(strcmp(nodo_lista->tipo, "Directorio") == 0){
            instruccion(nodo_lista, parametro_instruccion);
        }
    }
}


/*
Funcion utilizada para liberar la memoria dinamica utilizada durante la creacion del arbol.
Libera la memoria usada por un nodo tipo archivo.

    Parametros:
        nodo_archivo (Nodo*): Nodo tipo archivo el cual se va a eliminar una vez usado.

    Retorno:
        (void): Sin retorno.
*/
void liberar_archivo(Nodo* nodo_archivo){
    Archivo* archivo_actual = nodo_archivo->contenido;
    free(archivo_actual->contenido);
    free(archivo_actual);
    free(nodo_archivo);
}


/*
Funcion utilizada para liberar la memoria dinamica utilizada durante la creacion del arbol.
Libera la memoria usada por un nodo tipo directorio.
Aplica recursividad, de forma que al encontrarse con un directorio hijo, elimine los hijos de este y así repetitivamente.

    Parametros:
        nodo_directorio (Nodo*): Nodo tipo directorio el cual se va a eliminar una vez usado.

    Retorno:
        (void): Sin retorno.
*/
void liberar_directorio(Nodo* nodo_directorio){
    Directorio* directorio_actual = nodo_directorio->contenido;
    Lista* hijos_actual = directorio_actual->hijos;

    for(int i = 0; i < hijos_actual->largo_actual; i++){
        Nodo* hijo_actual = &hijos_actual->arreglo[i];
        if(strcmp(hijo_actual->tipo, "Directorio") == 0){
            liberar_directorio(hijo_actual);
        }
        else if(strcmp(hijo_actual->tipo, "Archivo") == 0){
            liberar_archivo(hijo_actual);
        }
    }
    free(hijos_actual->arreglo);
    free(hijos_actual);
    free(directorio_actual);
    free(nodo_directorio);
}


/*
Funcion utilizada para liberar la memoria dinamica utilizada durante la creacion del arbol.
Usa las funciones liberar_archivo y liberar_diretorio.
Libera la memoria del nodo y lista empleado dependiendo del tipo de este.
    Parametros:
        nodo_actual (Nodo*): Nodo el cual se va a eliminar una vez usado.

    Retorno:
        (void): Sin retorno.
*/
void liberar_memoria(Nodo* nodo_actual){
    Directorio* directorio_actual = nodo_actual->contenido;
    Lista* hijos_actual = directorio_actual->hijos;

    for(int i = 0; i < hijos_actual->largo_actual; i++){
        Nodo* hijo_actual = &hijos_actual->arreglo[i];
        if(strcmp(hijo_actual->tipo, "Directorio") == 0){
            liberar_directorio(hijo_actual);
        }
        else if(strcmp(hijo_actual->tipo, "Archivo") == 0){
            liberar_archivo(hijo_actual);
        }
    }
    free(hijos_actual->arreglo);
    free(hijos_actual);
    free(directorio_actual);
    free(nodo_actual);
}

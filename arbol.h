#ifndef TAREA_DOS_ARBOL_H
#define TAREA_DOS_ARBOL_H
#endif


typedef struct Nodo {
    struct Nodo* padre;
    char tipo[64];
    void* contenido;
} Nodo;

typedef struct {
    int largo_actual;
    int largo_maximo;
    Nodo* arreglo;
} Lista;

typedef struct {
    char nombre[128];
    Lista* hijos;
} Directorio;

typedef struct {
    char nombre[128];
    char contenido[256];
} Archivo;


Lista* crear_lista(int largo_maximo_inicial);

void insertar_lista(Lista* lista, struct Nodo nodo);

Nodo* buscar_directorio(Directorio* actual, char* nombre);

Nodo* buscar_archivo(Directorio* actual, char* nombre);

Nodo* crear_nodo(Nodo* padre, char* tipo, char* nombre); // Nodo* padre,  DEVOLVER DSP

void mkdir(Nodo* actual, char* nombre_directorio);

void touch(Nodo* actual, char* nombre_archivo);

void write(Nodo* actual, char* nombre_archivo, char* contenido);

void cat(Nodo* actual, char* nombre_archivo);

void ls(Nodo* actual);

void ls_dir(Nodo* actual, char* nombre_directorio);

void mapdir(
        Nodo* actual,
        void (*instruccion)(Nodo*, char*),
        char* parametro_instruccion
);


Nodo* cd(Nodo* actual, char* nombre_nuevo_actual);

Nodo* dos_puntos_ve_(Nodo* actual);

void liberar_memoria(Nodo* nodo_actual);
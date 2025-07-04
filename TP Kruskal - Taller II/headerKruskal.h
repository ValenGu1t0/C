// HEADER CON DEFINICIONES Y PROTOTIPOS

// Trabajaremos con un grafo de 5 vertices o nodos, modificable.
#define VERTICES 5          

/* ----------------------------- */
    /* DEFINICION DE STRUCTS */
/* ----------------------------- */

typedef int tipo_nombre;
typedef int tipo_elemento;
typedef int vertice;

/* Arista */
typedef struct _Arista {    // Struct que almacena los datos de un segmento entre dos vertices

    vertice u;              // Vertices 
    vertice v;
    int costo;

} arista;

/* Rama es una lista enlazada de aristas - Osea el grafo */  
typedef struct _Rama {

    struct _Arista a;
    struct _Rama *sig;

} rama;


typedef struct _Encabezado {

    int cuenta;                 // Cantidad de vertices que tiene la componente
    int primer_elemento;        // Cual es el primer vertice de la componente

} encabezado;


typedef struct _Nombre {

    tipo_nombre nombre_conjunto;    // Nombre de la componente a la que pertence
    int siguiente_elemento;         // Indice del siguiente vertice que pertenece a la componente

} nombre;

/* Este struct representa el Arbol, donde primero sera el grafo con todos los vertices y costos originales, 
pero sin ninguna arista; iremos agregamos los vertices a esta estructura utilizando la funcion inicial) */
typedef struct _Conjunto_CE{

    nombre nombres[VERTICES];
    encabezado encabezamientos_conjunto[VERTICES];

} conjunto_CE;

/* ----------------------- */
/* PROTOTIPOS DE FUNCIONES */
/* ----------------------- */

void inicial(tipo_nombre, tipo_elemento, conjunto_CE *);
void combina(tipo_nombre, tipo_nombre, conjunto_CE *);
void fusionar(tipo_nombre , tipo_nombre , conjunto_CE *);
tipo_nombre encuentra (int, conjunto_CE *);
void kruskal (rama **);
void inserta (int, int, int, rama **);
arista sacar_min (rama **);
void lista (rama *);
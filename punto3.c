#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct Tarea{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
} tarea;

typedef struct Nodo{
    tarea t;
    struct Nodo *Siguiente;
} nodo;

nodo* crearListaVacia();
nodo* crearNodo(char *descripcion, int id, int duracion);
void insertarNodo(nodo **start, char *descripcion, int id, int duracion);
void mostrarTareas(nodo *start);
void moverTareas(nodo **Tareas, nodo **TareasRealizadas);
tarea buscarTareaId(nodo **Tareas, nodo **TareasRealizadas, int id);
void mostrarTarea(tarea T);
tarea buscarTareaPalabra(nodo **Tareas, nodo **TareasRealizadas, char* palabra);


int main(){
    srand(time(NULL));
    nodo *Tareas=crearListaVacia();
    nodo *TareasRealizadas=crearListaVacia();
    int cantTareas;

    //cargar tareas
    printf("cuantas tareas desea ingresar? ");
    scanf("%d",&cantTareas);

    for (int i=0; i < cantTareas; i++)
    {
        char *descripcion = (char *) malloc(100 * sizeof(char));
        printf("--> Ingrese la %d) tarea a realizar\n",i+1);
        fflush(stdin);
        gets(descripcion);

        insertarNodo(&Tareas,descripcion,i+1,0);
        free(descripcion);
    }
    //muestra todas las tareas
    printf("\n Las tareas ingresadas son: ");
    mostrarTareas(Tareas);

    //mueve las tareas de realizadas a hechas
    moverTareas(&Tareas,&TareasRealizadas);

    printf("\t--TAREAS REALIZADAS--\n");
    mostrarTareas(TareasRealizadas);
    printf("\t--TAREAS PENDIENTES--\n");
    mostrarTareas(Tareas);

    //Busqueda por id
    tarea busqueda;
    int id;
    printf("\n\t--BUSQUEDA DE TAREAS POR ID--\n");
    printf("Ingrese el ID de la tarea que busca: \n");
    scanf("%d",&id);
    busqueda = buscarTareaId(&Tareas,&TareasRealizadas,id);
    printf("\nResultado: ");
    mostrarTarea(busqueda);

    //Busqueda por palabra
    char* clave;
    clave = (char*)malloc(sizeof(char)*10);
    printf("\n\t--BUSQUEDA DE TAREAS POR PALABRA--\n");
    printf("Ingrese la palabra clave de la tarea que busca: \n");
    fflush(stdin);
    gets(clave);
    busqueda = buscarTareaPalabra(&Tareas,&TareasRealizadas,clave);
    printf("\nResultado: ");
    if(busqueda.TareaID == 0){
		printf("\nNo se encontraron tareas con esa palabra clave");
	}else{
		mostrarTarea(busqueda);
	}
    //libera memoria
    free(Tareas);
    free(TareasRealizadas);
    return 0;
}

nodo* crearListaVacia()
{
    return NULL;
}

nodo* crearNodo(char *descripcion, int id, int duracion)//crea un nodo e inserta la info
{
    nodo* Tarea = (nodo*)malloc(sizeof(nodo));
    Tarea->t.Descripcion = (char *) malloc(strlen(descripcion+1) * sizeof(char));
    strcpy(Tarea->t.Descripcion, descripcion);
    if(duracion==0){
        Tarea->t.Duracion = rand() % 99;
    }else{
        Tarea->t.Duracion = duracion;
    }
    Tarea->t.TareaID = id;
    Tarea->Siguiente=NULL;

    return Tarea;
}

void insertarNodo(nodo **start,char *descripcion,int id,int duracion)//inserta el nodo al comienzo de la lista
{
    nodo *nuevoNodo = crearNodo(descripcion,id,duracion);
    nuevoNodo->Siguiente = *start;
    *start = nuevoNodo;
}

void mostrarTareas(nodo *start)//muestra las tareas
{
    nodo * aux=start;
    while (aux)
    {
        printf("\nTarea %d: ",aux->t.TareaID);
        printf("%s",aux->t.Descripcion);
        printf("\nDuracion: %d\n",aux->t.Duracion);
        aux = aux->Siguiente;
    }    
}


void moverTareas(nodo **Tareas, nodo **TareasRealizadas)//mueve las tareas desde pendientes a hechas
{
    nodo * TareasPendientes = crearListaVacia();
    int realizado;

    printf("\nREVISION DE TAREAS");
    while ((*Tareas)!=NULL)
    {
        printf("\nTarea ID%d: ",(*Tareas)->t.TareaID);
        printf("%s",(*Tareas)->t.Descripcion);
        printf("\nDuracion: %d",(*Tareas)->t.Duracion);

        printf("\tSe realizo la Tarea?(1.Si  0.No)\n");
        scanf("%d",&realizado);

        if(realizado==1){
            //inserto el nodo en tareas realizadas
            insertarNodo(TareasRealizadas, (*Tareas)->t.Descripcion,(*Tareas)->t.TareaID,(*Tareas)->t.Duracion);
        }else{
            insertarNodo(&TareasPendientes, (*Tareas)->t.Descripcion,(*Tareas)->t.TareaID,(*Tareas)->t.Duracion);
        }
        *Tareas = (*Tareas)->Siguiente;
    }
    *Tareas = TareasPendientes;
}

tarea buscarTareaId(nodo **Tareas,nodo **TareasRealizadas,int id)//busqueda por ID
{
    tarea resultado;
    resultado.TareaID=0;

    while ((*Tareas)!= NULL)//busqueda en las tareas pendientes
    {
        if (id == (*Tareas)->t.TareaID)
        {
            return (*Tareas)->t;
        }
        *Tareas = (*Tareas)->Siguiente;
    }
    
    while ((*TareasRealizadas)!= NULL)//busqueda en las tareas pendientes
    {
        if (id == (*TareasRealizadas)->t.TareaID)
        {
            return (*TareasRealizadas)->t;
        }
        *TareasRealizadas = (*TareasRealizadas)->Siguiente;
    }
    return resultado;
}

void mostrarTarea(tarea T){
	printf("\nTarea %d: ", T.TareaID);
	printf("\nDescripcion: %s", T.Descripcion);
	printf("\nDuracion: %d", T.Duracion);
	printf("\n");
}

tarea buscarTareaPalabra(nodo **Tareas,nodo **TareasRealizadas,char* palabra)//busqueda por palabra
{
    tarea resultado;
    while ((*Tareas)!= NULL)//busqueda en las tareas pendientes
    {
        while (*((*Tareas)->t.Descripcion) != '\0')
        {
            if(strstr((*Tareas)->t.Descripcion,palabra))
            {
                return (*Tareas)->t;
            }
            ((*Tareas)->t.Descripcion)++;
        }
        *Tareas = (*Tareas)->Siguiente;
        
    }
    while ((*TareasRealizadas)!= NULL)//busqueda en las tareas pendientes
    {
        while (*((*TareasRealizadas)->t.Descripcion) != '\0')
        {
            if(strstr((*TareasRealizadas)->t.Descripcion,palabra))
            {
                return (*TareasRealizadas)->t;
            }
            ((*TareasRealizadas)->t.Descripcion)++;
        }
        *TareasRealizadas = (*TareasRealizadas)->Siguiente;
    }
    resultado.TareaID = 0;
    return resultado;
}

//funciones a tener en cuenta
// void cargarTareaAlFinal(Lista* listaTareas, short ID){//para cargar el nodo al final de la lista

//     Nodo* nuevoNodo = crearNodo(ID);

//     enlazarNodoAlFinal(listaTareas,nuevoNodo);

// }
// void enlazarNodoAlFinal(Lista* listaTareas, Nodo* nuevoNodo){
//     if(*listaTareas != NULL){

//         // Si la lista no esta vacia,
//         Lista headAux = *listaTareas;
//         // uso un head auxiliar para llegar al último nodo de la lista y no mover el head de la lista

//         while(headAux->sigNodo != NULL){
//             headAux = headAux->sigNodo;
//         }

//         headAux->sigNodo = nuevoNodo;
//         // Ahora el último nodo apunta a el nuevo nodo creado, que ya está inicializado con su puntero en NULL.

//     } else {
//         // Si la lista esta vacia, cargo el nuevo nodo directamente.

//         *listaTareas = nuevoNodo;
//         // Notar que el nuevo nodo ya viene inicializado con su puntero en NULL, por lo que no hago la asignación
//         // nuevoNodo = *listaTareas

//         // Además, en este caso la lista está vacía, no hace falta tener en cuenta el enlazamiento de otros nodos.
//     }
// }

// Nodo* quitarNodo(Lista* listaTareas){//para eliminar un nodo

//     Nodo* aux = NULL;

//     if(*listaTareas != NULL){
//         aux = *listaTareas;
//         *listaTareas = (*listaTareas)->sigNodo;
//         aux->sigNodo = NULL;
//         // Para poder agregar el nodo a otra lista de ser necesario, modifico su puntero a NULL
//     }

//     return aux;
// }
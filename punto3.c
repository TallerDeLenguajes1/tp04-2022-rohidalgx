#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

typedef struct Tarea{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}TAREA;

typedef struct Nodo{
    TAREA T;
    struct Nodo * Siguiente;
}NODO;

NODO *crearListaVacia();
void CargarTareas(NODO *lista, int cantidad);
void mostrarTarea(NODO *lista, int cantidad);
// void moverTareas(TAREA **pTareas, TAREA **pTareasHechas, int cantidad);
// void mostrarTareasHechasYPendientes(TAREA **pTareasHechas, TAREA **pTareasPendientes, int cantidad);
// TAREA *BuscarTareaPorID(TAREA **tarea, int cant);
// TAREA *BuscarTareaPorPalabra(TAREA **tarea, int cant);

int main(){
    srand(time(NULL));

    NODO *ListaPendientes = crearListaVacia();
    NODO *ListaHechas = crearListaVacia();

    int cantTareas;

    printf ("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d", &cantTareas);


    CargarTareas(ListaPendientes, cantTareas);
    mostrarTarea(ListaPendientes, cantTareas);
    // moverTareas(pTareas, pTareasHechas, cantTareas);

    // mostrarTareasHechasYPendientes(pTareasHechas, pTareas, cantTareas);

    // tarea = BuscarTareaPorID(pTareas, cantTareas);
    // if(tarea != NULL){
    //     printf("\n------- TAREA ENCONTRADA -------\n");
    //     printf("Tarea ID: %d\n", tarea->TareaID);
    //     printf("Descripcion: %s\n", tarea->Descripcion);
    //     printf("Duracion: %d\n", tarea->Duracion);
    // }

    // tarea_palabra = BuscarTareaPorPalabra(pTareas, cantTareas);
    // if(tarea_palabra != NULL){
    //     printf("\n------- TAREA ENCONTRADA -------\n");
    //     printf("Tarea ID: %d\n", tarea_palabra->TareaID);
    //     printf("Descripcion: %s\n", tarea_palabra->Descripcion);
    //     printf("Duracion: %d\n", tarea_palabra->Duracion);
    // }

    // free(pTareas);
    // free(pTareasHechas);

    return 0;
}

NODO *crearListaVacia(){
    return (NULL);
}

void CargarTareas(NODO *lista, int cantidad){

    for(int i=0; i < cantidad; i++){
        printf("------Carga de tareas----------\n");
        lista->T.TareaID = i + 1;
        lista->T.Descripcion=(char *)malloc(sizeof(char)*100);
        fflush(stdin);
        printf("Ingresar Descripcion: \n");
        gets(lista->T.Descripcion);
        lista->T.Duracion=rand()%(100-10+1)+10;
        lista = lista->Siguiente;
    }
}

void mostrarTarea(NODO *lista, int cantidad){

    for(int i=0; i < cantidad; i++){
        printf("------Mostrar Tareas----------\n");
        printf("----Tarea ID [%d]----\n",(lista->T.TareaID));
        printf("Descripcion de la tarea:%s\n",(lista->T.Descripcion));
        printf("Duracion de la tarea:%d\n",(lista->T.Duracion));
        lista = lista->Siguiente;
    }
}

// void moverTareas(TAREA **pTareas, TAREA **pTareasHechas, int cantidad){
//     int si_o_no;

//     printf("\n---------- Tareas Pendientes ----------\n");
//     for (int i = 0; i < cantidad; i++)
//     {
//         if (*(pTareas + i) != NULL)
//         {
//             printf("----------------------------------------\n");
//             printf("Tarea ID: %d\n", pTareas[i]->TareaID);
//             printf("Descripcion: %s\n", pTareas[i]->Descripcion);
//             printf("Duracion: %d\n", pTareas[i]->Duracion);
//             printf("\nMover a realizadas? (1 = SI; 0 = NO)-----\n");
//             scanf("%d", &si_o_no);

//             if (si_o_no == 1)
//             {
//                 *(pTareasHechas + i) = *(pTareas + i);
//                 *(pTareas + i) = NULL;
//             }else{
//                 *(pTareasHechas + i) = NULL;
//             }
//         }
//     }
// }

// void mostrarTareasHechasYPendientes(TAREA **pTareasHechas, TAREA **pTareasPendientes, int cantidad){


//     printf("\n---------- TAREAS REALIZADAS ----------\n");
//     for (int i = 0; i < cantidad; i++)
//     {
//         if (pTareasHechas[i] != NULL)
//         {
//             printf("----------------------------------------\n");
//             printf("Tarea ID: %d\n", pTareasHechas[i]->TareaID);
//             printf("Descripcion: %s\n", pTareasHechas[i]->Descripcion);
//             printf("Duracion: %d\n", pTareasHechas[i]->Duracion);
//         }
//     }

//     printf("\n---------- TAREAS PENDIENTES ----------\n");
//     for (int i = 0; i < cantidad; i++)
//     {
//         if (pTareasPendientes[i] != NULL)
//         {
//             printf("----------------------------------------\n");
//             printf("Tarea ID: %d\n", pTareasPendientes[i]->TareaID);
//             printf("Descripcion: %s\n", pTareasPendientes[i]->Descripcion);
//             printf("Duracion: %d\n", pTareasPendientes[i]->Duracion);
//         }
//     }
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

typedef struct Tarea {
int TareaID; //Numerado en ciclo iterativo
char *Descripcion; //
int Duracion; // entre 10 – 100
}TAREA;

void CargarTareas(TAREA **tarea, int cantidad);
void mostrarTarea(TAREA **tarea, int cantidad);
void moverTareas(TAREA **pTareas, TAREA **pTareasHechas, int cantidad);
void mostrarTareasHechasYPendientes(TAREA **pTareasHechas, TAREA **pTareasPendientes, int cantidad);

int main(){
    srand(time(NULL));

    int cantTareas;

    printf ("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d", &cantTareas);

    TAREA **pTareas, **pTareasHechas;
    pTareas = (TAREA**) malloc(sizeof(TAREA)*cantTareas);
    pTareasHechas = (TAREA**) malloc(sizeof(TAREA)*cantTareas);

    CargarTareas(pTareas, cantTareas);
    mostrarTarea(pTareas, cantTareas);
    moverTareas(pTareas, pTareasHechas, cantTareas);

    mostrarTareasHechasYPendientes(pTareasHechas, pTareas, cantTareas);

    return 0;

}

void CargarTareas(TAREA **tarea, int cantidad){

    for(int i=0; i < cantidad; i++){

        printf("------Carga de tareas----------\n");
        TAREA *buff=(TAREA *)malloc(sizeof(tarea));
        (buff)->TareaID=i+1;
        (buff)->Descripcion=(char *)malloc(sizeof(char)*100);
        fflush(stdin);
        printf("Ingresar Descripcion: \n");
        gets((buff)->Descripcion);
        (buff)->Duracion=rand()%(100-10+1)+10;
        *tarea=buff;
        tarea++;
    }
}

void mostrarTarea(TAREA **tarea, int cantidad){

    for(int i=0; i < cantidad; i++){
        printf("------Mostrar Tareas----------\n");
        printf("----Tarea ID [%d]----\n",(*tarea)->TareaID);
        printf("Descripcion de la tarea:%s\n",(*tarea)->Descripcion);
        printf("Duracion de la tarea:%d\n",(*tarea)->Duracion);
        tarea++;
    }
}

void moverTareas(TAREA **pTareas, TAREA **pTareasHechas, int cantidad){
    int si_o_no;

    printf("\n---------- Tareas Pendientes ----------\n");
    for (int i = 0; i < cantidad; i++)
    {
        if (*(pTareas + i) != NULL)
        {
            printf("----------------------------------------\n");
            printf("Tarea ID: %d\n", pTareas[i]->TareaID);
            printf("Descripcion: %s\n", pTareas[i]->Descripcion);
            printf("Duracion: %d\n", pTareas[i]->Duracion);
            printf("\n----- Mover a realizadas? (1 = SI; 0 = NO)-----\n");
            scanf("%d", &si_o_no);

            if (si_o_no == 1)
            {
                *(pTareasHechas + i) = *(pTareas + i);
                *(pTareas + i) = NULL;
            }else{
                *(pTareasHechas + i) = NULL;
            }
        }
    }
}

void mostrarTareasHechasYPendientes(TAREA **pTareasHechas, TAREA **pTareasPendientes, int cantidad){


    printf("\n---------- TAREAS REALIZADAS ----------\n");
    for (int i = 0; i < cantidad; i++)
    {
        if (pTareasHechas[i] != NULL)
        {
            printf("----------------------------------------\n");
            printf("Tarea ID: %d\n", pTareasHechas[i]->TareaID);
            printf("Descripcion: %s\n", pTareasHechas[i]->Descripcion);
            printf("Duracion: %d\n", pTareasHechas[i]->Duracion);
        }
    }

    printf("\n---------- TAREAS PENDIENTES ----------\n");
    for (int i = 0; i < cantidad; i++)
    {
        if (pTareasPendientes[i] != NULL)
        {
            printf("----------------------------------------\n");
            printf("Tarea ID: %d\n", pTareasPendientes[i]->TareaID);
            printf("Descripcion: %s\n", pTareasPendientes[i]->Descripcion);
            printf("Duracion: %d\n", pTareasPendientes[i]->Duracion);
        }
    }
}
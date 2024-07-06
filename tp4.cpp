#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea
{
    int TareaID;
    char *Descripcion;
    int Duracion;
} Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *siguiente;
} Nodo;
Nodo *CrearListaVacia();
Nodo *CrearNodo(Tarea tarea);
Tarea cargarTarea(int cantidadTareas);
void controlTareas(Nodo **ListaPendientes, Nodo **ListaRealizadas, Nodo **ListasProgreso);
void insertarNodo(Nodo **Start, Tarea tarea);
void mostrarTareas(Nodo *ListaTareas);
void moverTareas(Nodo **origen, Nodo **destino, int id);
Nodo *buscarporId(Nodo **ListaPendientes, Nodo **ListaRealizadas, Nodo **ListasProgreso, int id);
Nodo *BorrarNodo(Nodo **origen, Nodo *nodoaBorrar);

int main(int argc, char const *argv[])
{
    int eleccion, cantidadTareas = 0, id;
    char opcionSeguir;
    Nodo *ListaTareasPendientes, *ListaTareasRealizadas, *ListaTareasProgreso;

    ListaTareasPendientes = CrearListaVacia();
    ListaTareasPendientes = CrearListaVacia();
    ListaTareasPendientes = CrearListaVacia();

    do
    {
        cantidadTareas++;
        puts("*********** MENU ***********");
        printf("\t1 - Cargar tareas\n");
        printf("\t2 - Control de las tareas pendientes\n");
        printf("\t3 - Mostrar tareas realizadas, pendientes y en progreso \n");
        printf("\t4 - Buscar tareas por ID\n");
        printf("\t5 - Buscar tareas por palabra clave\n");
        printf("\t6 - Mostrar los tiempo\n");
        printf("\t7 - Modificar el lugar de la tarea por id\n");
        printf("\t8 - Eliminar Tarea por id\n");

        printf("\t9 - Salir\n");
        puts("\n");
        printf("Ingrese una opcion: ");
        fflush(stdin);
        scanf("%d", &eleccion);
    } while (eleccion != 9);

    switch (eleccion)
    {
    case 1:
        do
        {
            cantidadTareas++;
            printf("Tarea numero 100%d", cantidadTareas);
            Tarea tarea = cargarTarea(cantidadTareas);
            insertarNodo(&ListaTareasPendientes, tarea);
            printf("Desea agregar mas tareas?\n");
            printf("Presione 's' o 'S' para agregar mas tareas\n");
            printf("Presione cualquier otra tecla si no desea agregar mas tareas\n");
            fflush(stdin);
            scanf("%c", &opcionSeguir);
        } while (opcionSeguir == 's' || opcionSeguir == 'S');
        break;
    case 2:
        if (cantidadTareas == 0)
        {
            printf("No hay tareas a mostrar");
        }
        else
        {
            controlTareas(&ListaTareasPendientes, &ListaTareasProgreso, &ListaTareasRealizadas);
        }

        break;
    case 3:

        break;
    case 4:

        break;
    case 5:

        break;
    case 6:

        break;
    case 7:

        break;
    case 8:
        printf("Ingrese el id de la tarea que desea buscar:");
        scanf("%d", &id);
        char eleccionLista;
        Nodo *tareaBuscada = buscarporId(&ListaTareasPendientes, &ListaTareasProgreso, &ListaTareasRealizadas, id);
        if (tareaBuscada == NULL)
        {
            printf("No se encontró la tarea en las listas");
        }
        else
        {
            printf("Indique donde se encontró la lista:\n");
            printf("S:Lista tareas pendientes\n");
            printf("P:Lista tareas progreso\n");
            printf("R:Lista tareas realizadas\n");
            printf("Eleccion:");
            scanf("%s", &eleccionLista);
            if (eleccionLista == 'R' || eleccionLista == 'r')
            {
                BorrarNodo(&ListaTareasRealizadas, tareaBuscada);
            }
            if (eleccionLista == 'P' || eleccionLista == 'p')
            {
                BorrarNodo(&ListaTareasProgreso, tareaBuscada);
            }
            if (eleccionLista == 'S' || eleccionLista == 's')
            {
                BorrarNodo(&ListaTareasPendientes, tareaBuscada);
            }
        }

        break;

    default:
        break;
    }

    return 0;
}

Nodo *CrearListaVacia()
{
    return NULL;
}
Nodo *CrearNodo(Tarea tarea)
{
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->T = tarea;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}
void insertarNodo(Nodo **Start, Tarea tarea)
{
    Nodo *nuevoNodo = CrearNodo(tarea);
    nuevoNodo->siguiente = *Start;
    *Start = nuevoNodo;
}
void mostrarTareas(Nodo *ListaTareas)
{
    if (ListaTareas == NULL)
    {
        printf("No hay tareas a mostrar");
        return;
    }
    else
    {
        mostrarTareas(ListaTareas->siguiente);
        printf("La tarea con id 100%d\n", ListaTareas->T.TareaID);
        printf("Descripcion:%s\n", ListaTareas->T.Descripcion);
        printf("Duracion:%d\n", ListaTareas->T.Duracion);
    }
}
void moverTareas(Nodo **origen, Nodo **destino, int id)
{
    Nodo *actual = *origen;
    Nodo *anterior = NULL;

    while (actual != NULL && actual->T.TareaID != id)
    {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == NULL)
    {
        printf("No se pudo encontrar la tarea que indicó");
        return;
    }

    if (anterior == NULL)
    {
        *origen = actual->siguiente;
    }
    else
    {
        anterior->siguiente = actual->siguiente;
    }
    actual->siguiente = *destino;
    *destino = actual;
}
Nodo *buscarporId(Nodo **ListaPendientes, Nodo **ListaRealizadas, Nodo **ListasProgreso, int id)
{
    Nodo *aux;
    aux = *ListaPendientes;
    while (aux != NULL)
    {
        if (aux->T.TareaID == id)
        {
            return aux;
        }
        aux = aux->siguiente;
    }
    aux = *ListaRealizadas;
    while (aux != NULL)
    {
        if (aux->T.TareaID == id)
        {
            return aux;
        }
        aux = aux->siguiente;
    }
    aux = *ListasProgreso;
    while (aux != NULL)
    {
        if (aux->T.TareaID == id)
        {
            return aux;
        }
        aux = aux->siguiente;
    }

    return NULL;
}
Nodo *BorrarNodo(Nodo **origen, Nodo *nodoaBorrar)
{
    Nodo *temp = *origen;

    if (temp == nodoaBorrar)
    {
        *origen = temp->siguiente;
        free(temp);
    }
    while (temp->siguiente != NULL && temp->siguiente != nodoaBorrar)
    {
        temp = temp->siguiente;
    }
    if (temp->siguiente == NULL)
    {
        printf("No se pudo encontrar el elemento a borrar");
    }

    temp->siguiente = temp->siguiente->siguiente;
    free(nodoaBorrar);
}
void controlTareas(Nodo **ListaPendientes, Nodo **ListaRealizadas, Nodo **ListasProgreso)
{
    int id;
    char op;
    mostrarTareas(*ListaPendientes);
    printf("Ingrese el ultimo numero del id de la tarea que esta buscando:");
    fflush(stdin);
    scanf("%d", &id);
    printf("Desea mover la tarea Tareas Realizadas ? Responda 'R' o 'r'\n");
    printf("Desea mover la tarea Tareas en Progreso ? Responda 'P' o 'p'\n");
    fflush(stdin);
    scanf("%c", &op);
    if (op == 'R' || op == 'r')
    {
        moverTareas(ListaPendientes, ListaRealizadas, id);
    }
    if (op == 'P' || op == 'p')
    {
        moverTareas(ListaPendientes, ListasProgreso, id);
    }
}
Tarea cargarTarea(int cantidadTareas)
{
    Tarea tarea;
    tarea.TareaID = cantidadTareas;
    printf("Ingrese la descripcion de la tarea de no mas de 100 caracteres:");
    tarea.Descripcion = malloc(sizeof(char) * 100);
    fflush(stdin);
    gets(tarea.Descripcion);
    do
    {
        printf("Ingrese la duracion de la tarea entre 10 y 100:");
        fflush(stdin);
        scanf("%d", &tarea.Duracion);
    } while (tarea.Duracion >= 10 && tarea.Duracion <= 100);

    return tarea;
}

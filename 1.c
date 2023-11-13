#include <stdio.h>
#include "BRL.h"

typedef struct datos
{
    char status[10];
    char matricula[7];
    char ApPat[20];
    char ApMat[20];
    char Nombre[50];
    char Edad[3];
    char Sexo[8];
}Talum;


void cargar_Archivo();


int main()
{
    int menu = 0;
    int op;
    do
    {
        op = validarNumeros("--MENU--\n0.- Salir\n1.- Cargar Archivo\n2.- Agregar \n3.- Eliminar\n4.- Buscar \n5.- Ordenar\n6.- Mostrar Todo\n7.- Generar Archivo\n8.- Cantidad de registros en Archivo\n9.- Mostrar Borrados", 0, 9);
        switch (op)
        {
        case 0:
            system("cls");
            printf("FIN DEL PROGRAMA");
            break;
        case 1:
            cargar_Archivo();
            menu = 1;
            break;
        case 2:
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
            break;
        case 9:
            break;
        }
    } while (!menu);
}

void cargar_Archivo()
{


}
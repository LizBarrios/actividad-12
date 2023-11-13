// BarriosRetanaLizeth 372813
// 11-nov-23
/*
MENÚ
1.- Cargar Archivo
2.- Agregar
3.- Eliminar
4.- Buscar
5.- Ordenar
6.- Mostrar Todo
7.- Generar Archivo
8.- Cantidad de registros en Archivo
9.- Mostrar Borrados
0.- Salir
INSTRUCCIONES: Programa que contenga el menú anterior, el programa utiliza un
vector de registros de máximo 1,500 registros, de la siguiente estructura:
[status, matricula, ApPat, ApMat, Nombre, Edad, sexo] donde el campo llave es matricula.

datos.txt  es el archivo con los registros a cargar en el vector de registros

1.- Cargar Archivo : El programa deberá cargar el vector de registros desde el archivo
de texto (solo podrá cargarse una sola vez el archivo)
2.- Agregar : El programa deberá ser capaz de agregar un 10 registros al arreglo y al
final del archivo de texto.  (Generar automáticamente los datos).
3.- Eliminar : El programa deberá buscar una matrícula en el vector por medio del método
de búsqueda más óptimo. Utilizar banderas para escoger el método más adecuado., imprimir
el registro y preguntar si se quiere eliminar el registro, (al cerrar el programa se deberar
agregar al archivo borrados el registro o registros eliminados, asi se debera mantener dos
archivos uno con datos validos y otro con los datos que se borraron)
4.- Buscar : El programa deberá buscar una matrícula en el vector por medio del método de
búsqueda más óptimo. Utilizar banderas para escoger el método más adecuado. Mostrar los
datos en forma de registro
5.- Ordenar : El programa deberá ordenar el vector por medio del método de ordenación más
óptimo. Utilizar banderas para escoger el método más adecuado se ordenará por el campo llave
(matrícula)
6.- Mostrar Todo: El programa deberá mostrar todos los registros del vector tal y como están
 en ese momento ordenado o desordenado. (mostrar en forma de tabla, y de 40 en 40)
7.- Generar Archivo : El programa deberá preguntar al usuario el nombre del archivo,  solo
nombre sin extensión, el programa generará un archivo con el nombre proporcionado por el usuario
 con extensión .txt los datos que pondrá en el archivo de texto serán idénticos a los contenidos
 en el Vector de registros. (ordenado o desordenado). El programa podrá generar múltiples archivos
  para comprobar las salidas.
8.- Cantidad de registros en archivo : El programa deberá llamar a un archivo externo, donde mande
ejecutar el archivo y como parametros el nombre del archivo que se desea evaluar, el programa externo
deberar ser capaz de retornar un valor enero que sea la cantida de registros que contiene el archivo
en cuestion
9.- Mostrar Borrados: El programa deberá mostrar el archivo de texto tal y como se visualiza con la
cantidad de registros que se eliminaron del archivo original y que fueron marcados en su momnto como
registros eliminados
NOTA:  Programa 100% Validado.
NOTA 2: Si el programa vector cambia de tamaño por agregar un nuevo registro al salir el programa deberá actualizar o sustituir el datos.txt (debera contener puros registros validos los elimindos o inactivos deberan ser parte del archivo de texto2)
NOTA 3: Usar libreria propia
NOTA 4: archivo.txt es un ejemplo de cómo debe ser el archivo que se genere
*/
// BRL_act11_1_932

#include <stdio.h>
#include "BRL.h"
typedef struct Reg
{
    int Matricula;
    char Nombre[30];
    char ApPat[30];
    char ApMat[30];
    int Edad;
    char sexo[10];
    int Status;
} Tdatos;

void registros_automaticos(Tdatos registros[], int *num_registros);
void imprimir(Tdatos registros[], int num_registros);
void imprimir_en_archivo(Tdatos registros[], int num_registros, FILE *fa, char *nombre_archivo);
void dar_de_baja_registro(Tdatos registros[], int *num_registros, int matricula_a_eliminar);
void imprimir_eliminados(Tdatos registros[], int num_registros, FILE *fa);
int mostrar_registro(Tdatos registros[], int *num_registros, int matricula);
void ordenar(Tdatos registros[], int *num_registros);
int particion(Tdatos registros[], int ri, int rs);
void quicksort(Tdatos registros[], int ri, int rs);
void ordenarQuickSort(Tdatos registros[], int *num_registros);
void cantidad_de_registros(FILE *fa, char *nombre_archivo);
void buscar(Tdatos registros[], int *num_registros);
void copiarArchivo(FILE *fa);

int main()
{
    Tdatos registros[1500];
    FILE *archivo, *carpeta_de_eliminados;
    carpeta_de_eliminados = fopen("archivos_dados_de_baja.txt", "a");
    char nombre_archivo[20];
    int num_registros = 0, matricula_a_eliminar, encontrado, ordenado = 1, quieres_eliminar;
    int opc, menu;
    do
    {
        menu = 1;
        opc = validarnumeros("\n--MENU--\n1.- Cargar Archivo\n2.- Agregar \n3.- Eliminar\n4.- Buscar\n5.- Ordenar\n6.- Mostrar Todo\n7.- Generar Archivo\n8.- Cantidad de registros en Archivo\n9.- Mostrar Borrados\n0.-salir\n", 0, 9);
        switch (opc)
        {
        case 0:
            system("cls");
            printf("FIN DEL PROGRAMA");
            return 0;
            break;
        case 1:
        copiarArchivo(archivo);
            break;
        case 2:
            registros_automaticos(registros, &num_registros);
            ordenado = 1;

            break;

        case 3:
            matricula_a_eliminar = validarnumeros("INGRESE LA MATRICULA DEL REGISTRO PARA ELIMINAR SU REGISTRO\n", 200000, 400000);
            encontrado = mostrar_registro(registros, &num_registros, matricula_a_eliminar);
            if (encontrado == 1)
            {
                quieres_eliminar = validarnumeros("QUIERES ELIMINAR ESTE REGISTRO?\n1.-SI\n2.-NO\n", 1, 2);
                if (quieres_eliminar == 1)
                {
                    dar_de_baja_registro(registros, &num_registros, matricula_a_eliminar);
                    imprimir_eliminados(registros, num_registros, carpeta_de_eliminados);
                    imprimir_en_archivo(registros, num_registros, archivo, nombre_archivo);
                    ordenado = 1;
                }
            }

            break;

        case 4:
            if (num_registros > 0)
            {
                buscar(registros, &num_registros);
            }
            else
            {
                printf("NO HAY REGISTROS\n");
            }
            break;
        case 5:
            if (num_registros > 0)
            {
                if (ordenado == 1)
                {
                    if (num_registros <= 500)
                    {
                        ordenar(registros, &num_registros);
                        printf("ORDENADO POR METODO DE BURBUJA\n");
                    }
                    else
                    {
                        ordenarQuickSort(registros, &num_registros);
                        printf("ORDENADO POR METODO QUICKSORT\n");
                    }
                    ordenado = 0;
                }
                else
                {
                    printf("YA ESTA ORDENADO\n");
                    getchar();
                }
            }
            else
            {
                printf("NO HAY REGISTROS\n");
            }

            break;

        case 6:
            if (ordenado == 0)
            {
                printf("ESTAN ORDENADOS\n");
            }
            else
            {
                printf("ESTAN DESORDENADOS\n");
            }
            if (num_registros > 0)
            {
                imprimir(registros, num_registros);
            }
            else
            {
                printf("NO HAY REGISTROS\n");
            }
            break;
        case 7:
            printf("INGRESE EL NOMBRE DEL ARCHIVO\n");
            gets(nombre_archivo);
            strcat(nombre_archivo, ".txt");
            archivo = fopen(nombre_archivo, "a");
            imprimir_en_archivo(registros, num_registros, archivo, nombre_archivo);

            break;
        case 8:
            printf("INGRESE EL NOMBRE DEL ARCHIVO\n");
            gets(nombre_archivo);
            strcat(nombre_archivo, ".txt");
            cantidad_de_registros(archivo, nombre_archivo);
            break;

        case 9:
            imprimir_eliminados(registros, num_registros, carpeta_de_eliminados);
            break;
        }

    } while (menu == 1);
    fclose(carpeta_de_eliminados);
}
void registros_automaticos(Tdatos registros[], int *num_registros)
{
    char hombres[20][10] = {"JUAN", "PEDRO", "CARLOS", "LUIS", "JAVIER", "ANDRES", "ALEJANDRO", "MIGUEL", "JOSE", "ADAN", "JORGE", "GABRIEL", "ROBERTO", "DAVID", "FERNANDO", "RAUL", "EDUARDO", "SERGIO", "ANTONIO", "FRANCISCO"};
    char mujeres[20][10] = {"DANIELA", "LAURA", "ANA", "CARMEN", "SOFIA", "ISABEL", "MARTA", "PAULA", "ELENA", "PATRICIA", "LUCIA", "CLARA", "ROSA", "BEATRIZ", "CAROLINA", "JULIA", "TERESA", "SARA", "IRENE", "ADRIANA"};
    char apPaterno[20][10] = {"BARRIOS", "RODRIGUEZ", "LOPEZ", "PEREZ", "MARTINEZ", "SANCHEZ", "FERNANDEZ", "GONZALEZ", "RAMIREZ", "TORRES", "MARTIN", "JIMENEZ", "RUIZ", "DIAZ", "SOTO", "GOMEZ", "LOZANO", "CASTRO", "HERRERA", "GARCIA"};
    char apMaterno[20][10] = {"SUAREZ", "VILLEGAS", "GUERRERO", "PALACIOS", "FARIAS", "AVILA", "MOLINA", "SALAZAR", "DELGADO", "SANCHEZ", "FLORES", "MORALES", "ROMERO", "OROZCO", "RIVERA", "CASTILLO", "CHAVEZ", "SUAREZ", "VILLEGAS", "GUERRERO"};
    char GenSex[2][10] = {"HOMBRE", "MUJER"};

    int k;

    for (k = 0; k < 10; k++)
    {
        Tdatos *registro = &registros[*num_registros];
        int edad = 0, numsexo = 0, matricula = 0;
        int numero_nombre2;

        matricula = random(200000, 400000);
        registro->Matricula = matricula;

        numsexo = random(1, 2);
        strcpy(registro->sexo, GenSex[numsexo - 1]);
        if (numsexo == 1)
        {
            strcpy(registro->Nombre, hombres[rand() % 20]);
            numero_nombre2 = rand() % 2;
            if (numero_nombre2 == 0)
            {
                strcat(registro->Nombre, "_");
                strcat(registro->Nombre, hombres[rand() % 20]);
            }
        }
        else
        {
            strcpy(registro->Nombre, mujeres[rand() % 20]);
            if (numero_nombre2 == 0)
            {
                strcat(registro->Nombre, "_");
                strcpy(registro->Nombre, mujeres[rand() % 20]);
            }
        }
        strcpy(registro->ApPat, apPaterno[rand() % 20]);
        strcpy(registro->ApMat, apMaterno[rand() % 20]);

        edad = random(18, 30);
        registro->Edad = edad;

        strcpy(registro->sexo, GenSex[numsexo - 1]);

        registro->Status = 1;
        (*num_registros)++;
        if (*num_registros > 1499)
        {
            printf("REGISTROS LLENOS");
            k = 100;
        }
    }
}
void imprimir(Tdatos registros[], int num_registros)
{
    int i, acu = 1;
    printf("Registros almacenados:\n");
    printf("=======================================================================================================\n");
    printf("|  No. | Matricula |          Nombre              | Apellido Pat.   | Apellido Mat.   | Edad |  Sexo  |\n");
    printf("=======================================================================================================\n");

    for (i = 0; i < num_registros; i++)
    {
        if (registros[i].Status == 1)
        {
            printf("| %-4d | %-9d | %-28s | %-15s | %-15s | %-4d | %-6s |\n", i + 1, registros[i].Matricula, registros[i].Nombre, registros[i].ApPat, registros[i].ApMat, registros[i].Edad, registros[i].sexo);
            printf("=======================================================================================================\n");

            if (acu == 40)
            {
                getchar();
                acu = 0;
            }
            acu++;
        }
    }
}
void imprimir_en_archivo(Tdatos registros[], int num_registros, FILE *fa, char *nombre_archivo)
{
    int i, acu = 1;
    fa = fopen(nombre_archivo, "w");
    for (int i = 0; i < num_registros; i++)
    {
        if (!feof(fa))
        {
            fprintf(fa, " ");
        }
    }
    if (num_registros == 0)
    {
        fprintf(fa, "No hay registros para imprimir.\n");
        fclose(fa);
        return;
    }
    fprintf(fa, "\nRegistros almacenados:\n");
    fprintf(fa, "  No.    Matricula   Nombre                         Apellido Pat.     Apellido Mat.     Edad   Sexo   \n");

    for (i = 0; i <= num_registros; i++)
    {
        if (registros[i].Status == 1)
        {
            fprintf(fa, "  %-4d   %-9d   %-28s   %-15s   %-15s   %-4d   %-6s  \n", i + 1, registros[i].Matricula, registros[i].Nombre, registros[i].ApPat, registros[i].ApMat, registros[i].Edad, registros[i].sexo);

            if (acu == 40)
            {
                getchar();
                acu = 0;
            }
            acu++;
        }
    }
    fclose(fa);
}
void dar_de_baja_registro(Tdatos registros[], int *num_registros, int matricula_a_eliminar)
{
    int i;
    for (i = 0; i <= *num_registros; i++)
    {
        if (registros[i].Matricula == matricula_a_eliminar)
        {
            if (registros[i].Status == 1)
            {
                registros[i].Status = 2;
                printf("REGISTRO DADO DE BAJA\n");

                (*num_registros)--;
            }
            else
            {
                printf("EL REGSITRO YA ESTA DADO DE BAJA");
            }
        }
    }
}
void imprimir_eliminados(Tdatos registros[], int num_registros, FILE *fa)
{
    int i, acu = 1;

    fa = fopen("archivos_dados_de_baja.txt", "w");
    for (i = 0; i < num_registros; i++)
    {
        if (!feof(fa))
        {
            fprintf(fa, " ");
        }
    }
    if (num_registros == 0)
    {
        fprintf(fa, "No hay registros para imprimir.\n");
        fclose(fa);
        return;
    }
    fprintf(fa, "\nRegistros ELIMINADOS:\n");
    fprintf(fa, "  No.    Matricula   Nombre                         Apellido Pat.     Apellido Mat.     Edad    Sexo   \n");

    for (i = 0; i <= num_registros; i++)
    {
        if (registros[i].Status == 2)
        {
            fprintf(fa, "  %-4d   %-9d   %-28s   %-15s   %-15s   %-4d   %-6s  \n", i + 1, registros[i].Matricula, registros[i].Nombre, registros[i].ApPat, registros[i].ApMat, registros[i].Edad, registros[i].sexo);

            if (acu == 40)
            {
                getchar();
                acu = 0;
            }
            acu++;
        }
    }
    fclose(fa);
}
int mostrar_registro(Tdatos registros[], int *num_registros, int matricula)
{
    int i;

    for (i = 0; i < *num_registros; i++)
    {
        if (registros[i].Matricula == matricula)
        {
            printf("Registros almacenado:\n");
            printf("=======================================================================================================\n");
            printf("|  No. | Matricula |          Nombre              | Apellido Pat.   | Apellido Mat.   | Edad |  Sexo  |\n");
            printf("=======================================================================================================\n");

            printf("| %-4d | %-9d | %-28s | %-15s | %-15s | %-4d | %-6s |\n", i + 1, registros[i].Matricula, registros[i].Nombre, registros[i].ApPat, registros[i].ApMat, registros[i].Edad, registros[i].sexo);
            printf("=======================================================================================================\n");

            return 1;
        }
    }

    printf("NO SE ENCONTRO LA MATRICULA\n\n");
    return 0;
}
void ordenar(Tdatos registros[], int *num_registros)
{
    Tdatos temp;
    int i, j;
    for (i = 0; i < *num_registros; i++)
    {
        for (j = 0; j < *num_registros - 1; j++)
        {
            if (registros[j].Matricula > registros[j + 1].Matricula)
            {
                temp = registros[j];
                registros[j] = registros[j + 1];
                registros[j + 1] = temp;
            }
        }
    }
}
int particion(Tdatos registros[], int ri, int rs)
{
    int tem2;
    int i, j;

    tem2 = registros[rs].Matricula;
    i = (ri - 1);

    for (j = ri; j < rs; j++)
    {
        if (registros[j].Matricula < tem2)
        {
            i++;
            Tdatos temp = registros[i];
            registros[i] = registros[j];
            registros[j] = temp;
        }
    }

    Tdatos temp = registros[i + 1];
    registros[i + 1] = registros[rs];
    registros[rs] = temp;

    return (i + 1);
}
void quicksort(Tdatos registros[], int ri, int rs)
{
    int pi;
    if (ri < rs)
    {
        pi = particion(registros, ri, rs);

        quicksort(registros, ri, pi - 1);
        quicksort(registros, pi + 1, rs);
    }
}
void ordenarQuickSort(Tdatos registros[], int *num_registros)
{
    quicksort(registros, 0, *num_registros - 1);
} // fue mi aportacion al codigo jijiji
void cantidad_de_registros(FILE *fa, char *nombre_archivo)
{
    int con = -3;
    fa = fopen(nombre_archivo, "r");
    if (fa == NULL)
    {
        printf("El archivo no se pudo abrir o no existe.\n");
        return;
    }
    char c;
    while ((c = fgetc(fa)) != EOF)
    {
        if (c == '\n')
        {
            con++;
        }
    }
    fclose(fa);
    printf("------------------------------\n");
    printf("Registros del archivo: [  %-4d]\n", con);
    printf("------------------------------\n");
}
void buscar(Tdatos registros[], int *num_registros)
{
    int numero_matricula, encoontrado = 0;
    numero_matricula = validarnumeros("INRESE LA MATRICULA\n", 200000, 400000);

    for (int i = 0; i < *num_registros; i++)
    {
        if (registros[i].Matricula == numero_matricula)
        {
            printf("============================================================================\n");
            printf("| Registro %d:                                                              |\n", i + 1);
            printf("|--------------------------------------------------------------------------|\n");
            printf("| Matricula: %-7d                                                       |\n", registros[i].Matricula);
            printf("| Nombre: %-30s                                   |\n", registros[i].Nombre);
            printf("| Apellido Paterno: %-25s                              |\n", registros[i].ApPat);
            printf("| Apellido Materno: %-25s                              |\n", registros[i].ApMat);
            printf("| Edad: %-2d                                                                 |\n", registros[i].Edad);
            printf("| Sexo: %-10s                                                         |\n", registros[i].sexo);
            printf("============================================================================\n");
        }
        encoontrado = 1;
    }
    if (encoontrado == 0)
    {
        printf("NO SE ENCONTRO LA MATRICULA\n\n");
    }
}
void copiarArchivo(FILE *fa)
{
    FILE *archivo_origen;
    char caracter, nombre_externo[30], nombre_destino[30];
    printf("INGRESE EL NOMBRE DEL ARCHIVO EXTERNO\n");
    gets(nombre_externo);
    strcat(nombre_externo, ".txt");
    archivo_origen = fopen(nombre_externo, "r");
    if (archivo_origen == NULL)
    {
        printf("No se pudo abrir el archivo externo.\n");
        return;
    }
    
    printf("INGRESE EL NOMBRE DEL ARCHIVO DESTINO\n");
    gets(nombre_destino);
    strcat(nombre_destino, ".txt");
    fa = fopen(nombre_destino, "w");
    if (fa == NULL)
    {
        printf("No se pudo crear o abrir el archivo.\n");
        fclose(archivo_origen);
        return;
    }

    while ((caracter = fgetc(archivo_origen)) != EOF)
    {
        fputc(caracter, fa);
    }

    fclose(archivo_origen);
    fclose(fa);
}
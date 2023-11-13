#include <stdio.h>
#include <stdlib.h>

#define MAX_REGISTROS 50
#define MAX_LONGITUD_NOMBRE 30
#define MAX_LONGITUD_APELLIDO 30

typedef struct {
    int Matricula;
    char Nombre[MAX_LONGITUD_NOMBRE];
    char ApPat[MAX_LONGITUD_APELLIDO];
    char ApMat[MAX_LONGITUD_APELLIDO];
    int Edad;
    char Sexo[MAX_LONGITUD_NOMBRE];
    int Status;
} Tdatos;

int main() {
    FILE *archivo;
    Tdatos registros[MAX_REGISTROS];
    int i = 0;

    archivo = fopen("Lizeth.txt", "r");

    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Leer datos del archivo y almacenar en el vector de registros
    while (i < MAX_REGISTROS && fscanf(archivo, "%d %s %s %s %d %s %d",
                  &registros[i].Matricula,
                  registros[i].Nombre,
                  registros[i].ApPat,
                  registros[i].ApMat,
                  &registros[i].Edad,
                  registros[i].Sexo,
                  &registros[i].Status) == 7) {
        i++;
    }

    fclose(archivo);

    // Verificar si se leyeron registros
    if (i == 0) {
        printf("No se leyeron registros desde el archivo.\n");
        return 1;
    }

    // Ahora el vector de registros contiene los datos del archivo

    // Puedes realizar cualquier operación con los datos cargados
    // Por ejemplo, imprimirlos en la consola

    printf("Registros cargados:\n");
    printf("Matricula   Nombre                         Apellido Pat.     Apellido Mat.     Edad   Sexo   Status\n");
    for (int j = 0; j < i; j++) {
        printf("%d      %s                    %s           %s           %d     %s     %d\n",
               registros[j].Matricula,
               registros[j].Nombre,
               registros[j].ApPat,
               registros[j].ApMat,
               registros[j].Edad,
               registros[j].Sexo,
               registros[j].Status);
    }

    return 0;
}

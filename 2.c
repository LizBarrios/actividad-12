#include <stdio.h>
#include <string.h>

typedef struct Reg {
    int Matricula;
    char Nombre[30];
    char ApPat[30];
    char ApMat[30];
    int Edad;
    char Sexo[10];
    int Status;
} Tdatos;

#define P 100  // Definir P según tus necesidades

void carg_txt(Tdatos alu[], int *p) {
    int v;
    char name[20];
    printf("Ingrese el nombre del documento\n");
    do {
        gets(name);
        v = 0;  // Aquí deberías validar el nombre según tus necesidades
    } while (v == 1);
    strcat(name, ".txt");

    FILE *doc = fopen(name, "r");
    if (doc) {
        Tdatos reg;
        char cad[10];  // Ajusta el tamaño según tus necesidades
        int i;
        while (!feof(doc)) {
            if ((*p + 1) <= P) {
                reg.Status = 1;
                fscanf(doc, "%d.- %d %s %s %s %d %s", &i, &reg.Matricula, reg.Nombre, reg.ApPat, reg.ApMat, &reg.Edad, cad);

                if (strcmp(cad, "HOMBRE") == 0 || strcmp(cad, "MASCULINO") == 0) {
                    strcpy(reg.Sexo, "HOMBRE");
                } else if (strcmp(cad, "MUJER") == 0 || strcmp(cad, "FEMENINO") == 0) {
                    strcpy(reg.Sexo, "MUJER");
                } else {
                    // Manejar otro caso si es necesario
                }

                alu[(*p)++] = reg;
            } else {
                printf("Registro lleno\n");
            }
        }

        printf("Registros cargados\n");
        // system("PAUSE"); // Evita el uso de system("PAUSE")
        getchar();  // Pausa la ejecución hasta que el usuario presiona Enter
    } else {
        printf("Error 404\nNo se encontró el archivo o no existe\n");
        // system("PAUSE"); // Evita el uso de system("PAUSE")
        getchar();  // Pausa la ejecución hasta que el usuario presiona Enter
    }
    fclose(doc);
}

int main() {
    Tdatos vector_de_registros[P];
    int contador_registros = 0;

    carg_txt(vector_de_registros, &contador_registros);

    // Resto de tu programa...

    return 0;
}

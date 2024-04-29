/*Ejercicio 1
Realizar un programa en el cual se ingresen los siguientes datos
Nombre, Apellido y DNI
a) Crear un menu donde se ingresen los datos y los guarde en un
archivo
b) Otro ítem donde se pueda realizar una búsqueda por DNI y
devuelva los datos de Nombre y apellido
c) Salir del mismo*/


#include <stdio.h>
#include <string.h>

#define MAX_NOMBRE 50
#define MAX_APELLIDO 50

typedef struct {
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
    int dni;
} Persona;

void guardarPersona(FILE *archivo) {
    Persona persona;
    printf("Ingrese el nombre: ");
    fgets(persona.nombre, MAX_NOMBRE, stdin);
    persona.nombre[strcspn(persona.nombre, "\n")] = '\0';

    printf("Ingrese el apellido: ");
    fgets(persona.apellido, MAX_APELLIDO, stdin);
    persona.apellido[strcspn(persona.apellido, "\n")] = '\0';

    printf("Ingrese el DNI: ");
    scanf("%d%*c", &persona.dni);

    fwrite(&persona, sizeof(Persona), 1, archivo);
    printf("Datos guardados en el archivo.\n");
}

void buscarPorDNI(FILE *archivo) {
    Persona persona;
    int dni, encontrado = 0;
    printf("Ingrese el DNI a buscar: ");
    scanf("%d%*c", &dni);

    rewind(archivo);
    while (fread(&persona, sizeof(Persona), 1, archivo) == 1) {
        if (persona.dni == dni) {
            printf("Nombre: %s\n", persona.nombre);
            printf("Apellido: %s\n", persona.apellido);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontro ninguna persona con ese DNI.\n");
    }
}

int main() {
    FILE *archivo = fopen("personas.dat", "rb+");
    if (archivo == NULL) {
        archivo = fopen("personas.dat", "wb+");
        if (archivo == NULL) {
            printf("Error al crear el archivo.\n");
            return 1;
        }
    }

    int opcion;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Ingresar datos\n");
        printf("2. Buscar por DNI\n");
        printf("3. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d%*c", &opcion);

        switch (opcion) {
            case 1:
                guardarPersona(archivo);
                break;
            case 2:
                buscarPorDNI(archivo);
                break;
            case 3:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción invalida.\n");
        }
    } while (opcion != 3);

    fclose(archivo);
    return 0;
}

/*3) Agregarle validación de datos de manera que no se repitan cuando
sea necesario. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOMBRE 50
#define MAX_APELLIDO 50

typedef struct {
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
    int dni;
} Persona;

int dniExistente(FILE *archivo, int dni) {
    Persona persona;
    rewind(archivo);
    while (fread(&persona, sizeof(Persona), 1, archivo) == 1) {
        if (persona.dni == dni) {
            return 1;  // DNI existente
        }
    }
    return 0;  // DNI no existente
}

void guardarPersona(FILE *archivo) {
    Persona persona;
    int dniValido = 0;

    printf("Ingrese el nombre: ");
    fgets(persona.nombre, MAX_NOMBRE, stdin);
    persona.nombre[strcspn(persona.nombre, "\n")] = '\0';

    printf("Ingrese el apellido: ");
    fgets(persona.apellido, MAX_APELLIDO, stdin);
    persona.apellido[strcspn(persona.apellido, "\n")] = '\0';

    do {
        printf("Ingrese el DNI: ");
        scanf("%d%*c", &persona.dni);

        if (dniExistente(archivo, persona.dni)) {
            printf("El DNI ya existe, ingrese otro DNI.\n");
        } else {
            dniValido = 1;
        }
    } while (!dniValido);

    fwrite(&persona, sizeof(Persona), 1, archivo);
    printf("Datos guardados en el archivo.\n");
}

void buscarPorNombreYApellido(FILE *archivo) {
    Persona persona;
    char nombreBuscar[MAX_NOMBRE], apellidoBuscar[MAX_APELLIDO];
    int encontrado = 0;

    printf("Ingrese el nombre a buscar: ");
    fgets(nombreBuscar, MAX_NOMBRE, stdin);
    nombreBuscar[strcspn(nombreBuscar, "\n")] = '\0';

    printf("Ingrese el apellido a buscar: ");
    fgets(apellidoBuscar, MAX_APELLIDO, stdin);
    apellidoBuscar[strcspn(apellidoBuscar, "\n")] = '\0';

    // Convertir a minúsculas para hacer la búsqueda case-insensitive
    for (int i = 0; nombreBuscar[i]; i++) {
        nombreBuscar[i] = tolower(nombreBuscar[i]);
    }
    for (int i = 0; apellidoBuscar[i]; i++) {
        apellidoBuscar[i] = tolower(apellidoBuscar[i]);
    }

    rewind(archivo);
    while (fread(&persona, sizeof(Persona), 1, archivo) == 1) {
        char nombreMinusculas[MAX_NOMBRE], apellidoMinusculas[MAX_APELLIDO];
        strcpy(nombreMinusculas, persona.nombre);
        strcpy(apellidoMinusculas, persona.apellido);

        // Convertir a minúsculas para hacer la comparación case-insensitive
        for (int i = 0; nombreMinusculas[i]; i++) {
            nombreMinusculas[i] = tolower(nombreMinusculas[i]);
        }
        for (int i = 0; apellidoMinusculas[i]; i++) {
            apellidoMinusculas[i] = tolower(apellidoMinusculas[i]);
        }

        if (strcmp(nombreMinusculas, nombreBuscar) == 0 && strcmp(apellidoMinusculas, apellidoBuscar) == 0) {
            printf("Nombre: %s\n", persona.nombre);
            printf("Apellido: %s\n", persona.apellido);
            printf("DNI: %d\n", persona.dni);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("No se encontro ninguna persona con ese nombre y apellido.\n");
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
        printf("2. Buscar por nombre y apellido\n");
        printf("3. Salir\n");
        printf("Ingrese una opcion: ");
        if (scanf("%d%*c", &opcion) != 1) {
            printf("Opcion inválida. Ingrese un numero entero.\n");
            scanf("%*c"); // Limpiar el buffer de entrada
        } else {
            switch (opcion) {
                case 1:
                    guardarPersona(archivo);
                    break;
                case 2:
                    buscarPorNombreYApellido(archivo);
                    break;
                case 3:
                    printf("Saliendo del programa...\n");
                    break;
                default:
                    printf("Opcion invalida.\n");
            }
        }
    } while (opcion != 3);

    fclose(archivo);
    return 0;
}

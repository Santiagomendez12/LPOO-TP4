/*5) Guardar Los cambios en un archivo con nombre pertinente sin
modificar el original
y pudiendo tener acceso a los mismos*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 50
#define MAX_APELLIDO 50
#define MAX_DNI 20
#define MAX_PERSONAS 100

// Estructura para almacenar los datos de una persona
typedef struct {
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
    char dni[MAX_DNI];
} Persona;

// Función para guardar los datos de una persona en un archivo
void guardarDatos(Persona persona, const char *nombreArchivo) {
    FILE *archivo;
    Persona temp;
    int duplicado = 0;

    // Verificar si el registro ya existe
    archivo = fopen(nombreArchivo, "r");
    if (archivo != NULL) {
        while (fscanf(archivo, "%s %s %s", temp.nombre, temp.apellido, temp.dni) != EOF) {
            if (strcmp(temp.dni, persona.dni) == 0) {
                duplicado = 1;
                break;
            }
        }
        fclose(archivo);
    }

    if (duplicado) {
        printf("Error: El DNI %s ya existe en la base de datos.\n", persona.dni);
    } else {
        archivo = fopen(nombreArchivo, "a"); // Abre el archivo en modo append (agregar al final)
        if (archivo == NULL) {
            printf("Error al abrir el archivo.\n");
            return;
        }
        fprintf(archivo, "%s %s %s\n", persona.nombre, persona.apellido, persona.dni);
        fclose(archivo);
        printf("Datos guardados exitosamente en %s.\n", nombreArchivo);
    }
}

// Función para buscar y mostrar los datos de una persona por nombre y apellido
void buscarPorNombreApellido(char nombreBuscar[], char apellidoBuscar[], const char *nombreArchivo) {
    FILE *archivo;
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
    char dni[MAX_DNI];
    int encontrado = 0;

    archivo = fopen(nombreArchivo, "r"); // Abre el archivo en modo lectura
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    while (fscanf(archivo, "%s %s %s", nombre, apellido, dni) != EOF) {
        if (strcmp(nombre, nombreBuscar) == 0 && strcmp(apellido, apellidoBuscar) == 0) {
            printf("Nombre: %s\n", nombre);
            printf("Apellido: %s\n", apellido);
            printf("DNI: %s\n", dni);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Persona con nombre %s y apellido %s no encontrada.\n", nombreBuscar, apellidoBuscar);
    }
    fclose(archivo);
}

// Función para comparar dos personas por nombre y apellido
int compararPorNombreApellido(const void *a, const void *b) {
    const Persona *personaA = (const Persona *)a;
    const Persona *personaB = (const Persona *)b;
    int comparacionApellido = strcmp(personaA->apellido, personaB->apellido);
    if (comparacionApellido == 0) {
        return strcmp(personaA->nombre, personaB->nombre);
    }
    return comparacionApellido;
}

// Función para comparar dos personas por DNI
int compararPorDNI(const void *a, const void *b) {
    const Persona *personaA = (const Persona *)a;
    const Persona *personaB = (const Persona *)b;
    return strcmp(personaA->dni, personaB->dni);
}

int main() {
    int opcion;
    Persona personas[MAX_PERSONAS];
    int numPersonas = 0;
    char nombreArchivo[MAX_NOMBRE];

    do {
        printf("\n--- Menu ---\n");
        printf("1. Ingresar datos de una persona\n");
        printf("2. Buscar persona por nombre y apellido\n");
        printf("3. Mostrar personas ordenadas por nombre y apellido\n");
        printf("4. Mostrar personas ordenadas por DNI\n");
        printf("5. Guardar datos en un archivo nuevo\n");
        printf("6. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer del teclado

        switch (opcion) {
            case 1:
                printf("\nIngrese el nombre: ");
                fgets(personas[numPersonas].nombre, MAX_NOMBRE, stdin);
                personas[numPersonas].nombre[strcspn(personas[numPersonas].nombre, "\n")] = 0; // Eliminar el salto de línea
                printf("Ingrese el apellido: ");
                fgets(personas[numPersonas].apellido, MAX_APELLIDO, stdin);
                personas[numPersonas].apellido[strcspn(personas[numPersonas].apellido, "\n")] = 0; // Eliminar el salto de línea
                printf("Ingrese el DNI: ");
                fgets(personas[numPersonas].dni, MAX_DNI, stdin);
                personas[numPersonas].dni[strcspn(personas[numPersonas].dni, "\n")] = 0; // Eliminar el salto de línea
                numPersonas++;
                break;
            case 2:
                if (numPersonas == 0) {
                    printf("Error: No hay datos ingresados.\n");
                    break;
                }
                printf("\nIngrese el nombre a buscar: ");
                fgets(personas[numPersonas].nombre, MAX_NOMBRE, stdin);
                personas[numPersonas].nombre[strcspn(personas[numPersonas].nombre, "\n")] = 0; // Eliminar el salto de línea
                printf("Ingrese el apellido a buscar: ");
                fgets(personas[numPersonas].apellido, MAX_APELLIDO, stdin);
                personas[numPersonas].apellido[strcspn(personas[numPersonas].apellido, "\n")] = 0; // Eliminar el salto de línea
                buscarPorNombreApellido(personas[numPersonas].nombre, personas[numPersonas].apellido, nombreArchivo);
                break;
            case 3:
                if (numPersonas == 0) {
                    printf("Error: No hay datos ingresados.\n");
                    break;
                }
                printf("\nIngrese el nombre del archivo donde desea guardar los datos: ");
                fgets(nombreArchivo, MAX_NOMBRE, stdin);
                nombreArchivo[strcspn(nombreArchivo, "\n")] = 0; // Eliminar el salto de línea
                printf("\nPersonas ordenadas por nombre y apellido:\n");
                qsort(personas, numPersonas, sizeof(Persona), compararPorNombreApellido);
                for (int i = 0; i < numPersonas; i++) {
                    printf("Nombre: %s\n", personas[i].nombre);
                    printf("Apellido: %s\n", personas[i].apellido);
                    printf("DNI: %s\n", personas[i].dni);
                    printf("\n");
                }
                break;
            case 4:
                if (numPersonas == 0) {
                    printf("Error: No hay datos ingresados.\n");
                    break;
                }
                printf("\nIngrese el nombre del archivo donde desea guardar los datos: ");
                fgets(nombreArchivo, MAX_NOMBRE, stdin);
                nombreArchivo[strcspn(nombreArchivo, "\n")] = 0; // Eliminar el salto de línea
                printf("\nPersonas ordenadas por DNI:\n");
                qsort(personas, numPersonas, sizeof(Persona), compararPorDNI);
                for (int i = 0; i < numPersonas; i++) {
                    printf("Nombre: %s\n", personas[i].nombre);
                    printf("Apellido: %s\n", personas[i].apellido);
                    printf("DNI: %s\n", personas[i].dni);
                    printf("\n");
                }
                break;
            case 5:
                if (numPersonas == 0) {
                    printf("Error: No hay datos ingresados.\n");
                    break;
                }
                printf("\nIngrese el nombre del archivo donde desea guardar los datos: ");
                fgets(nombreArchivo, MAX_NOMBRE, stdin);
                nombreArchivo[strcspn(nombreArchivo, "\n")] = 0; // Eliminar el salto de línea
                FILE *archivoGuardado;
                archivoGuardado = fopen(nombreArchivo, "w");
                if (archivoGuardado == NULL) {
                    printf("Error al abrir el archivo.\n");
                    break;
                }
                for (int i = 0; i < numPersonas; i++) {
                    fprintf(archivoGuardado, "%s %s %s\n", personas[i].nombre, personas[i].apellido, personas[i].dni);
                }
                fclose(archivoGuardado);
                printf("Datos guardados exitosamente en %s.\n", nombreArchivo);
                break;
            case 6:
                printf("\nSaliendo del programa.\n");
                break;
            default:
                printf("\nOpcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 6);

    return 0;
}


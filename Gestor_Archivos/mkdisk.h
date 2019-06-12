#ifndef MKDISK_H
#define MKDISK_H
#include <time.h>
#include "estructuras.h"

void ProcesoMKDISK(char* entrada, int linea);
void CrearDisco(char* size, char* fit, char* unit, char* path, int linea);
MBR CrearMBR(int tam, int signature, char* fit);
#endif // MKDISK_H

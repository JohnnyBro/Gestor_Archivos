#include "analizador.h"
#include "mkdisk.h"
#include "mrdisk.h"
#include "fdisk.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>


void Analisis(char* entrada, int linea)
{
    char *comando=malloc(200);
    strcpy(comando,entrada);
    comando=strtok(comando," ");

    if(strcasecmp(comando,"MKDISK")==0)
        ProcesoMKDISK(entrada, linea);
    else if (strcasecmp(comando,"RMDISK")==0)
        ProcesoRMDISK(entrada,linea);
    else if(strcasecmp(comando,"FDISK")==0)
        ProcesoFDISK(entrada,linea);
    else if(strcasecmp(comando,"MOUNT")==0)
        MOUNT(entrada,linea);// falta modificar esto*******
    else if(strcasecmp(comando,"UNMOUNT")==0)
        UNMOUNT(entrada,linea);
    else if(strcasecmp(comando,"PAUSE")==0)
        PAUSE();
    else
        printf("\nxxxxxxxxxx\nERROR! Linea %d: comando invalido\nxxxxxxxxxx\n", linea);

}

void MOUNT(char* entrada, int linea)
{
    printf("INGRESO A MOUNT: %s\n", entrada);
}
void UNMOUNT(char* entrada, int linea)
{
    printf("INGRESO A UNMOUNT: %s\n", entrada);
}
void PAUSE()
{
    printf("INGRESO A PAUSE\n");
}

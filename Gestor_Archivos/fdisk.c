#include "fdisk.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

void ProcesoFDISK(char* entrada, int linea)
{
    char* fdisk=malloc(200);
    char* size=malloc(200);
    char* unit=malloc(200);
    char* path=malloc(200);
    char* type=malloc(200);
    char* fit=malloc(200);
    char* delete=malloc(200);
    char* name=malloc(200);
    char* add=malloc(200);

    strcpy(fdisk,entrada);
    fdisk=strtok(fdisk," -");
    while(fdisk!=NULL)
    {
        if(strcasecmp(fdisk,"MKDISK")==0)
            printf("mk par: %s\n",fdisk);
        else if(strcasestr(fdisk,"size")!=NULL)
            strcpy(size,fdisk);
        else if(strcasestr(fdisk,"unit")!=NULL)
            strcpy(unit,fdisk);
        else if(strcasestr(fdisk,"path")!=NULL)
            strcpy(path,fdisk);
        else if(strcasestr(fdisk,"type")!=NULL)
            strcpy(type,fdisk);
        else if(strcasestr(fdisk,"fit")!=NULL)
            strcpy(fit,fdisk);
        else if(strcasestr(fdisk,"delete")!=NULL)
            strcpy(delete,fdisk);
        else if(strcasestr(fdisk,"name")!=NULL)
            strcpy(name,fdisk);
        else
            printf("\nxxxxxxxxxx\nAVISO! Linea %d: PARAMETRO INCOMPLETO O INVALIDO: %s\nxxxxxxxxxx\n",linea,fdisk);

        fdisk=strtok(NULL,"-");
    }


}

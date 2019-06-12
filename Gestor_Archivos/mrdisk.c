#include "mrdisk.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

void ProcesoRMDISK(char* entrada, int linea)
{
    char* rmdisk=malloc(200);
    char* path=malloc(200);
    strcpy(rmdisk,entrada);
    rmdisk=strtok(rmdisk," -");
    while(rmdisk!=NULL)
    {
        if(strcasecmp(rmdisk,"MKDISK")==0)
            printf("mk par: %s\n",rmdisk);
        else if(strcasestr(rmdisk,"path")!=NULL)
            strcpy(path,rmdisk);
        else
            printf("\nxxxxxxxxxx\nAVISO! Linea %d: PARAMETRO INCOMPLETO O INVALIDO: %s\nxxxxxxxxxx\n",linea,rmdisk);

        rmdisk=strtok(NULL,"-");
    }
}

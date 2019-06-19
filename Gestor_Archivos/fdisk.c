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
    fdisk=strtok(fdisk," ");
    while(fdisk!=NULL)
    {
        if(strcasecmp(fdisk,"FDISK")==0)
        {
            printf("FDISk par: %s\n",fdisk);
            fdisk=strtok(NULL,"-");
        }else if(strcasestr(fdisk,"size")!=NULL)
        {
            strcpy(size,fdisk);
            fdisk=strtok(NULL,"-");
        }else if(strcasestr(fdisk,"unit")!=NULL)
        {
            strcpy(unit,fdisk);
        }else if(strcasestr(fdisk,"path")!=NULL)
        {
            strcpy(path,fdisk);
            fdisk=strtok(NULL,"-");
        }else if(strcasestr(fdisk,"type")!=NULL)
        {
            strcpy(type,fdisk);
            fdisk=strtok(NULL,"-");
        }else if(strcasestr(fdisk,"fit")!=NULL)
        {
            strcpy(fit,fdisk);
            fdisk=strtok(NULL,"-");
        }else if(strcasestr(fdisk,"delete")!=NULL)
        {
             strcpy(delete,fdisk);
             fdisk=strtok(NULL,"-");
        }else if(strcasestr(fdisk,"name")!=NULL)
        {
            strcpy(name,fdisk);
            fdisk=strtok(NULL,"-");
        }else if(strcasestr(fdisk,"add")!=NULL)
        {
             strcpy(add,fdisk);
             fdisk=strtok(NULL," ");
        }
        else
            printf("\nxxxxxxxxxx\nAVISO! Linea %d: PARAMETRO INCOMPLETO O INVALIDO: %s\nxxxxxxxxxx\n",linea,fdisk);


    }


    size=strtok(size,"~:");
    size=strtok(NULL,"~:");
    unit=strtok(unit,"~:");
    unit=strtok(NULL,"~:");
    path=strtok(path,"~:");
    path=strtok(NULL,"~:");
    type=strtok(type,"~:");
    type=strtok(NULL,"~:");
    fit=strtok(fit,"~:");
    fit=strtok(NULL,"~:");
    delete=strtok(delete,"~:");
    delete=strtok(NULL,"~:");
    name=strtok(name,"~:");
    name=strtok(NULL,"~:");
    add=strtok(add,"~:");
    add=strtok(NULL,"~:");

    Validadciones(size, unit, path, type, fit, delete, name, add,linea);
}

void Validadciones(char* size, char* unit, char* path, char* type, char* fit, char* delete, char* name, char* add, int linea)
{
    //ver el signo del add

    int tam=atoi(size);
    signed int ad=0;
    int flag_size=0;
    int flag_unit=0;
    int flag_path=0;
    int flag_type=0;
    int flag_fit=0;
    int flag_delete=0;
    int flag_name=0;
    int flag_add=0;

    if(add!=NULL && delete!=NULL)
    {
        printf("\nxxxxxxxxxx\nERROR! Linea %d: NO SE PERMITEN LOS COMANDOS 'ADD' Y 'DELETE' EN LA MISMA INSTRUCCION : \nxxxxxxxxxx\n",linea);
        return;
    }else
    {
        if(add!=NULL)
        {
           ad=malloc(200);
           ad=atoi(add);
           printf("parametro add: %d\n",ad);
        }else if(delete!=NULL)
        {

        }else
        {

        }
    }

    if(path!=NULL && name!=NULL)
    {
        if(add==NULL && delete==NULL)//se crea una particion
        {

        }else
        {
            if(delete!=NULL)//se elimina la particion
            {

            }else
            {
                if(tam<0)//quita espacio de la particion
                {

                }else if(tam>0)//agrega espadcio en la particion
                {

                }else
                {
                    printf("\nxxxxxxxxxx\nERROR! Linea %d: EL PARAMETRO 'SIZE' NO PUEDE SER IGUAL A CERO \nxxxxxxxxxx\n",linea);
                    return;
                }
            }
        }
    }else
    {
        printf("\nxxxxxxxxxx\nERROR! Linea %d: PARAMETROS INCOMPLETOS O INVALIDOS: \nxxxxxxxxxx\n",linea);
        return;
    }




//    if(path!=NULL && name!=NULL && tam>0 )
//    {
//        if(unit!=NULL)//validando UNIT
//        {
//            unit=malloc(200);
//            if(strcasecmp(unit,"B")==0)
//                flag_unit=1;
//            else if(strcasecmp(unit,"k")==0)
//                flag_unit=1;
//            else if(strcasecmp(unit,"M")==0)
//                flag_unit=1;
//            else
//                printf("\nxxxxxxxxxx\nERROR! Linea %d: PARAMETROS INVALIDOS EN COMANDO 'UNIT' \nxxxxxxxxxx\n",linea);
//        }else
//        {
//           unit=malloc(200);
//           strcpy(unit,"K");
//           flag_unit=1;
//        }

//        if(fit!=NULL)
//        {
//            fit=malloc(200);
//            if(strcasecmp(fit,"BF")==0)
//                flag_fit=1;
//            else if(strcasecmp(fit,"FF")==0)
//                flag_fit=1;
//            else if(strcasecmp(fit,"WF")==0)
//                flag_fit=1;
//            else
//                printf("\nxxxxxxxxxx\nERROR! Linea %d: PARAMETROS INVALIDOS EN COMANDO 'FIT': \nxxxxxxxxxx\n",linea);
//        }else
//        {
//            fit=malloc(200);
//            strcpy(fit,"WF");
//            flag_fit=1;
//        }

//        if(delete!=NULL)
//        {
//            if(strcasecmp(delete,"FAST")==0)
//                flag_delete=1;
//            else if(strcasecmp(delete,"FULL")==0)
//                flag_delete=1;
//            else
//                printf("\nxxxxxxxxxx\nERROR! Linea %d: PARAMETROS INVALIDOS EN COMANDO 'DELETE': \nxxxxxxxxxx\n",linea);
//        }else
//        {
//            flag_delete=1;
//        }

//        if(add!=NULL)
//        {
//            ad=atoi(add);
//            if(add!=0)
//                flag_add=1;
//            else
//                printf("\nxxxxxxxxxx\nERROR! Linea %d: PARAMETROS INVALIDOS EN COMANDO 'ADD': \nxxxxxxxxxx\n",linea);
//        }
//    }else
//    {
//        printf("\nxxxxxxxxxx\nERROR! Linea %d: PARAMETROS INCOMPLETOS O INVALIDOS: \nxxxxxxxxxx\n",linea);
//    }
}




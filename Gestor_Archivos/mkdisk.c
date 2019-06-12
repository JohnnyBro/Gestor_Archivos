#include "mkdisk.h"
#include "estructuras.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <setjmp.h>
#include <libgen.h>
#include <time.h>

void ProcesoMKDISK(char* entrada, int linea)
{
     char* mkdisk=malloc(200);
     char* size=malloc(200);
     char* fit=malloc(200);
     char* unit=malloc(200);
     char* path=malloc(200);
     strcpy(mkdisk,entrada);
     mkdisk=strtok(mkdisk," -");
     while(mkdisk!=NULL)
     {
         if(strcasecmp(mkdisk,"MKDISK")==0)
             printf("mk par: %s\n",mkdisk);
         else if(strcasestr(mkdisk,"size")!=NULL)
             strcpy(size,mkdisk);
         else if(strcasestr(mkdisk,"fit")!=NULL)
             strcpy(fit,mkdisk);
         else if(strcasestr(mkdisk,"unit")!=NULL)
             strcpy(unit,mkdisk);
         else if(strcasestr(mkdisk,"path")!=NULL)
             strcpy(path,mkdisk);
         else
             printf("\nxxxxxxxxxx\nAVISO! Linea %d: PARAMETRO INCOMPLETO O INVALIDO: %s\nxxxxxxxxxx\n",linea,mkdisk);

         mkdisk=strtok(NULL,"-");
     }

     size=strtok(size,"~:");
     size=strtok(NULL,"~:");
     fit=strtok(fit,"~:");
     fit=strtok(NULL,"~:");
     unit=strtok(unit,"~:");
     unit=strtok(NULL,"~:");
     path=strtok(path,"~:");
     path=strtok(NULL,"~:");

    CrearDisco(size, fit, unit, path, linea);
}

void CrearDisco(char* size, char* fit, char* unit, char* path, int linea)
{
    int tam=0;
    tam=atoi(size);
    int flag_tam=0;
    int flag_fit=0;
    int flag_unit=0;
    int flag_path=0;



    if(path!=NULL && tam>0)
    {
        flag_tam=1;
        if(fit!=NULL)//validando el parametro 'FIT'*****
        {

            if(strstr(fit," ")!=NULL)
                fit=strtok(fit," ");

            if(strcasecmp(fit,"BF")==0 || strcasecmp(fit,"FF")==0 || strcasecmp(fit,"WF")==0)
            {
                flag_fit=1;
            }else
            {
                printf("\nxxxxxxxxxx\nERROR! Linea %d: valor incorrecto en el parametro 'FIT'\nxxxxxxxxxx\n",linea);
            }
        }else
        {
            fit=malloc(200);
            strcpy(fit,"FF");
            flag_fit=1;
        }

        if(unit!=NULL)//Validadndo el parametro 'UNIT'*****
        {
            if(strstr(unit," ")!=NULL)
                unit=strtok(unit," ");

            if(strcasecmp(unit,"K")==0)
            {
                tam=tam*1;
                flag_unit=1;
            }else if(strcasecmp(unit,"M")==0)
            {
                tam=tam*1000;
                flag_unit=1;
            }else
            {
                printf("\nxxxxxxxxxx\nERROR! Linea %d: valor incorrecto en el parametro 'UNIT'\nxxxxxxxxxx\n",linea);
            }
        }else
        {
            unit=malloc(200);
            strcpy(unit,"M");
            tam=tam*1000;
            flag_unit=1;
        }

        if(strstr(path,"\"")!=NULL)
        {
            path=strtok(path,"\"");
        }

        //separando el directorio y el nombre del archivos*****
        char *disk_name=basename(path); //obtengo el nombre del archivo
        char *disk_dir=dirname(path);   //obtengo la ruta del archivo sin el slash  '/' que divide la ruta y el nombre del archivo

        if(strcasestr(disk_name,".disk")!=NULL)//validando el path.
            flag_path=1;

        if(flag_tam==1 && flag_fit==1 && flag_unit==1 && flag_path)// se creara el disco solo si los parametros son correctos
        {
            //creando directorio*****
            char *dir=malloc(200);
            strcpy(dir,"mkdir -p '");
            strcat(dir,disk_dir);
            strcat(dir,"'");        // al final tendriamos algo como esto: mkdir -p '/home/archivos/fase1' por si viniera algun espacio entre la ruta, linux lo reconocera por estar entre comillas ' '.
            system(dir);            // se usa la instruccion system() para crear el directorio.
            printf("Se creo el directorio %s \n",disk_dir);

            //Creando el archivo binario que simula el disco duro*****
            char *path_aux=malloc(200);
            //strcpy(path_aux,"\"");
            strcpy(path_aux,path);
            strcat(path_aux,"/");
            strcat(path_aux,disk_name);
            //strcat(path_aux,"\""); //se le vuelve a agregar las comillas por si existe algun espacio de por medio y evitar crear el archivo en un directorio erroneo.
            printf("path completo: %s\n",path_aux);
            FILE *file=fopen(path_aux, "wb");
            free(path_aux);

            if(file!=NULL)
            {
                fseek(file,0, SEEK_SET);
                char buffer[1000];
                for(int i=0; i<tam; i++)
                {
                    fwrite(buffer, sizeof (buffer),1,file);
                }

                time_t t;
                srand((unsigned) time(&t));
                int signature = rand()%50;
                MBR master=CrearMBR(tam, signature,fit);
                printf("SE CREO EL MBR CON TAMANIO DE: %d",sizeof (master));

                fseek(file, 0, SEEK_SET);
                fwrite(&master,sizeof(MBR),1,file);


                fseek(file, 0, SEEK_SET);
                fread(&master, sizeof(MBR),1,file);

                printf("\n*****MBR******\n");
                printf("Tamanio: %d\n",master.mbr_tamanio);
                printf("Signature: %d\n",master.mbr_disk_signature);
                printf("Fit: %c\n",master.mbr_disk_fit);
                struct tm *ts;
                char buf[80];
                ts = localtime(&master.mbr_fecha_creacion);
                strftime(buf, sizeof (buf), "%A %Y/%m/%d %H:%M:%S", ts);
                printf("Fecha de MBR: %s\n", buf);
                printf("SE CREO EL DISCO %s SATISFACTORIAMENTE\n",disk_name);
                fclose(file);

                //**voy por aqui


            }else
            {

            }

        }else
        {
            printf("\nxxxxxxxxxx\nERROR! Linea %d: No se pudo crear el disco primero corrija los errores aneriores y vuelva a interntar.\nxxxxxxxxxx\n",linea);
            return;
        }
    }else
    {
        printf("\nxxxxxxxxxx\nERROR! Linea %d: valores incorrectos en los parametros 'SIZE' o 'PATH'\nxxxxxxxxxx\n",linea);
        return;
    }
}

MBR CrearMBR(int tam, int signature, char* fit)
{
    //char aux[2];
    //strcpy(aux,fit);
    MBR nuevo;
    nuevo.mbr_tamanio = tam;
    nuevo.mbr_fecha_creacion=time(0);
    nuevo.mbr_disk_signature=signature;
    nuevo.mbr_disk_fit=fit[0];

    struct tm *ts;
    char buf[80];
    ts=localtime(&nuevo.mbr_fecha_creacion);
    strftime(buf,sizeof(buf),"%A %Y/%m/%d %H:%M:%S",ts);
    //printf("\tfecha de MBR: %s\n",buf);

    for(int i=0; i<4;i++)
    {
        nuevo.part[i].part_fit='0';
        strcpy(nuevo.part[i].part_name,"");
        nuevo.part[i].part_size=0;
        nuevo.part[i].part_start=0;
        nuevo.part[i].part_status='0';
        nuevo.part[i].part_type='0';
    }

    return nuevo;
}

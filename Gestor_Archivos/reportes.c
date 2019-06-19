#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stropts.h>
#include "reportes.h"
#include "estructuras.h"

void ProcesoRep(char* entrada, int linea)
{
    char* rep=malloc(200);
    char* name=malloc(200);
     char* path=malloc(200);
    char* id=malloc(200);

    strcpy(rep,entrada);
    rep=strtok(rep," -");
    while(rep!=NULL)
    {
        if(strcasecmp(rep,"REP")==0)
            printf("REP par: %s\n",rep);
        else if(strcasestr(rep,"NAME")!=NULL)
            strcpy(name,rep);
        else if(strcasestr(rep,"ID")!=NULL)
            strcpy(id,rep);
        else if(strcasestr(rep,"path")!=NULL)
            strcpy(path,path);
        else
            printf("\nxxxxxxxxxx\nAVISO! Linea %d: PARAMETRO INCOMPLETO O INVALIDO: %s\nxxxxxxxxxx\n",linea);

        rep=strtok(NULL,"-");
    }

    name=strtok(name,"~:");
    name=strtok(NULL,"~:");
    path=strtok(path,"~:");
    path=strtok(NULL,"~:");
    id=strtok(id,"~:");
    id=strtok(NULL,"~:");

    CrearReporte(name, path, id, linea);
}

void CrearReporte(char* name, char* path, char* id, int linea)
{
    if(name!=NULL && path!=NULL && id!=NULL)
    {
        if(strstr(path,"\"")!=NULL)
        {
            path=strtok(path,"\"");
        }

        FILE* file = fopen(path, "r+b");
        if(file==NULL)
        {
            printf("\nxxxxxxxxxx\nAVISO! Linea %d: EL ARCHIVO NO EXISTE EN INSTRUCCION 'REP': %s\nxxxxxxxxxx\n",linea);
            return;
        }

        MBR nuevo;
        fseek(file, 0, SEEK_SET);
        fread(&nuevo, sizeof(nuevo), 1, file);

        printf("%d\n",nuevo.mbr_tamanio);
        struct tm *ts;
        char buf[80];
        ts=localtime(&nuevo.mbr_fecha_creacion);
        strftime(buf,sizeof(buf),"%A %Y/%m/%d %H:%M:%S",ts);
        printf("\tfecha de MBR: %s\n",buf);
        printf("%d\n",nuevo.mbr_disk_signature);

        for(int i=0; i<4 ;i++)
        {
            printf("%d\n",nuevo.part[i].part_size);
            printf("%c\n",nuevo.part[i].part_fit);
            printf("%s\n",nuevo.part[i].part_name);
            printf("%c\n",nuevo.part[i].part_status);
            printf("%d\n",nuevo.part[i].part_start);
            printf("%c\n",nuevo.part[i].part_type);

        }
        fclose(file);
        GraficarMBR(name, path, id, linea);
    }else
    {
        printf("\nxxxxxxxxxx\nERROR! Linea %d: INSTRUCCION REP INCOMPLETA INGRESE TODOS LOS COMANDOS REQUERIDOS: %s\nxxxxxxxxxx\n",linea);
    }
}


void GraficarMBR(char* name, char* path, char*id, int linea)
{
    if(strstr(path,"\"")!=NULL)
    {
        path=strtok(path,"\"");
    }
    if(strcasestr(name,"MBR")!=NULL)
    {

    }else if(strcasestr(name,"DISK")!=NULL)
    {

    }else
    {
        return;
    }

    FILE *archivo_dot;
    printf("\n pathReporte:   %s", path);
    archivo_dot = fopen(path, "w");
    fprintf(archivo_dot, "digraph G {\n");
    fprintf(archivo_dot, "node[shape=record]\n");
    fprintf(archivo_dot, "edge[arrowhead = none, headlabel=1, taillabel = 1]\n");

    FILE *disco = fopen(path, "r+b");
    if (disco != NULL)
    {
        MBR nuevo;
        fseek(disco, 0, SEEK_SET);
        fread(&nuevo, sizeof(nuevo), 1, disco);
        struct tm *ts;
        char buf[80];
        ts=localtime(&nuevo.mbr_fecha_creacion);
        strftime(buf,sizeof(buf),"%A %Y/%m/%d %H:%M:%S",ts);

        //printf("\n%d",nuevo.mbr_tamanio);
        //printf("\n%s",nuevo.mbr_fecha_creacion);
        //printf("\n%d",nuevo.mbr_signature);

        fprintf(archivo_dot, "a0 [label = \"{%s|mbr_tamanio:%d|mbr_fecha_creacion:%s|"
                "mbr_disk_signature:%d", "Disco 1", nuevo.mbr_tamanio,
                buf, nuevo.mbr_disk_signature);
        for(int i=0; i<4 ;i++)
        {
            fprintf(archivo_dot, "|%s|part_status:%c|part_type:%c|part_fit:%c|"
                    "part_start:%d|part_size:%d",
                    nuevo.part[i].part_name,
                    nuevo.part[i].part_status, nuevo.part[i].part_type,
                    nuevo.part[i].part_fit, nuevo.part[i].part_start,
                    nuevo.part[i].part_size);
        }
        fprintf(archivo_dot, "}\"];");
        fprintf(archivo_dot, "}");
        fclose(disco);
        fclose(archivo_dot);
    }

        char lineaDot1[150] = "dot ";
        strcat(lineaDot1, "/home/johnny/Documentos/Entradas_MIAF1/grafo.txt");
        strcat(lineaDot1, " -o ");
        strcat(lineaDot1, "/home/johnny/Documentos/Entradas_MIAF1/grafo");
        strcat(lineaDot1, ".png -Tpng");
        printf("\nPATH: %s\n", lineaDot1);
        system(lineaDot1);
        printf("\n");
        printf("%s\n",lineaDot1);

        char lineaDot2[150] = "xdg-open ";
        strcat(lineaDot2, "/home/johnny/Documentos/Entradas_MIAF1/grafo.png");
        printf("\nPATH: %s\n", lineaDot2);
        system(lineaDot2);
        printf("\n");
        printf("%s\n",lineaDot2);
}

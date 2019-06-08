#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "analizador.h"

static int salir=0;

void LectorEntrada(void);
void LimpiarPantalla(void);
void ComandoExec(char* entrada);
char* LimpiarEntrada(char* entrada);
char* LeerComentario(char* entrada);
char* UnirLinea(char* entrada);
void Salir(void);


int main()
{
    printf("Hello World!\n");
    LectorEntrada();

    return 0;
}

void LectorEntrada()
{
    char* ln_completa=malloc(200);
    char* entrada=malloc(200);
    char* cadena =NULL;

    while(salir==0)
    {
        printf("MIA-> ");
        fgets(entrada,200,stdin);
        if(strcasecmp(entrada,"\n")==0)
        {
            printf("***INGRESE ALGUN COMANDO***\n");
        }else
        {
            cadena=LimpiarEntrada(entrada);
            if(strcasecmp(cadena,"EXIT")==0)
            {
                Salir();
            }else if(strcasecmp(cadena,"CLEAR")==0)
            {
                LimpiarPantalla();
            }else
            {
                if(strstr(cadena,"#")!=NULL)
                {
                    char *aux=LeerComentario(cadena);
                    if(aux!=NULL)
                    {
                        strcpy(cadena,aux);
                    }else
                    {
                        continue;
                    }
                }

                if(strstr(cadena,"\\")!=NULL)
                {
                    if(strcasecmp(ln_completa,"")==0)
                    {
                        strcpy(ln_completa,UnirLinea(cadena));
                    }else
                    {
                        strcat(ln_completa," ");
                        strcat(ln_completa,UnirLinea(cadena));
                    }

                }else
                {
                    if(strcasecmp(ln_completa,"")!=0)
                    {
                        strcat(ln_completa," ");
                        strcat(ln_completa,cadena);
                        //printf("Analizar: %s\n",ln_completa);
                        if(strcasestr(ln_completa,"EXEC")!=NULL)
                        {
                            printf("comando exec: %s\n",ln_completa);
                            ComandoExec(ln_completa);
                        }else
                        {
                            printf("analisis: %s\n",ln_completa);
                            Analisis(ln_completa);
                        }
                        strcpy(ln_completa,"");
                    }else
                    {
                        if(strcasestr(cadena,"EXEC")!=NULL)
                        {
                            printf("comando exec: %s\n",cadena);
                            ComandoExec(cadena);
                        }else
                        {
                            printf("comando: %s\n", cadena);
                            Analisis(cadena);
                        }
                    }
                }
            }
        }
        //free(cadena);
        //free(entrada);
    }


}

void ComandoExec(char *entrada)
{
    int cont=0;
    char *aux=strtok(entrada," ");
    aux=strtok(NULL," ");
    aux=strtok(aux,"~:");

    while (aux!=NULL)
    {
        cont++;
        aux=strtok(NULL,"~:");
    }

    if(cont<=1)//lo hago para confirmar que la instruccion -path~:~"ruta" este completa
    {
        printf("ERROR! instruccion 'EXEC' incompleta\n");
    }else
    {
       FILE *file;

    }
}


void LimpiarPantalla()
{
    system("clear");
}

void Salir()
{
    salir=1;
}

char* LimpiarEntrada(char* entrada)
{
    entrada=strtok(entrada,"\n");
    return (entrada);
   /*
    char *salto=strtok(entrada, "\n");
    char *aux=malloc(200);
    strcpy(aux,salto);
    while(salto!=NULL)
    {
        salto=strtok(NULL,"\n");
    }
    free(salto);
    return aux;
    */

}

char* LeerComentario(char* entrada)
{
    char linea[200];
    strcpy(linea,entrada);

    if(linea[0]=='#')
    {
        return (NULL);
    }else
    {
        entrada=strtok(entrada,"#");
        return (entrada);
    }
}

char* UnirLinea(char* entrada)
{
    char *aux=strtok(entrada,"\\");
    return aux;
}



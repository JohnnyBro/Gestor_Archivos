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
            printf("\nxxxxxxxxxx\nINGRESE ALGUN COMANDO\nxxxxxxxxxx\n");
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
                        //strcat(ln_completa," ");
                        strcat(ln_completa,cadena);
                        if(strcasestr(ln_completa,"EXEC")!=NULL)
                        {
                            ComandoExec(ln_completa);
                        }else
                        {
                            Analisis(ln_completa, 0);
                        }
                        strcpy(ln_completa,"");
                    }else
                    {
                        if(strcasestr(cadena,"EXEC")!=NULL)
                        {
                            ComandoExec(cadena);
                        }else
                        {
                            Analisis(cadena, 0);
                        }
                    }
                }
            }
        }
    }


}

void ComandoExec(char *entrada)
{
    char* cmd_completo=malloc(200);
    char *aux=strtok(entrada," ");
    aux=strtok(NULL," ");
    aux=strtok(aux,"~:");

    if(aux==NULL)
    {
        printf("\nxxxxxxxxxx\nERROR NO CONTROLADO! instruccion 'EXEC' invalida\nxxxxxxxxxx\n");
    }else
    {
        if(strcasecmp(aux,"-path")==0)
        {
            aux=strtok(NULL,"~:");
            printf("la ruta es: %s\n", aux);
            FILE *file;
            file=fopen(aux, "r");

            if(file==NULL)
            {
                printf("\nxxxxxxxxxx\nArchivo no existe.\nxxxxxxxxxx\n");
            }else
            {
                printf("leyendo archivo.....\n");
                char linea[200];
                int cont_linea=0;
                char *lectura;
                while(fgets(linea,200,file)!=NULL)
                {
                    cont_linea++;
                    //Se enviara a analizar linea por linea
                    lectura=LimpiarEntrada(linea);
                    if(lectura!=NULL)
                    {
                        if(strstr(lectura,"#")!=NULL)
                        {
                            char *auxA=LeerComentario(lectura);
                            if(auxA!=NULL)
                            {
                                strcpy(lectura,auxA);
                            }else
                            {
                                continue;
                            }
                        }

                        if(strstr(lectura,"\\")!=NULL)
                        {
                            if(strcasecmp(cmd_completo,"")==0)
                            {
                                strcpy(cmd_completo,UnirLinea(lectura));
                            }else
                            {
                                strcat(cmd_completo," ");
                                strcat(cmd_completo,UnirLinea(lectura));
                            }

                        }else
                        {
                            if(strcasecmp(cmd_completo,"")!=0)
                            {
                                //strcat(cmd_completo," ");
                                strcat(cmd_completo,lectura);
                                Analisis(cmd_completo, cont_linea);
                                strcpy(cmd_completo,"");
                            }else
                            {
                                Analisis(lectura,cont_linea);
                            }
                        }
                    }else
                    {
                        continue;
                    }
                }
            }

        }else
        {
            printf("\nxxxxxxxxxx\nERROR! instruccion 'EXEC' incompleta\nxxxxxxxxxx\n");
        }
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
}

char* LeerComentario(char* entrada)
{
    char linea[200];
    strcpy(linea,entrada);

    if(linea[0]=='#')
    {
        printf("%s\n", entrada);
        return (NULL);
    }else
    {
        char *aux=malloc(200);
        entrada=strtok(entrada,"#");
        strcpy(aux,entrada);
        entrada=strtok(NULL,"#");
        if(entrada!=NULL)
        {
            printf("#%s\n",entrada);
            printf("%s\n",aux);
        }
        return (aux);
    }
}

char* UnirLinea(char* entrada)
{
    char *aux=strtok(entrada,"\\");
    return aux;
}

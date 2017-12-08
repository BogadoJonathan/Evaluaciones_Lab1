#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ArrayList.h"
#include "letra.h"


int ingresarNumero(char mensaje[100], int minimo, int maximo)
{
    int retorno=0;
    int i;
    char numero[300];
    int numeroVerdadero;
    do
    {
        do
        {
            printf("%s", mensaje);
            scanf("%s",numero);
            retorno=1;
            int cantidad=strlen(numero);
            for (i=0; i<cantidad; i++)
            {
                if(isalpha(numero[i]))
                {
                    printf("No puede ingresar letra/s\n");
                    system("pause");
                    retorno=0;
                    break;
                }
            }
        }
        while(retorno==0);
        numeroVerdadero=atoi(numero);
        if (numeroVerdadero>=minimo && numeroVerdadero<=maximo)
            retorno=1;
        else
        {
            retorno=0;
            printf("Tiene que ingresar un numero desde el %d hasta el %d\n",minimo,maximo);
            system("pause");
        }
    }
    while(retorno==0);

    return numeroVerdadero;
}

void ingresarTexto(char mensaje[100],char *Destino,int desde, int hasta,char ingresarNumeros)
{
    int cantidad;
    int verificacion=1;
    int i;
    char texto[hasta];

    do
    {
        printf("\n%s",mensaje);
        fflush(stdin);
        fgets(texto,hasta+1,stdin);
        for(i=0; i<=hasta; i++)
        {
            if(texto[i]=='\n')
                texto[i]='\0';
        }
        cantidad=strlen(texto);
        if(cantidad>=desde && cantidad<=hasta)
        {
            verificacion=0;
            if(ingresarNumeros=='n'){
            for(i=0; i<cantidad; i++)
            {
                if(isdigit(texto[i]))
                {
                    printf("no puede ingresar numeros\n");
                    verificacion=1;
                    break;
                }
            }
            }
        }
        else
        {
            printf("supero el limite de caracteres permitidos o no ingreso nada\n");
        }
    }while(verificacion);
    strcpy(Destino,texto);
}

int menu (void)
{
    printf("1 - Dar de alta\n");
    printf("2 - Completar\n");
    printf("3 - Comprobar\n");
    printf("4 - Generar y listar\n");
    printf("5 - Salir.\n");

    return ingresarNumero("Ingrese opcion: ",1,5);
}


void darDeAlta(ArrayList *pLista)
{
    char *letra=NULL;
    char buffer[3][20];
    int verificacion;
    eLetra *pLetra=NULL;
    FILE *archivo=fopen("datos.csv","r");
    if(archivo==NULL)
        exit(1);
            letra=malloc(sizeof(char));
            fscanf(archivo,"%[^,],%[^,],%[^,],%[^\n]\n",letra,buffer[0], buffer[1], buffer[2]);
    while(!feof(archivo))
    {
            pLetra=malloc(sizeof(eLetra));
            letra=malloc(sizeof(char));
            fscanf(archivo,"%[^,],%[^,],%[^,],%[^\n]\n",letra,buffer[0], buffer[1], buffer[2]);
            pLetra->letra=*letra;
            strcpy(pLetra->nombre,buffer[0]);
            pLetra->vocal=atoi(buffer[1]);
            pLetra->consonante=atoi(buffer[2]);
            verificacion=al_add(pLista,pLetra);
            if(verificacion)
                printf("La carga fallo");
    }

    printf("Carga exitosa\n");
    system("pause");
    free(pLetra);
    fclose(archivo);
}

void completar(ArrayList *pList){
    int max=al_len(pList);
    int i;
    eLetra *pLetra=NULL;

    for(i=0;i<max;i++)
    {
        pLetra=malloc(sizeof(eLetra));
         pLetra=al_get(pList,i);
         if(pLetra->letra=='a' || pLetra->letra=='e' || pLetra->letra=='i' || pLetra->letra=='o' || pLetra->letra=='u')
         {
             pLetra->vocal=1;
         }
         else
            pLetra->consonante=1;

         al_set(pList,i,pLetra);

    }
    free(pLetra);
}

void comprobar(ArrayList *pList)
{
    int retorno=0;
    char palabra[19];
    char *letra;
    int max,i,j;
    int maxLetra=al_len(pList);
    int verificador=0;
    eLetra *pLetra=NULL;
    ingresarTexto("Ingrese palabra: ",palabra,1,20,'n');
    max=strlen(palabra);

    for(i=0;i<maxLetra;i++)
    {
        pLetra=malloc(sizeof(eLetra));
        letra=malloc(sizeof(char));
        pLetra=al_get(pList,i);
        *letra=pLetra->letra;
        if(verificador==max)
        {
         retorno=1;
         break;
        }
        for(j=0;j<max;j++)
        {
           if(*letra==palabra[j]){
            verificador++;
            break;
           }

        }
    }

    if(retorno==1)
        puts("Existen letras necesarias para su existencia");
    else
        puts("NO Existen letras necesarias para su existencia");


}

void generarYListas (ArrayList *letraRepetidas, ArrayList *letraSinRepetir, ArrayList *pList)
{
    int max=al_len(pList);
    int i,j;
    int contador=0;
    eLetra *pLetra=NULL;
    letraRepetidas=al_clone(pList);
    letraSinRepetir=al_clone(pList);

    for(i=0;i<max;i++)
    {
        pLetra=malloc(sizeof(eLetra));
        pLetra=al_get(letraRepetidas,i);
        for(j=0;j<2;j++){
            if(al_contains(letraRepetidas,pLetra)){
                contador++;
            }
        }
        if(contador!=2){
            al_remove(letraRepetidas,i);
            i--;
            max--;
        }
        contador=0;
    }
    al_sort(letraRepetidas,comparar,1);

    max=al_len(letraRepetidas);

     for(i=0;i<max;i++)
    {
        pLetra=malloc(sizeof(eLetra));
        pLetra=al_get(letraRepetidas,i);
        printf("%s\n",pLetra->nombre);
    }
    puts("\n\nLETRAS REPETIDAS\n");
    system("pause");
    system("cls");


    max=al_len(pList);
     for(i=0;i<max;i++)
    {
        pLetra=malloc(sizeof(eLetra));
        pLetra=al_get(letraSinRepetir,i);
        for(j=0;j<2;j++){
            if(al_contains(letraSinRepetir,pLetra)){
                contador++;
            }
        }
        if(contador==2){
            al_remove(letraSinRepetir,i);
            i--;
            max--;
        }
        contador=0;
    }
    al_sort(letraSinRepetir,comparar,1);

    max=al_len(letraSinRepetir);

     for(i=0;i<max;i++)
    {
        pLetra=malloc(sizeof(eLetra));
        pLetra=al_get(letraSinRepetir,i);
        printf("%s\n",pLetra->nombre);
    }

    puts("\n\nLETRAS SIN REPETIR\n");
    system("pause");

}

int comparar(void* letra1,void* letra2){
    eLetra *aux1=letra1;
    eLetra *aux2=letra2;

    if(aux1->letra < aux2->letra)
        return 1;
    else if(aux1->letra > aux2->letra)
        return 0;
}

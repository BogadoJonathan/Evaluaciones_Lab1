#include "defines.h"
#include "abonado.h"
#include "NuevaLlamada.h"
#include "reclamos.h"
#include "informar.h"

void IniciarValoresAbonado (eAbonado abonado[])
{
    int i;

    for(i=0;i<MAX;i++)
    {
        abonado[i].estado=0;
        abonado[i].CantReclamos=0;
    }

}

int BuscarVacio(eAbonado abonado[])
{
    int indice=-1;
    int i;

    for(i=0;i<MAX;i++)
    {
        if(abonado[i].estado==0)
        {
            indice=i;
            break;
        }
    }

    return indice;
}

int VerificacionTexto (char texto[],int desde, int hasta)
{
    int cantidad=strlen(texto);
    int retorno=0;
    int i;


    if (cantidad>=desde && cantidad<=hasta )
    {
        retorno=1;
            for (i=0;i<cantidad;i++)
            {

                   if(isdigit(texto[i]))
                    {
                        system("cls");
                        printf("No puede ingresar numero/s\n");
                        retorno=0;
                        break;
                    }
                }

    }
    else
    {
        system("cls");
        printf("Supero el limite de caracter permitido o no ingreso nada\n");
    }

    return retorno;
}

int VerificacionNumero (char mensaje [100], int desde, int hasta)
{
    int retorno=0;
    int i;
    char numero[500];
    int numeroverdadero;

    do
    {
    printf("%s ",mensaje);
    scanf ("%s",numero);
    int cantidad=strlen(numero);

        if (cantidad>=desde && cantidad<=hasta )
        {
            retorno=1;
                for (i=0;i<cantidad;i++)
                {
                    if(isalpha(numero[i]))
                    {

                        printf("No puede ingresar letras/s\n");
                        retorno=0;
                        break;
                    }
                }

        }
        else
        {
            printf("Supero el limite de numeros permitidos o no ingreso los numeros suficientes\n");
        }
    }while(retorno==0);
    numeroverdadero=atoi(numero);

    return numeroverdadero;

}

void IngresarNombreYApellido (eAbonado abonado [],int indice)
{
char validarTexto[500];

        system("cls");
        do
        {
            printf("Ingresa nombre: ");
            fflush(stdin);
            gets(validarTexto);
        }while(!(VerificacionTexto(validarTexto,1,35)));

        strcpy(abonado[indice].nombre,validarTexto);

        system("cls");
        do
        {
            printf("Ingresa apellido: ");
            fflush(stdin);
            gets(validarTexto);
        }while(!(VerificacionTexto(validarTexto,1,35)));

        strcpy(abonado[indice].apellido,validarTexto);
}

void AltaDeAbonado (eAbonado abonado[])
{
    int indice= BuscarVacio(abonado);

    if(indice==-1)
    {
        printf("No hay mas espacio.");
    }
    else
    {
        if (indice==0)
        {
            abonado[0].id=100;
        }
        else
        {
            abonado[indice].id=abonado[indice-1].id+1;
        }

        IngresarNombreYApellido(abonado,indice);

        system("cls");
        abonado[indice].numero=VerificacionNumero ("Ingresa numero telefonico",3,MaxTelefo);

        printf("Alta realizada con exito");

        abonado[indice].estado=1;
    }
}

void MostrarAbonados (eAbonado abonado[])
{
    int i;

    printf("ID\tNombre\t\t\tApellido\n");
    for(i=0;i<MAX;i++)
    {
        if (abonado[i].estado==1)
        {
            printf("%d\t%1s\t\t%5s\n",abonado[i].id,abonado[i].nombre,abonado[i].apellido);
        }
    }

}

int BuscarPorId (eAbonado abonado[], int id)
{
    int i;
    int retorno=-1;

    for (i=0;i<MAX;i++)
    {
        if(abonado[i].id==id && abonado[i].estado==1)
        {
            retorno=i;
            break;
        }
    }
    return retorno;
}

void ModificarAbonado (eAbonado abonado[])
{
    int id;
    int indice;
    int nodisponible=nohayabonado(abonado);

    if (nodisponible==1)
    {

    printf("Abonados disponibles: \n");
    MostrarAbonados(abonado);

    id=VerificacionNumero("Ingrese ID para modificar:",3,3);

    indice=BuscarPorId(abonado,id);

    if (indice==-1)
    {
        system("cls");
        printf("ID incorrecta.");
    }
    else
    {
       IngresarNombreYApellido(abonado,indice);

        system("cls");
        printf("MODIFICACION EXITOSA!");
    }

}
}

int nohayabonado (eAbonado abonado[])
{
    int i;
    int retorno=0;
    for(i=0;i<MAX;i++)
    {
            if(abonado[i].estado==1)
            {
                retorno=1;
                    break;
            }
    }
    if(retorno==0)
    {
        printf("No hay abonados registrados, deberas dar de alta por lo menos a uno\n\n");
    }

    return retorno;
}

void BajaDeAbonado (eAbonado abonado[])
{
    int id;
    int indice;
    int nodisponible=nohayabonado(abonado);

    if (nodisponible==1)
    {
    printf("Abonados disponibles: \n");
    MostrarAbonados(abonado);
    id=VerificacionNumero("Ingrese ID para dar de baja:",3,3);

    indice=BuscarPorId(abonado,id);

    if (indice==-1)
    {
        printf("ID incorrecta.");
    }
    else
    {
        printf("Abonado inhabilitado");
        abonado[indice].estado=-1;
    }

}
}

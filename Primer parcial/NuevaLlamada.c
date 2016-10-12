#include "defines.h"
#include "abonado.h"
#include "NuevaLlamada.h"
#include "reclamos.h"
#include "informar.h"

void IniciarValorLlamada (eLlamada llamada[])
{
    int i;
    for(i=0;i<MAX;i++)
    {
        llamada[i].estado=0;
        llamada[i].tiempo=0;
        llamada[i].estadollamado=-1;
    }
}


int LlamadaVacia(eLlamada llamada[])
{
    int i;
    int indice=-1;

    for (i=0;i<MAX;i++)
    {
        if (llamada[i].estado==0)
        {
            indice=i;
            break;
        }
    }
    return indice;

}

void NuevaLlamada (eLlamada llamada[],eAbonado abonado[],eReclamo reclamo[])
{
    int nodisponible=nohayabonado(abonado);

    if (nodisponible==1)
    {
        int id;
        int indiceLlamada=LlamadaVacia(llamada);
        int indiceAbonado;

        if (indiceLlamada==-1)
        {
            printf("Todos los telefenos estan ocupados");
        }
        else
        {
            printf("Abonados disponibles: \n");
            MostrarAbonados(abonado);
            id=VerificacionNumero("Ingrese ID:",3,3);

            indiceAbonado=BuscarPorId(abonado,id);

            if (indiceAbonado==-1)
            {
                printf("ID incorrecto");
            }
            else
            {
                int op;
                llamada[indiceLlamada].IdAbonado=id;
                llamada[indiceLlamada].estadollamado=EN_CURSO;

                op=OpcionesDeReclamo(reclamo);

                llamada[indiceLlamada].Motivo=op;

                abonado[indiceAbonado].CantReclamos++;

                reclamo[op-1].CantReclamos++;

                llamada[indiceLlamada].estado=1;

                printf("Llama procesada.");

            }
        }

    }

}

int LlamadasEnCurso (eLlamada llamadas[],eAbonado abonado[])
{
    int i;
    int indice;
    int op=-1;
    int flag=0;

    printf("LLAMADAS EN CURSO\n\n");
    printf("ID\tNombre y apellido\t\tEstado\t\tTiempo\n");

    for (i=0;i<MAX;i++)
    {
        if(llamadas[i].estadollamado==EN_CURSO)
        {
            indice=BuscarPorId(abonado,llamadas[i].IdAbonado);
            printf("%d\t%s %s\t\t%s\t\t%.2f\n",llamadas[i].IdAbonado,abonado[indice].nombre,abonado[indice].apellido,"En Curso",0.00);
            flag++;
        }
    }

    if (flag==0)
    {
        system("cls");
        printf("\nNo hay ninguna llamada en curso\n\n");

        op =0;
    }

    else
    {
        int verificacion;

        do
        {
            op=VerificacionNumero("Ingrese ID para finalizar llamada:",3,3);
            verificacion=BuscarPorId(abonado,op);
        }while(verificacion==-1 );
    }


    return op;
}

void FinLlamada (eLlamada llamadas[],eAbonado abonado[], eReclamo reclamo[])
{
   int id=LlamadasEnCurso(llamadas,abonado);
   int i;
   int indiceLlamada;
   int indiceReclamo;

   if (id==-1)
   {
       printf("ID incorrecta");
   }
   else
   {if(id!=0)
    {

       for (i=0;i<MAX;i++)
       {
           if(llamadas[i].IdAbonado==id)
           {
               indiceLlamada=i;
               break;
           }
       }


       llamadas[indiceLlamada].tiempo=(float)VerificacionNumero("Ingrese tiempo transcurido:",1,3);

       indiceReclamo=llamadas[indiceLlamada].Motivo-1;
       reclamo[indiceReclamo].tiempo+=llamadas[indiceLlamada].tiempo;

       int solucion;
       do{
       system("cls");
       printf("Indique estado: \n");
       printf("1 - SOLUCIONADO \n");
       printf("2 - NO SOLUCIONADO \n");
       printf("%f",llamadas[indiceLlamada].tiempo);
       solucion=VerificacionNumero("Ingrese opcion:",1,1);
       }while(solucion!=1 && solucion !=2);

       if (solucion==1)
       {
           llamadas[indiceLlamada].estadollamado=SOLUCIONADO;
       }
       else
       {
           llamadas[indiceLlamada].estadollamado=NO_SOLUCIONADO;
       }
         printf("Llamada finalizada");
    }
   }
}

#include "defines.h"
#include "abonado.h"
#include "NuevaLlamada.h"
#include "reclamos.h"
#include "informar.h"


void OPinformar (eAbonado abonado[],eLlamada llamada[],eReclamo reclamo[])
{
    int op;

    if(!llamada[0].estado)
    {
        printf("No hubo llamados\n");
    }

    if (nohayabonado(abonado) && llamada[0].estado)
    {
            printf("Seleccione lo que desee saber: \n");
            printf("1 - El nombre y apellido del abonado con mas reclamos\n");
            printf("2 - El reclamo mas realizado\n");
            printf("3 - El reclamo que mas demora en ser resulto (promedio)\n");
            scanf("%d",&op);

            switch (op)
            {
                case 1: ConMasReclamos(abonado);
                        break;
                case 2: ReclamoMasRealizado (reclamo);
                        break;
                case 3: ReclamoQueMasDemora (reclamo,llamada);
                        break;
                default: printf("Opcion incorrecta");
                            break;
            }

    }


}

void ConMasReclamos (eAbonado abonado[])
{
    int i;
    int mayor=abonado[0].CantReclamos;
    int id=abonado[0].id;
    int indice;


    for(i=1;i<MAX;i++)
    {
        if(abonado[i].CantReclamos>mayor)
        {
            mayor=abonado[i].CantReclamos;
            id=abonado[i].id;
        }
    }
    indice=BuscarPorId(abonado,id);


        printf("El abonado con mas reclamos es: %s %s, con %d reclamo(s)\n\n",abonado[indice].nombre,abonado[indice].apellido,mayor);

}

void ReclamoMasRealizado (eReclamo reclamo[])
{
    int i;
    int mayor=reclamo[0].CantReclamos;
    int id=reclamo[0].id;

    for(i=1;i<MAX_RECLAMO;i++)
    {
        if(reclamo[i].CantReclamos>mayor)
        {
            mayor=reclamo[i].CantReclamos;
            id=reclamo[i].id;
        }
    }

    printf("El reclamo mas realizado es: %s\n\n",reclamo[id-1].descripcion);
}

void ReclamoQueMasDemora (eReclamo reclamo[], eLlamada llamada[])
{
    int i;
    float promedio;
    float mayor;
    int indice;
    int verificacion=0;
    int flag=0;

    for(i=0;i<MAX;i++)
    {
        if(llamada[i].estadollamado==SOLUCIONADO || llamada[i].estadollamado==NO_SOLUCIONADO)
        {
            verificacion=1;
        }
    }

    if(verificacion)
    {
        for(i=0;i<MAX_RECLAMO;i++)
        {
            if(reclamo[i].CantReclamos==0)
            {
                continue;
            }
            promedio=reclamo[i].tiempo/reclamo[i].CantReclamos;
            if (!flag)
            {
                mayor=promedio;
                indice=reclamo[i].id-1;
                flag++;
            }
            else if (promedio>mayor)
            {
                mayor=promedio;
                indice=reclamo[i].id-1;
            }


        }

        printf("El reclamo que mas demora en ser resuelto es: %s, con un promedio de %2.f \n", reclamo[indice].descripcion, mayor);
    }
    else {
        printf("No se ha finalizado ninguna llamada");
    }
}

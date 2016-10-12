#include "defines.h"
#include "abonado.h"
#include "NuevaLlamada.h"
#include "reclamos.h"
#include "informar.h"

void IniciarValoresReclamo (eReclamo reclamo[])
{
    int i;

    for (i=0;i<MAX_RECLAMO;i++)
    {
        reclamo[i].CantReclamos=0;
        reclamo[i].tiempo=0;
    }

    strcpy(reclamo[0].descripcion,"Falla 3G");
    reclamo[0].id=FALLA_3G;

    strcpy(reclamo[1].descripcion,"Falla LTE");
    reclamo[1].id=FALLA_LTE;

    strcpy(reclamo[2].descripcion,"Falla Equipo");
    reclamo[2].id=FALLA_EQUPO;

}

int OpcionesDeReclamo (eReclamo reclamo[])
{
    int i;
    int op=-1;

    do
    {
    system("cls");
    printf("Ingrese opcion del reclamo: \n");
    for(i=0;i<MAX_RECLAMO;i++)
    {
        printf("%d - %s\n",reclamo[i].id,reclamo[i].descripcion);
    }
    op=VerificacionNumero("Ingrese opcion: ",1,1);
    }while(op<=0 || op>MAX_RECLAMO);

    return op;
}

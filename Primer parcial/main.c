#include "defines.h"
#include "abonado.h"
#include "NuevaLlamada.h"
#include "reclamos.h"
#include "informar.h"

int main()
{

 char seguir='s';

 eAbonado abonado[MAX];
 eLlamada llamada[MAX];
 eReclamo reclamo [MAX_RECLAMO];

 IniciarValoresReclamo(reclamo);
 IniciarValorLlamada(llamada);
 IniciarValoresAbonado(abonado);


    do
    {
        switch (menu())
        {
        case 1:
                system("cls");
                AltaDeAbonado (abonado);
                system("pause");
                break;

        case 2:
                system("cls");
                ModificarAbonado(abonado);
                system("pause");
                break;
        case 3:
                system("cls");
                BajaDeAbonado(abonado);
                system("pause");
                break;
        case 4:
                system("cls");
                NuevaLlamada(llamada,abonado,reclamo);
                system("pause");
                break;
        case 5:
                FinLlamada(llamada,abonado,reclamo);
                system("pause");
                break;
        case 6:
                system("cls");
                OPinformar(abonado,llamada,reclamo);
                system("pause");
                break;

        case 7:
            seguir='n';
            break;
        default:
            printf("Opcion incorrecta\n\n");
            system("pause");
            break;
        }
    }while (seguir == 's');

    return 0;
}

int menu()
{
    int opcion;
    system("cls");

    printf("*****MENU*****\n\n");
    printf("1 - Alta de abonado\n");
    printf("2 - Modificar datos del abonado\n");
    printf("3 - Baja de abonado\n");
    printf("4 - Nueva llamada\n");
    printf("5 - Fin de la llamada\n");
    printf("6 - Informar.\n");
    printf("7 - Salir\n");
    opcion=VerificacionNumero("Ingrese opcion:",1,1);

    return opcion;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ArrayList.h"
#include "letra.h"

int main()
{
    int verificador=0;
    ArrayList *letra=al_newArrayList();
    ArrayList *letrasRepetidas=al_newArrayList();
    ArrayList *letraSinRepetir=al_newArrayList();

while(1)
    {
        switch(menu())
        {
        case 1:

            if(verificador==0){
                darDeAlta(letra);
                verificador=1;
            }
            else{
                printf("\nLa carga ya fue realizada anteriormente.\n");
                system("pause");
            }
            break;
        case 2:
            completar(letra);
            break;
        case 3:
            comprobar(letra);
            system("pause");
            break;
        case 4:
            generarYListas (letrasRepetidas,letraSinRepetir,letra);
            break;
        case 5:
            exit(1);
            break;
        default: printf("Opcion incorrecto");
            break;
        }
        system("cls");
    }

    return 0;
}


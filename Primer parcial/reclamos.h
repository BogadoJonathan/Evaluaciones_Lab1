#ifndef RECLAMOS_H
#define RECLAMOS_H

#define FALLA_3G 1
#define FALLA_LTE 2
#define FALLA_EQUPO 3

#define MAX_RECLAMO 3

typedef struct
{
    int id;
    char descripcion [20];
    float CantReclamos;
    float tiempo;
}eReclamo;

/**
* \brief Inicia los valores de la estructura eReclamo
* \param pone CantReclamos y tiempo en 0
* \return void
*
*/
void IniciarValoresReclamo (eReclamo reclamo[]);

/**
* \brief Muestra por pantalla las opciones de reclamo disponible
* \param el usuario ingresa la opcion
* \return devuelve la opcion seleccionada por el usuario
*
*/
int OpcionesDeReclamo (eReclamo reclamo[]);

/**
* \brief Inicia una nueva llamada
* \param recibe una eLlamada vacia, y pone su estado de llamada en CURSO y se le agregan los datos dados por el usuario
* \return void
*
*/
void NuevaLlamada (eLlamada llamada[],eAbonado abonado[],eReclamo reclamo[]);

/**
* \brief Finaliza una llamada
* \param al finalizar agrega su tiempo, y si se ha solucionado
* \return void
*
*/
void FinLlamada (eLlamada llamadas[],eAbonado abonado[], eReclamo reclamo[]);

#endif // RECLAMOS_H

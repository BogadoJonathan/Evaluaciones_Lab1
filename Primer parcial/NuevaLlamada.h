#ifndef NUEVALLAMADA_H
#define NUEVALLAMADA_H

#define EN_CURSO 0
#define SOLUCIONADO 1
#define NO_SOLUCIONADO 2

typedef struct
{
    unsigned short int IdAbonado;
    short int Motivo;
    short int estado;
    short int estadollamado;
    float tiempo;
}eLlamada;

/**
* \brief Inicia los valores de la estructura eLlamada
* \param pone al estado y al tiempo en 0, y estado de llamada en -1
* \return void
*
*/
void IniciarValorLlamada (eLlamada llamada[]);

/**
* \brief Busca una eLlamada vacia para agregarle valores
* \param recorre la estructura en busca del estado 0
* \return indice del estado en 0
*
*/
int LlamadaVacia(eLlamada llamada[]);

/**
* \brief Bmuestra las llamadas que estan en curso
* \param se ingresa la ID de la llamada en curso
* \return devuelve id seleccionada por el usuario
*
*/
int LlamadasEnCurso (eLlamada llamadas[],eAbonado abonado[]);


#endif // NUEVALLAMADA_H

#ifndef INFORMAR_H
#define INFORMAR_H

/**
* \brief Muestra las opciones de INFORMAR
* \param pide al usuario que ingrese numero de opcion
* \return void
*
*/
void OPinformar (eAbonado abonado[],eLlamada llamada[],eReclamo reclamo[]);

/**
* \brief Muestra nombre y apellido del abonado con mas reclamos
* \param verifica entre las variable CantReclamos de todos los abonados cual es el que mas reclamos hizo
* \return void
*
*/
void ConMasReclamos (eAbonado abonado[]);

/**
* \brief muestra cual es el reclamo mas realizado
* \param recorre todo el array en busca del CantReclamos mas mayor, informando cual es
* \return void
*
*/
void ReclamoMasRealizado (eReclamo reclamo[]);

/**
* \brief Promedia el tiempo de los reclamos, mostrando el mayor
* \param promedia el tiempo por la cantidad de reclamos de cada eReclamo, verificando cual es el mayor
* \return void
*
*/
void ReclamoQueMasDemora (eReclamo reclamo[], eLlamada llamada[]);


#endif // INFORMAR_H

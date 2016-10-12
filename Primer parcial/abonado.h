#ifndef ABONADO_H
#define ABONADO_H

#define MaxTelefo 10

typedef struct
{
    unsigned short int id;//[0 , 65535]
    unsigned int numero; //[0 , 4294967295]
    char nombre [36];
    char apellido [36];
    int estado;
    unsigned short int CantReclamos;
}eAbonado;

/**
* \brief inicia valores de eAbonado
* \param pone su estado y CantDeReclamos en 0
* \return void
*
*/
void IniciarValoresAbonado (eAbonado abonado[]);

/**
* \brief Busca eAbonado con estado en 0
* \param Recorre toda el array de estructura para encontrar una disponible para ser modificada
* \return devuelve indice del array vacio
*
*/
int BuscarVacio(eAbonado abonado[]);

/**
* \brief Da de alta un abonado agregandole sus datos
* \param se pediran los datos necesario para la alta del nuevo abonado, se le asignara una ID incremental
* \return void
*
*/
void AltaDeAbonado (eAbonado abonado[]);

/**
* \brief Muestra los abonados disponibles
* \param Busca en el array de estructura los estados en 1 para luego ser mostrados
* \return void
*
*/
void MostrarAbonados (eAbonado abonado[]);

/**
* \brief Busca la ID que ingreso el usuario
* \param recibe una ID para luego buscarla por todo el array de estrutura
* \return devuelve el indice donde se encuentra el ID, de lo contrario devuelve -1
*
*/
int BuscarPorId (eAbonado abonado[], int id);

/**
* \brief Modifica nombre y apellido de un abonado
* \param recibe el indice donde se encuentra la ID a modificar, y se le modifica nombre y apellido
* \return void
*
*/
void ModificarAbonado (eAbonado abonado[]);

/**
* \brief Da de baja a un abonado
* \param pone en -1 el estado del abonado seleccionado por el usuario
* \return void
*
*/
void BajaDeAbonado (eAbonado abonado[]);

/**
* \brief Verifica si se creo un abonado
* \param Si no se creo bloqueara el acceso a algunas opciones
* \return devuelve 1 si hay abonado ya creado, 0 si no hay
*
*/
int nohayabonado (eAbonado abonado[]);

/**
* \brief ingresa nombre y apellido
* \param ingresa nombre y apellido del abonado
* \return void
*
*/
void IngresarNombreYApellido (eAbonado abonado [],int indice);

/**
* \brief Verifica el ingreso, que sea TEXTO
* \param verifica si no supera su limite y que el usuario no ingrese numero
* \return 0 si no cumple con lo indicado, de lo contrario devuelve 1 si ingreso bien
*
*/
int VerificacionTexto (char texto[],int desde, int hasta);

/**
* \brief Verifica el ingreso, que sea solo NUMEROS
* \param pide un numero, que se transformara en char, para luego ser verificado su limite, y que este no ingrese caracteres
* \return devuelve el numero ingresado por el usuario
*
*/
int VerificacionNumero (char mensaje [100], int desde, int hasta);


#endif // ABONADO_H

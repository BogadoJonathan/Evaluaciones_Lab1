#ifndef LETRA_H_INCLUDED
#define LETRA_H_INCLUDED

typedef struct{
char letra;
char nombre[21];
int vocal;
int consonante;
}eLetra;

/**
 * Ingreso de numero y verifica que lo que ingreso este correcto
 * @param un mensaje para que el usuario sepa que ingresar
 * @param un digito minimo que debe ingresar el usuario
 * @param un digita maximo que debe ingresar el usuario
 * @return devuelve el numero ingresado
 */
int ingresarNumero(char mensaje[100], int minimo, int maximo);
/**
 * Muestra mensaje, e ingresa texto y verifica que lo que ingreso este correcto
 * @param un mensaje para que el usuario
 * @param donde se guardara el dato
 * @param caracteres minimos
 * @param caracteres max
 * @param permitir o no numeros
 * @return void
 */
void ingresarTexto(char mensaje[100],char *Destino,int desde, int hasta,char ingresarNumeros);
/**
 * Muestra menu e ingresa opcion
 * @param void
 * @return opcion ingresada
 */
int menu (void);
/**
 * Carga todos los datos del archivo al programa
 * @param pList para guardar todo ahi
 * @return void
 */
void darDeAlta(ArrayList *pLista);
/**
 * Rellenar campos de vocal y consonante
 * @param pList recopilar los datos
 * @return void
 */
void completar(ArrayList *pList);
/**
 * El usuario ingresa palabra por teclado, y comprueba si hay letras existentes
 * @param pList para recopilar los datos
 * @return void
 */
void comprobar(ArrayList *pList);
/**
 * Genera 2 listas, ordenadas, una con letras repetidas y otra sin repetir
 * @param letrarepetidas para guardar todo ahi
 * @param letrassinrepetir para guardar todo ahi
 * @param pList recopilar datos
 * @return void
 */
void generarYListas (ArrayList *letraRepetidas, ArrayList *letraSinRepetir, ArrayList *pList);
/**
 * Para la funcion al_sort
 * @param letra1
 * @param letra1
 * @return devuelve 1 o 0
 */
int comparar(void* letra1,void* letra2);

#endif // LETRA_H_INCLUDED

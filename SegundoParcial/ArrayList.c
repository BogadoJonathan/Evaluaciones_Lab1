#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#include "letra.h"

// funciones privadas
int resizeUp(ArrayList* this);
int expand(ArrayList* this,int index);
int contract(ArrayList* this,int index);

#define AL_INCREMENT      10
#define AL_INITIAL_VALUE  10
//___________________

/** \brief Allocate a new arrayList with AL_INITIAL_VALUE elements.
 * \param void
 * \return ArrayList* Return (NULL) if Error [if can't allocate memory]
 *                  - (pointer to new arrayList) if ok
 */
ArrayList* al_newArrayList(void)  //CREA ARRAYLIST
{
    ArrayList* this;
    ArrayList* returnAux = NULL;
    void* pElements;
    this = (ArrayList *)malloc(sizeof(ArrayList));

    if(this != NULL)
    {
        pElements = malloc(sizeof(void *)*AL_INITIAL_VALUE );
        if(pElements != NULL)
        {
            this->size=0;
            this->pElements=pElements;
            this->reservedSize=AL_INITIAL_VALUE;
            this->add=al_add;
            this->len=al_len;
            this->set=al_set;
            this->remove=al_remove;
            this->clear=al_clear;
            this->clone=al_clone;
            this->get=al_get;
            this->contains=al_contains;
            this->push=al_push;
            this->indexOf=al_indexOf;
            this->isEmpty=al_isEmpty;
            this->pop=al_pop;
            this->subList=al_subList;
            this->containsAll=al_containsAll;
            this->deleteArrayList = al_deleteArrayList;
            this->sort = al_sort;
            returnAux = this;
        }
        else
        {
            free(this);
        }
    }

    return returnAux;
}


/** \brief  Add an element to arrayList and if is
 *          nessesary resize the array
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (0) if Ok
 *
 */
int al_add(ArrayList* pList, void* pElement) //AGREGA ELEMENTO
{
    int returnAux = -1;

    if(pElement!=NULL && pList != NULL && !resizeUp(pList))
    {
        pList->pElements[pList->size]= pElement;
        pList->size ++;
        returnAux = 0;
    }

    return returnAux;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Ok
 *
 */
int al_deleteArrayList(ArrayList* this) //ELIMINA LISTA
{
    int returnAux = -1;

    if (this!=NULL)
    {
       /* if(this->size>0)
            returnAux=0;
        else
            returnAux=1;*/ //50% de efectividad
        returnAux=0;
        free(this->pElements);
        free(this);
    }
    return returnAux;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return length of array or (-1) if Error [pList is NULL pointer]
 *
 */
int al_len(ArrayList* this) //RETORNA LA CANTIDAD DE ELEMENTOS
{
    int returnAux = -1;
    if(this!=NULL)
        returnAux=this->size;

    return returnAux;
}

/** \brief  Get an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return void* Return (NULL) if Error [pList is NULL pointer or invalid index] - (Pointer to element) if Ok
 *
 */
void* al_get(ArrayList* this, int index)//RETORNA ELEMENTO EN EL INDICE INDICADO
{
    void* returnAux = NULL;
    if(this!=NULL && index>=0 && index < this->size)
        returnAux = this->pElements[index];

    return returnAux;
}

/** \brief  Find if pList contains at least one element pElement
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer]
 *                  - ( 0) if Ok but not found a element
 *                  - ( 1) if this list contains at least one element pElement
 *
 */
int al_contains(ArrayList* this, void* pElement)//RETORNA EL INDICE DONDE SE ENCUENTRA EL ELEMENTO (BUSCADOR)
{
    int returnAux = -1,i;
    if(this!=NULL && pElement!=NULL)
    {
        returnAux = 0;
        for(i=0;i<this->size;i++)
        {
            if(al_get(this,i)==pElement)
            {
                returnAux = 1;
                break;
            }
        }
    }
    return returnAux;
}

/** \brief  Set a element in pList at index position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 *
 */
int al_set(ArrayList* this, int index,void* pElement)//MODIFICAR ELEMENTO
{
    int returnAux=-1;
    if(this!=NULL && pElement!=NULL && index>=0 && this->size>index)
    {
        returnAux = 0;
        this->pElements[index]=pElement;
    }
    return returnAux;
}

/** \brief  Remove an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_remove(ArrayList* this,int index)//ELIMINA EL ELEMENTO ESPECIFICO
{
   int returnAux = -1;
    if(this!=NULL && index>=0 && index<this->size)
    {
        if(contract(this,index)!=-1)
            returnAux = 0;
    }
    return returnAux;
}

/** \brief Removes all of the elements from this list
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer]
 *                  - ( 0) if Ok
 */
int al_clear(ArrayList* this)//BORRA TODOS LOS ELEMENTOS DEL ARRAYLIST
{
    int returnAux=-1,i;
    if(this!=NULL)
    {
		for(i=0; i<this->size; i++)
			free(this->pElements[i]);

		this->size=0;
		if(resizeDown(this)==0)
            returnAux=0;
    }
    return returnAux;
}

/** \brief Returns an array containing all of the elements in this list in proper sequence
 * \param pList ArrayList* Pointer to arrayList
 * \return ArrayList* Return  (NULL) if Error [pList is NULL pointer]
 *                          - (New array) if Ok
 */
ArrayList* al_clone(ArrayList* this)//COPIA UN ARRAYLIST
{
    ArrayList* returnAux=NULL;
    if(this!=NULL)
    {
        returnAux=al_newArrayList();
         if(returnAux!=NULL)
        {
            returnAux=this;
			/*for(i=0; i< this->size; i++){
            al_add(returnAux, this->pElements[i]);
           }*/
        }
    }
    return returnAux;
}




/** \brief Inserts the element at the specified position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_push(ArrayList* this, int index, void* pElement)//inserta un elemento en un indice especifico, corriendo a los otros
{
    int returnAux = -1;

    if(this!=NULL && pElement!=NULL && index>=0 && index<=this->size)
    {
		this->size++;
		resizeUp(this);
        expand(this,index);
        returnAux=0;
        al_set(this,index,pElement);
    }
    return returnAux;
}

/** \brief Returns the index of the first occurrence of the specified element
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (index to element) if Ok
 */
int al_indexOf(ArrayList* this, void* pElement)//retorna el indice de los elementos
{
    int returnAux = -1,i;
    if(this!=NULL && pElement!=NULL)
    {
        for(i=0;i<this->size;i++)
        {
            if(pElement==this->pElements[i])
                returnAux = i;
        }
    }
    return returnAux;
}



/** \brief Returns true if this list contains no elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Not Empty - (1) if is Empty
 */
int al_isEmpty(ArrayList* this)//RETORNA 0 SI HAY ELEMENTOS, DE LO CONTRARIO 1.
{
    int returnAux = -1;
    if(this!=NULL)
    {
        returnAux = 1;
        if(this->size > 0)
        {
            returnAux = 0;
        }
    }
    return returnAux ;
}




/** \brief Remove the item at the given position in the list, and return it.
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid index]
 *                  - ( element pointer) if Ok
 */
void* al_pop(ArrayList* this,int index)//RETORNA EL ELEMENTOS Y LUEGO LO ELIMINA
{
    void* returnAux = NULL;

    if(this!=NULL && index>=0 && index<this->size)
    {
        returnAux=this->pElements[index];
        contract(this,index);
    }

    return returnAux;
}


/** \brief Returns a new arrayList with a portion of pList between the specified
 *         fromIndex, inclusive, and toIndex, exclusive.
 * \param pList ArrayList* Pointer to arrayList
 * \param from int Initial index of the element (inclusive)
 * \param to int Final index of the element (exclusive)
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid 'from' or invalid 'to']
 *                  - ( pointer to new array) if Ok
 */
ArrayList* al_subList(ArrayList* this,int from,int to)//CREA UN NUEVO ARRAYLIST CON UN CONJUNTO ESPECIFICO DE ELEMENTOS
{

    ArrayList* returnAux = NULL;
    int i;

    if(this!=NULL && from>=0 && from<to &&  to<=this->size)
    {
        returnAux=al_newArrayList();
        if(returnAux!=NULL)
        {
            for(i=from;i<to;i++)
               al_add(returnAux,al_get(this,i));
        }
    }
    return returnAux ;
}

/** \brief Returns true if pList list contains all of the elements of pList2
 * \param pList ArrayList* Pointer to arrayList
 * \param pList2 ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList or pList2 are NULL pointer]
 *                  - (0) if Not contains All - (1) if is contains All
 */
int al_containsAll(ArrayList* this,ArrayList* this2)//COMPARA 2 ARRAYLIST, RETORNA 1 SI SON IGUALES DE LO CONTRARIO 0
{
    int returnAux = -1,i;
    if(this!=NULL && this2!= NULL)
    {
            returnAux = 1;
            for(i=0;i<this->size;i++)
            {
                if((this->pElements[i] != this2->pElements[i]))
                {
                    returnAux = 0;
                    break;
                }
            }
    }
    return returnAux;
}

/** \brief Sorts objects of list, use compare pFunc
 * \param pList ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [pList or pFunc are NULL pointer]
 *                  - (0) if ok
 */
int al_sort(ArrayList* this, int (*pFunc)(void* ,void*), int order)//ORDENA DE MAYOR A MENOR SEGUN EL USUARIO
{
    int returnAux = -1,i,j;
    void* pAux;
    if(this!=NULL && pFunc!=NULL && (order == 0 || order == 1))
    {
        for(i=0;i-1<this->size;i++)
        {
            for(j=i+1;j<this->size;j++)
            {
                if((pFunc(this->pElements[i],this->pElements[j])==1 && order== 1) || (pFunc(this->pElements[i],this->pElements[j])==-1 && order== 0))
                {
                    pAux = this->pElements[i];
                    this->pElements[i] = this->pElements[j];
                    this->pElements[j] = pAux;
                }
                returnAux = 0;
            }
        }
    }

    return returnAux;
}


/** \brief Increment the number of elements in pList in AL_INCREMENT elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
int resizeUp(ArrayList* this)//INCREMENTA PELEMENTS
{
   int returnAux = -1;
    void** pAux;

    if(this!=NULL)
    {
        if(this->size==this->reservedSize)
        {
            pAux=(void**)realloc(this->pElements, sizeof(void*)*(this->reservedSize+AL_INCREMENT));
            if(pAux!=NULL)
            {
                this->pElements = pAux;
                this->reservedSize = this->reservedSize + AL_INCREMENT;
            }
        }
        returnAux = 0;
    }

    return returnAux;
}

/** \brief  Expand an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int expand(ArrayList* this,int index)//EXPANDE
{
    int returnAux = -1,i;
    if(this != NULL && index >= 0 && index < this->size)
    {
        for(i=this->size;i>index;i--)
            *(this->pElements+(i+1)) = *(this->pElements+i);

		returnAux = 0;
    }
    return returnAux;
}

/** \brief  Contract an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int contract(ArrayList* this,int index)//CONTRAE
{
   int returnAux = -1;
    int i;
    if (this != NULL && index <= this->size && index >-1)
    {
        for (i=index; i<this->size-1; i++)
            *(this->pElements+i) = *(this->pElements+(i+1));
        this->size--;
        returnAux = 0;
        if (this->reservedSize>this->size+AL_INCREMENT)
        {
            if (resizeDown(this) != 0)
                returnAux = -1;
        }
    }

    return returnAux;
}


int resizeDown(ArrayList* this)
{
    int returnAux = -1;
    void** lista;
    if (this != NULL)
    {
        lista = (void**) realloc(this->pElements,sizeof(void*)*(this->size+AL_INCREMENT));
        if (lista!=NULL)
        {
            this->reservedSize=this->size+AL_INCREMENT;
            this->pElements=lista;
            returnAux = 0;
        }
    }
    return returnAux;
}

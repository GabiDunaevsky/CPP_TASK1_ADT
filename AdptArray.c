#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include "AdptArray.h"
#include "Person.h"

/*
For this code i was using th presantation from the last course in c (practice 11)
I was also serching some information using chat gpt for the malloc and calloc.
*/


// I took this struct from the presentation and changed it a little bit.
typedef struct AdptArray_{
    PElement* ArrElements;
    int iNum;
    /* Function Pointers */
    DEL_FUNC DelElementFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC PrintElementFunc;
    

}AdptArray_;

// I took this function from the presentation and changed it a little bit.
PAdptArray CreateAdptArray(COPY_FUNC copyFunc , DEL_FUNC DelElementFunc,PRINT_FUNC PrintElementFunc)
{
    PAdptArray pDA =(PAdptArray) malloc(sizeof(AdptArray_));
    if(pDA == NULL){
        return NULL;
    }
    pDA->ArrElements = (PElement*)malloc(sizeof(PElement)); // initalizing the array to size 0 at the biggining.
    pDA->iNum = 0;
    pDA->DelElementFunc = DelElementFunc;
    pDA->copyFunc = copyFunc;
    pDA->PrintElementFunc = PrintElementFunc;
return pDA;
}
// I took this function from the presentation and changed it a little bit.
void DeleteAdptArray(PAdptArray pDA){
    for (int i = 0; i < pDA->iNum; i++)
    {
        if (pDA->ArrElements[i])
        pDA->DelElementFunc(pDA->ArrElements[i]);
    }
    pDA->iNum = 0;
     free(pDA->ArrElements);
    free(pDA);
}
// We  have 3 options here, if the array or the struct dosnt exist i returned null, if the index smaller than the number of elements i just delete element index and puting the new one.
// The third case is when the indx is bigger than the array so i do calloc on the new size and then moving all the ekements and puting it as the new arr elements.
Result SetAdptArrayAt(PAdptArray pDA, int indx, PElement pelem){
    if (NULL == pDA || NULL == pelem || indx < 0){
        return FAIL;
    }
    else if(pDA->iNum <= indx){
        int tmp = pDA->iNum;
        // pDA->ArrElements = (PElement*) realloc(pDA->ArrElements,sizeof(PElement) * (indx + 1));
        pDA->iNum = indx+1;
         PElement* arr = (PElement)calloc(indx + 1, sizeof(PElement));
         for (int i = 0; i < tmp; i++)
        {
            if (pDA->ArrElements[i]) {
                arr[i] = pDA->ArrElements[i];
                }
        }
        arr[indx] = pDA->copyFunc(pelem);
        free(pDA->ArrElements); 
        pDA->ArrElements = arr;
        
    }else{
        pDA->DelElementFunc(pDA->ArrElements[indx]);
        pDA->ArrElements[indx] = pDA->copyFunc(pelem);
    }
    return SUCCESS;
}
//Returning a copy of the element in the requierd location and if the array is null or the struct or the value i return null.
PElement GetAdptArrayAt(PAdptArray pDA, int indx){
    if (NULL == pDA || pDA->iNum <= indx || pDA->ArrElements[indx] == NULL){
        return NULL;
    }
    return pDA->copyFunc(pDA->ArrElements[indx]);
}
//Just returning the number of elements of the array if he exist.
int GetAdptArraySize(PAdptArray pDA){
    if (NULL == pDA || NULL == pDA->ArrElements)
    {
        return -1;
    }
    return pDA->iNum;
}
//  I took this function from the presentation of the practice, just printing each elememt from the array using printelementfunc.
void PrintDB(PAdptArray pDA){
    for (int i = 0; i < pDA->iNum; i++)
    {
        if (pDA->ArrElements[i])
        pDA->PrintElementFunc(pDA->ArrElements[i]);
    }
}
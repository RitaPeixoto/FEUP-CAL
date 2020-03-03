/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n)//alinea a
{
	if(n==1 | n==0){
	    return 1;
	}
	else{
	    return n*factorialRecurs(n-1);
	}
}

int factorialDinam(int n)//alinea b
{
    int i =1, res=1;
    while(i<n){
        i++;
        res*=i;
    }
	return res;
}
/*
 * Alinea c
 * Em termos temporais são ambas lineares.
 * Em termos espaciais a implementação recursiva ocupa mais espaço pois guarda todas as chamadas da função enquanto nao a "arruma"
 * */

/*
 * Change.h
 */

#ifndef CHANGE_H_
#define CHANGE_H_

#include <string>
#include<vector>
using namespace std;

/* Calcula o troco num determinado montante m, utilizando um n�mero m�nimo
 * de moedas de valores unit�rios indicados (coinValues).
 * O array coinValues deve estar ordenado por ordem crescente.
 * O par�metro numCoins indica o tamanho do array.
 * Devolve:
 * Uma string com a sequ�ncia de valores das moedas por valores decrescente.
 * Por exemplo: calcChange(9, 3, {1, 2, 5}) = "5;2;2;"
 * */
string calcChange(int m, int numCoins, int *coinValues);
int minCoins(int i, int k, int *coinValues);
int lastCoin(int i, int k , int *coinValues);

#endif /* CHANGE_H_ */

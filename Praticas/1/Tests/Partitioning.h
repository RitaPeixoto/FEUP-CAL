/*
 * Partioning.h
 */

#ifndef PARTITIONING_H_
#define PARTITIONING_H_
#include <vector>
using namespace std;

/*Implementa a fun��o s(n,k) usando recursividade*/
int s_recursive(int n,int k);

/*Implementa a fun��o b(n) usando recursividade*/
int b_recursive(int n);

/*Implementa a fun��o s(n,k) usando programa��o din�mica*/
int s_dynamic(int n,int k);

/*Implementa a fun��o b(n) usando programa��o din�mica*/
int b_dynamic(int n);

#endif /* SUM_H_ */

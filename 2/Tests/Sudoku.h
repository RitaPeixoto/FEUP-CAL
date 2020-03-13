/*
 * Sudoku.h
 *
 */

#ifndef SUDOKU_H_
#define SUDOKU_H_

#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define IllegalArgumentException -1

class Sudoku
{
	/**
	 * numbers[i][j] - n�mero que ocupa a linha i, coluna j (de 0 a 8)
	 * 0 quer dizer n�o preenchido.
	 */
	int numbers[9][9];

	/**
	 * Informa��o derivada da anterior, para acelerar processamento (n�mero de 1 a 9, nao usa 0)
	 */
	int countFilled;
	bool columnHasNumber[9][10];
	bool lineHasNumber[9][10];
	bool block3x3HasNumber[3][3][10];
	int sol;
	int init;

	void initialize();

public:
	/** Inicia um Sudoku vazio.
	 */
	Sudoku();

	/**
	 * Inicia um Sudoku com um conte�do inicial.
	 * Lan�a excep��o IllegalArgumentException se os valores
	 * estiverem fora da gama de 1 a 9 ou se existirem n�meros repetidos
	 * por linha, coluna ou bloc 3x3.
	 *
	 * @param nums matriz com os valores iniciais (0 significa por preencher)
	 */
	Sudoku(int nums[9][9]);

	/**
	 * Obtem o conte�do actual (s� para leitura!).
	 */
	int** getNumbers();


	/**
	 * Verifica se o Sudoku j� est� completamente resolvido
	 */
	bool isComplete();


	/**
	 * Resolve o Sudoku.
	 * Retorna indica��o de sucesso ou insucesso (sudoku imposs�vel).
	 */
	bool solve();
    bool solve2();
    bool Possible(int row, int col, int n);

	/**
	 * Imprime o Sudoku.
	 */
	void print();
};

#endif /* SUDOKU_H_ */

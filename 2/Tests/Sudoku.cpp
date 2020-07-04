/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku()
{
	this->initialize();
}

/**
 * Inicia um Sudoku com um conte�do inicial.
 * Lan�a excep��o IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem n�meros repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9])
{
	this->initialize();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (nums[i][j] != 0)
			{
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
				init++;
			}
		}
	}
}

void Sudoku::initialize()
{
    sol =0;
    init =0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int n = 0; n < 10; n++)
			{
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtem o conte�do actual (s� para leitura!).
 */
int** Sudoku::getNumbers()
{
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++)
	{
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku j� est� completamente resolvido
 */
bool Sudoku::isComplete()
{
	return countFilled == 9 * 9;
}



/**
 * Resolve o Sudoku.
 * Retorna indica��o de sucesso ou insucesso (sudoku imposs�vel).
 */
bool Sudoku::solve(){
    if(isComplete())
        return true;
    for(int i=0; i<9;i++){
        for(int j=0; j<9;j++){
            if(numbers[i][j]==0){
                for(int n=1; n<=9; n++){
                    if(Possible(i,j,n)){
                        numbers[i][j]=n;
                        countFilled++;
                        columnHasNumber[j][n] = true;
                        lineHasNumber[i][n] =true;
                        block3x3HasNumber[i/3][j/3][n]=true;

                        if(solve())
                            return true;
                        else{
                            numbers[i][j]=0;
                            countFilled--;
                            columnHasNumber[j][n] = false;
                            lineHasNumber[i][n] = false;
                            block3x3HasNumber[i/3][j/3][n] = false;
                        }
                    }
                }
                return false;
            }
        }
    }
    return isComplete();
}

bool Sudoku::solve2(){
    if(isComplete()){
        sol ++;
        return true;
    }

    for(int i=0; i<9;i++){
        for(int j=0; j<9;j++){
            if(numbers[i][j]==0){
                for(int n=1; n<=9; n++){
                    if(Possible(i,j,n)){
                        numbers[i][j]=n;
                        countFilled++;
                        columnHasNumber[j][n] = true;
                        lineHasNumber[i][n] =true;
                        block3x3HasNumber[i/3][j/3][n]=true;

                        solve2();
                        numbers[i][j]=0;
                        countFilled--;
                        columnHasNumber[j][n] = false;
                        lineHasNumber[i][n] = false;
                        block3x3HasNumber[i/3][j/3][n] = false;
                        }
                    }
                if(countFilled == init){
                    cout << "Number of solutions: "<<sol<<endl;
                    return sol>0;
                }
                else
                  return false;
            }
        }
    }
    return true;
}



bool Sudoku::Possible(int row, int col, int n){
    return !lineHasNumber[row][n] && !columnHasNumber[col][n] && !block3x3HasNumber[row/3][col/3][n];
}

/**
 * Imprime o Sudoku.
 */
void Sudoku::print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";
		cout << endl;
	}
}

/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}

//alinea a
bool Labirinth::findGoal(int x, int y)
{
    static bool initialized = false;
    if(!initialized){
        initializeVisited();
        initialized=true;
    }
    bool found=false;
    visited[x][y]= true;
    if(labirinth[x][y]==2){//exit
        return true;
    }
    if(labirinth[x][y]==0){//wall
        return false;
    }
    for(int i=0; i<4;i++){
        switch(i){
            case 0://left
                if((x-1)>=0){
                    if(!visited[x-1][y]){
                        found = findGoal(x-1,y);
                        if(found){
                            return true;
                        }
                    }
                }
                break;
            case 1://right
                if((x+1)<10){
                    if(!visited[x+1][y]){
                        found = findGoal(x+1,y);
                        if(found){
                            return true;
                        }
                    }
                }
                break;


            case 2://up
                if((y+1)<10){
                    if(!visited[x][y+1]){
                        found = findGoal(x,y+1);
                        if(found){
                            return true;
                        }
                    }
                }
                break;

            case 3://down
                if((y-1)>=0 ){
                    if(!visited[x][y-1]){
                        found = findGoal(x,y-1);
                        if(found){
                            return true;
                        }
                    }

                }
                break;
        }
    }
    visited[x][y]=true;
	return false;
}
/*
T(n)=O(n2) no pior caso, em que n é dimensão do labirinto (neste caso n=10), pois cada célula só
é visitada no máximo uma vez.

 */

//outra resoluçao do find goal
/*bool Labirinth::findGoal(int x, int y)
{
initializeVisited();
return findGoalRec(x,y);
}
// Auxiliary recursive function
bool Labirinth::findGoalRec(int x, int y)
{
// Check if this position is worth visiting (limits checking could
// be omitted because the labyrinth is surrounded by walls)
if (x < 0 || y < 0 || x >= 10 || x >= 10
|| labirinth[y][x] == 0 || visited[y][x])
return false;
// Mark as visited
visited[y][x] = true;
// Check if the exit was reached
if (labirinth[y][x] == 2) {
cout << ": Reached the goal!" << endl;
return true;
}
// Try all the adjacent cells
return findGoalRec(x-1, y) || findGoalRec(x+1, y)
|| findGoalRec(x, y-1) || findGoalRec(x, y+1);
}

 */
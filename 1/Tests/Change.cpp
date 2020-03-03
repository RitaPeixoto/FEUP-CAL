/*
 * Change.cpp
 */

#include "Change.h"

string calcChange(int m, int numCoins, int *coinValues)
{
    string res;
    if(numCoins==0 || m==0){//if there are no coins or the change is 0
        return "";
    }
    if(minCoins(numCoins-1,m,coinValues)==0){//if it's not possible to obtain the change
        return "-";
    }
    // Compute all the needed coins to make change for the 'm' value
    int coin = lastCoin(numCoins-1,m,coinValues);
    vector<int>answer;
    while(coin!=0){
        m-=coin;
        answer.push_back(coin);
        coin = lastCoin(numCoins-1,m,coinValues);
    }
    // Compute the output in the indicated way by the unit tests
    for(int i=0; i<answer.size();i++){
        res += to_string(answer.at(i))+';';
    }
    return res;


}

int minCoins(int i, int k, int *coinValues){
    if(k==0){
        return 0;
    }
    else if(k<0 && i==0){
        return -1;
    }
    else if(i==0|| (coinValues[i]<=k && minCoins(i,k-coinValues[i],coinValues)<minCoins(i-1,k,coinValues))){
        return minCoins(i,k-coinValues[i],coinValues)+1;
    }
    else{
        return minCoins(i-1,k,coinValues);
    }
}

int lastCoin(int i, int k , int *coinValues){
    if(k==0||i==-1){
        return 0;
    }
    else if(k<0){
        return -1;
    }
    else if(i==0|| (coinValues[i]<=k && minCoins(i,k-coinValues[i],coinValues)<minCoins(i-1,k,coinValues))){
        return coinValues[i];
    }
    else{
        return lastCoin(i-1,k,coinValues);
    }
}
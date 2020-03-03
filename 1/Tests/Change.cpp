/*
 * Change.cpp
 */

#include "Change.h"

string calcChange(int m, int numCoins, int *coinValues) {
    if (m == 0)
        return "";

    int minCoins[m + 1];  // quantidade de moedas usadas
    int lastCoin[m + 1];  // ultima moeda adicionada

    fill_n(minCoins, m + 1, 0);
    fill_n(lastCoin, m + 1, 0);

    // percorre quantas moedas é para usar, usando 1, 2, 3...
    for (int i = 1; i <= numCoins; i++) {
        // montante a ter em consideração desde o valor da moeda até ao valor do montante requeridp
        for (int k = coinValues[i - 1]; k <= m; k++) {
            // ...==0 quando compara com i=1 para puder adicionar a 1ª moeda
            // se a quant. moedas usadas no montante a ter em conta for maior que
            //      quant. moedas usadas com o montante atual menos o valor da moeda maior
            // OU SEJA se ao adicionar a moeda nova o numero minimo de moedas diminui
            if (minCoins[k] == 0 || 1 + minCoins[k - coinValues[i - 1]] < minCoins[k]) {
                //atualiza o numero minimo de moedas: passa a ser 1 <- a moeda adicionada +
                //                                              o numero minimo de moedas do montante tirando o valor da moeda considerada
                minCoins[k] = 1 + minCoins[k - coinValues[i - 1]];
                //atualiza também a ultima moeda para ser a moeda de maior valor
                lastCoin[k] = coinValues[i - 1];
            }
            // não entra no if, a moeda não serve, então não mudam os arrays
        }
    }

    string output = "";
    int temp = m;

    if (minCoins[m] == 0)
        return "-";

    for (int i = 0; i < minCoins[m]; i++) {
        output += to_string(lastCoin[temp]) + ";";
        temp -= lastCoin[temp];
    }

    return output;
}
/*    if(numCoins==0 || m==0){//if there are no coins or the change is 0
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
}*/
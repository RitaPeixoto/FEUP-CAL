/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>
#include <iostream>

string calcSum(int* sequence, int size)
{
    if(size <=0){
        return "";
    }
    else if(size == 1){
        return to_string(sequence[0] )+",0"+";";
    }

    string res="";
    int n=0;

    while(n!=size){
        pair<int,int> t= sumMin(sequence,n+1,size);
        n++;
        res +=to_string(t.first)+","+to_string(t.second)+";";
    }


	return res;
}


pair<int,int> sumMin(int *sequence, int n, int size){
    int index=0,sum=0,sumt=0;

    for(int i=0;i<size;i++){
        if((i+n)<=size){
            sumt=0;
            for(int j=i; j<i+n;j++) {
                sumt += sequence[j];
            }
            if(sumt<sum ||(i==0)){
                index =i;
                sum=sumt;
            }
        }
        else{
            break;
        }
    }

    return make_pair(sum, index);
}

#include "mssm.h"

Array<int> otherArray(Array<int> john){
    Array<int> expArray;
    for (int i = 0; i < (john.size() + 1); i++){
        if (i % 2 != 0){
            expArray.append(john[i]);
        }
    }
    return expArray;
}

Array<int> oddVals(Array<int> john){
    Array<int> expArray;
    for (int i = 0; i < (john.size() + 1); i++){
        if (i % 2 == 0){
            expArray.append(john[i]);
        }
    }
    return expArray;
}

Array<int> mush(Array<int> Aral1, Array<int> Aral2){
    Array<int> expArray;
    for (int i = 0; i < (Aral1.size() + 1); i++){
        expArray.append(Aral1[i]);
    }
    for (int i = 0; i < (Aral2.size() + 1); i++){
        expArray.append(Aral2[i]);
    }
}

Array<int> uniqueInts(Array<int> joe){
    
}

int main(){

}
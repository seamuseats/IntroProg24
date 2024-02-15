#include "mssm.h"
#include "rand.h"
#include <cmath>
#include <cstdlib>

bool odd(int n){
    while (n > 1){
        n = n - 2;
    }
    if (n == 1){
        return true;
    }
    else{
        return false;
    }
}

int lastInt(int n){
    int i = n % 10;
    print("{}", i);
}

float roomVol(double w, double l){
    return 2 * w * 2 * l * 8;
}

int toInt(int n){
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += i;
    }
    
}

int sumOfAllOfThePositiveIntegersLessThanOrEqualToNThatAreMultiplesOfThreeOrFive(int n){
    int sum = 0;
    for (int i = 0; i <= n; i++){
        if (i % 3 == 0 || i % 5 == 0){
            sum += i;
        }
    }
}

int nthDigit(int a, int b){
    string eiy = to_string(a);
    return eiy[b];
}

int diceRoll(){
    int dieOne = randomInt(1, 6);
    int dieTwo = randomInt(1, 6);
    int dieThree = randomInt(1, 6);
    return dieOne + dieTwo + dieThree;
}

int main(){
    int a;
    int b;
    cin >> a;
    cin >> b;
    println("{}", nthDigit(a, b));
}
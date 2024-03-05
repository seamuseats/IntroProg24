#include "mssm.h"
#include <cmath>
#include <vector>

string change(double money,double cost){
    double change = money - cost;
    int bills[4] = {0, 0, 0, 0};
    int coins[4] = {0, 0, 0, 0};
    //Array<int> x{1,2,3,4}; <-- initializes an array x with 4 values
    //append (puts value on the end)
    //insertAtIndex (puts value at index)
    //removeAtIndex (removes value at index)
    //

    
    while (change >= 20){
        bills[0]++;
        change -= 20;
    }
    while (change >= 10){
        bills[1]++;
        change -= 10;
    }
    while (change >= 5){
        bills[2]++;
        change -= 5;
    }
    while (change >= 1){
        bills[3]++;
        change--;
    }
    
    
    while (change / 0.25 >= 1){
        coins[0]++;
        change -= 0.25;
    }
    while (change / 0.1 >= 1){
        coins[1]++;
        change -= 0.1;
    }
    while (change / 0.05 >= 1){
        coins[2]++;
        change -= 0.05;
    }
    while (change / 0.01 >= 1){
        coins[3]++;
        change -= 0.01;
    }
    string expStr = "";
    
    expStr += to_string(bills[0]);
    expStr += " 20s, ";
    expStr += to_string(bills[1]);
    expStr += " 10s, ";
    expStr += to_string(bills[2]);
    expStr += " 5s, ";
    expStr += to_string(bills[3]);
    expStr += " 1s, ";
    expStr += to_string(coins[0]);
    expStr += " quarters, ";
    expStr += to_string(coins[1]);
    expStr += " dimes, ";
    expStr += to_string(coins[2]);
    expStr += " nickels, ";
    expStr += to_string(coins[3]);
    expStr += " pennies, ";
    return expStr;
}

double average(Array<double> values){
    double sum{0};
    for (int i = 0; i < values.size(); sum += values[i], i++){}
    double average = sum / values.size();
    return average;
}

double arrayHigh(Array<double> amog){
    double high{amog[1]};
    for (int i = 0; i <= amog.size(); i++){
        if (amog[i] >= high){
            high = amog[i];
        }
    }
    return high;
}

int main(){
    double moneyIn;
    double price;
    println("money had?");
    cin >> moneyIn;
    println("Price?");
    cin >> price;
    println("{}", change(moneyIn, price));

    
    return 0;

}
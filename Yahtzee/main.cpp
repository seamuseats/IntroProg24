#include "mssm.h"
#include "rand.h"
#include <cmath>
#include <cstdlib>
#include <fmt/color.h>

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

Array<int> dieStacks(Array<int> dice){
    Array<int> dieStacks;
    dieStacks.resize(6);
    for (int i = 0; i < dice.size(); i++){
        switch(dice[i]){
        case 1:
            dieStacks[0]++;
            break;
        case 2:
            dieStacks[1]++;
            break;
        case 3:
            dieStacks[2]++;
            break;
        case 4:
            dieStacks[3]++;
            break;
        case 5:
            dieStacks[4]++;
            break;
        case 6:
            dieStacks[5]++;
            break;
        }
    }
    return dieStacks;
}

bool contains(Array<int> array, int x){
    for (int i = 0; i < array.size(); i++){
        if (dieStacks(array)[i] == x){
            return true;
        }
    }
    return false;
}

int nthDigit(int a, int b){
    string eiy = to_string(a);
    return eiy[b];
}

int arraySum(Array<int> array){
    int sum = 0;
    for(int i = 0; i < array.size(); i++){
        sum += array[i];
    }
    return sum;
}

Array<bool> calcOpts(Array<int> dice, Array<bool> used){
    Array<bool> Opts;
    Array<int> dieStacks{0, 0, 0, 0, 0, 0};
    for (int i = 0; i < dice.size(); i++){
        switch(dice[i]){
            case 1:
                dieStacks[0]++;
                break;
            case 2:
                dieStacks[1]++;
                break;
            case 3:
                dieStacks[2]++;
                break;
            case 4:
                dieStacks[3]++;
                break;
            case 5:
                dieStacks[4]++;
                break;
            case 6:
                dieStacks[5]++;
                break;
        }
    }
    //two of a kind
    if(used[1] == false){
        Opts.append(true);
    }
    else{
        Opts.append(false);
    }

    Opts.append(used[1] == false);
    //three of a kind
    if(used[2] == false){
        Opts.append(true);
    }
    else{
        Opts.append(false);
    }
    //full house
    if(used[3] == false){
        Opts.append(true);
    }
    else{
        Opts.append(false);
    }
    //small straight
    if(((dieStacks[0] > 0 && dieStacks[1] > 0 && dieStacks[2] > 0 && dieStacks[3] > 0) || (dieStacks[1] > 0 && dieStacks[2] > 0 && dieStacks[3] > 0 && dieStacks[4] > 0) || (dieStacks[2] > 0 && dieStacks[3] > 0 && dieStacks[4] > 0 && dieStacks[5] > 0)) && used[4] == false){
        Opts.append(true);
    }
    else{
        Opts.append(false);
    }
    //large straights
    if(used[5] == false && ((dieStacks[0] > 0 && dieStacks[1] > 0 && dieStacks[2] > 0 && dieStacks[3] > 0 && dieStacks[4] > 0) || (dieStacks[1] > 0 && dieStacks[2] > 0 && dieStacks[3] > 0 && dieStacks[4] > 0 && dieStacks[5] > 0))){
        Opts.append(true);
    }
    else{
        Opts.append(false);
    }
    //YAHTZEEE
    if(dieStacks[0] > 4 || dieStacks[1] > 4 || dieStacks[2] > 4 || dieStacks[3] > 4 || dieStacks[4] > 4 || dieStacks[5] > 4){
        Opts.append(true);
    }
    else{
        Opts.append(false);
    }
    //YAHTZEEE BONUS
    if((dieStacks[0] > 4 || dieStacks[1] > 4 || dieStacks[2] > 4 || dieStacks[3] > 4 || dieStacks[4] > 4 || dieStacks[5] > 4) && Opts[5] == true){
        Opts.append(true);
    }
    else{
        Opts.append(false);
    }
    //dieStacks[0]
    if(used[7] == false){
        Opts.append(true);
    }
    else{
        Opts.append(false);
    }
    //dieStacks[1]
    if(used[8] == false){
        Opts.append(true);
    }
    else{
        Opts.append(false);
    }
    //dieStacks[2]
    if(used[9] == false){
        Opts.append(true);
    }
    else{
        Opts.append(false);
    }
    //dieStacks[3]
    if(used[10] == false){
        Opts.append(true);
    }
    else{
        Opts.append(false);
    }
    //dieStacks[4]
    if(used[11] == false){
        Opts.append(true);
    }
    else{
        Opts.append(false);
    }
    //dieStacks[5]
    if(used[12] == false){
        Opts.append(true);
    }
    else{
        Opts.append(false);
    }
    return Opts;
}

int smallStraight(Array<int> dice){
    sort(dice.asVector().begin(), dice.asVector().end());

    
}

int calcUpperScore(Array<int> dice, int ruleNum){
    int score{0};
    
    // aces
        for (int i = 0; i < dice.size(); i++){
            switch(ruleNum){
            case 1:
                if(dice[i] == 1){
                    score += dice[i];
                }
                break;
            case 2:
                if(dice[i] == 2){
                    score += dice[i];
                }
                break;
            case 3:
                if(dice[i] == 3){
                    score += dice[i];
                }
                break;
            case 4:
                if(dice[i] == 4){
                    score += dice[i];
                }
                break;
            case 5:
                if(dice[i] == 5){
                    score += dice[i];
                }
                break;
            case 6:
                if(dice[i] == 6){
                    score += dice[i];
                }
                break;
            }
        
    }
    return score;
}      
        
int threeOfAKind(Array<int> dice){
    for (int i = 0; i < dice.size(); i++){
        if(dieStacks(dice)[i] >= 3){
            return arraySum(dice);
        }
    }
    return 0;
}

int fourOfAKind(Array<int> dice){
    for (int i = 0; i < dice.size(); i++){
        if(dieStacks(dice)[i] >= 4){
            return arraySum(dice);
        }
    }
    return 0;
}

int fullHouse(Array<int>dice){
    Array<int> stacks = dieStacks(dice);
    for (int i = 0; i < dice.size(); i++){
        if(contains(dice, 3) && contains(dice, 2)){
            return 25;
        }
        return 0;
    }
}

int calcScore(Array<int> dice, int ruleNum){
    int score;
    switch(ruleNum){
    // aces
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        return calcUpperScore(dice, ruleNum);
    //three of a kind
    case 7:
        return threeOfAKind(dice);
    case 8:
        return fourOfAKind(dice);
    case 9:
        break;
    
    

    }
}

Array<int> diceRoll(Array<int> holdId, Array<int> prevRoll){
    //loop over all 5 dice
    Array<int> exportArray;
    if (prevRoll.size() != 1)
    {
        for (int i = 0; i < 5; i++){
            if (holdId[i] == 0){
                exportArray.append(randomInt(1, 6));
            }
            else{
                exportArray.append(prevRoll[i]);
            }
        }
    }
    else{
        for (int i = 0; i < 5; i++){
            exportArray.append(randomInt(1, 6));
        }
    }
    return exportArray;
}
int main(){

    println("{}", fullHouse({1, 1, 2, 2, 2}));
    // string uname{getlogin()};
    // Array<int> dice{0};
    // Array<int> holdId{0};
    // Array<bool> used{false, false, false, false, false, false, false, false, false, false, false, false, false};
    // int q{0};
    // string c;
    // dice = diceRoll(holdId, dice);
    // fmt::print(fg(fmt::color::green), "Welcome {} to the wonderful game: Yahtzee! Brought to you by MSSM IntroProg\n", uname);
    // println("To begin, we'll start by rolling the dice!");
    // // StdAudio.play("diceRoll.wav");
    // println("survey says...\n {}!", dice);
    // println("your Options are {}", calcOpts(dice, used));
    // Array<bool> Opts{calcOpts(dice, used)};
    // println("do you wish to reroll? (Y/n)");
    // cin >> q;
    // if (q = ("Y" || "")){
    //     dice = diceRoll(holdId, dice);
    //     println("survey says...\n {}!", dice);
    //     println("your Options are {}", calcOpts(dice, used));
    // }
    // else{
    //     println("what do you want to do? (--help to see what goes where)");
    //     cin >> c;
    //     if(c == "--help"){
    //         println("(1-6, ones through sixes), (7-8, three/four of a kind), (9, full house), (10-11 sm/lg straight) (12, Yahtzee)");
    //     }
    //     else{
            
    //     }
    // }
}
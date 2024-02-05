#include "mssm.h"
#include <sstream>

string stringify_double(double val) {
    ostringstream s;
    s << val;
    return s.str();
}

string deriv(double john[], int coef) {
    //creats export string
    string exportStr = "";
    //defines the new exponents w/ power rule
    double coefs[coef - 1];
    //loops over writing code for every john[i] term
    for (int i = 0; i < coef - 1; i++){
        //defines degree of each term 
        int degree = coef - 1 - i;
        //defines the new coefficients with the power rule
        coefs[i] = john[i] * degree;
        //formatting and writing
        if (i != 0){
            exportStr += " + " + stringify_double(coefs[i]);
        }
        else{
            exportStr += stringify_double(coefs[i]);
        }

        if (degree - 1 > 0){
            exportStr += "x";
            if (degree - 1 > 1){
                exportStr += "^" + to_string(degree - 1);
            }
        }
    }
    return exportStr;
}

int main()
{
    print("Hello World!\n");   // statement
    
    int x = 0; 

    println("what do you want to do?\n 1 = divide,\n 2 = multiply,\n 3 = subtract,\n 4 = add,\n 5 = derivative of arbitrary polynomial,\n 6 = exponentiate");
    cin >> x;

    if (x > 6){
        println("too big!");
    }

    if (x <= 6 && x > 0){
        //a and b for addition, subtraction, multiplication, and division.
        float a;
        float b;
        if (x == 6){
            println("raise _");
            cin >> a;
            println("to the _ power");
            cin >> b;
            float c;
            c = pow(a, b);
            println("equals {}", c);
        }
        else if (x == 5){
            //checks degree of polynomial
            int degree;
            //requests input for number of terms
            println("terms?");
            cin >> degree;
            //makes an array with as many doubles as the degree
            double nums[degree];
            //asks for coefficients
            for (int i = 0; i < degree; i ++){
                println("value for {}th term?", i + 1);
                cin >> nums[i];
            }
        println("{}", deriv(nums, degree));

        }
        else if (x == 4){
            println("add _ ");
            cin >> a;
            println("to _ ...");
            cin >> b;
            println("equals {}", a + b);
        }
        else if (x == 3){
            println("subtract _");
            cin >> a;
            println("from _ ...");
            cin >> b;
            println("equals {}", b - a);
        }
        else if (x == 2){
            println("multiply _");
            cin >> a;
            println("by _ ...");
            cin >> b;
            println("equals {}", a * b);
        }
        else {
            println("divide _");
            cin >> a;
            println("by _ ...");
            cin >> b;
            if (b != 0){
                println("equals {}", a / b);
            }
            else {
                println("stupid!!!!!!!!!!!!!");
            }
        }
        
    }

    return 0;
}
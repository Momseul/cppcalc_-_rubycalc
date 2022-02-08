#include <iostream>
#include <sstream>
#include <string>
#include "calcex.h"
#include "calculator.h"
#include <iomanip>
using namespace std;

Calculator* calc;

int main(int argc, char* argv[]) {
   string line;
   calc = new Calculator();
 while(getline(cin, line)){
   try {

     //      cout << "Please enter a calculator expression: ";

      //getline(cin, line);
      // line + '\n';

      // calc = new Calculator();
      
 
      float result = calc->eval(line);

      //cout << "The result is " << setprecision(2) << fixed << result << endl;
      cout << setprecision(2) << fixed << result << endl;
      
      //}

      //delete calc;

   }
   catch(Exception ex) {
      cout << "Program Aborted due to exception!" << endl;
   }
}
   delete calc;
}
   

#pragma once

#include <string>
#include <map>
 
using namespace std;


class Calculator {
 public:
   Calculator();

   float eval(string expr);
   void store(float val);
   float recall();
   float clear();
   void setValue(string val, float result);
   float mapS(string val);

 private:
   float memory;
   map<string,float> identifiers;
};

extern Calculator* calc;



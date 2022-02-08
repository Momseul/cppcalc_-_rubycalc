#include "calculator.h"
#include "parser.h"
#include "ast.h"
#include <string>
#include <iostream>
#include <sstream>
#include <map>


Calculator::Calculator():
   memory(0.0)
{}

float Calculator::eval(string expr) {

   Parser* parser = new Parser(new istringstream(expr));
   
   AST* tree = parser->parse();
   
   float result = tree->evaluate();
   
   delete tree;
   
   delete parser;
   
   return result;
}

void Calculator::store(float val) {
   memory = val;
}

float Calculator::recall() {
   return memory;
}

float Calculator::clear() {
  memory = 0;
  return memory;
}

void Calculator::setValue(string val, float result) {
  identifiers.insert( std::pair<string,float>(val,result) );

}

float Calculator::mapS(string val) {
  map<string, int>::iterator it;
  if(identifiers.empty()) {
    return 0.0;
  }
  float x = identifiers.find(val)->second;
  return x;
  
}


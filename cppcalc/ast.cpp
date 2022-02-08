#include "ast.h"
#include <iostream>
#include <math.h> 
#include "calculator.h"

// for debug information uncomment
//#define debug

AST::AST() {}

AST::~AST() {}

BinaryNode::BinaryNode(AST* left, AST* right):
   AST(),
   leftTree(left),
   rightTree(right)
{}

BinaryNode::~BinaryNode() {
#ifdef debug
   cout << "In BinaryNode destructor" << endl;
#endif

   try {
      delete leftTree;
   } catch (...) {}

   try {
      delete rightTree;
   } catch(...) {}
}
   
AST* BinaryNode::getLeftSubTree() const {
   return leftTree;
}

AST* BinaryNode::getRightSubTree() const {
   return rightTree;
}

UnaryNode::UnaryNode(AST* sub):
   AST(),
   subTree(sub)
{}

UnaryNode::~UnaryNode() {
#ifdef debug
   cout << "In UnaryNode destructor" << endl;
#endif

   try {
      delete subTree;
   } catch (...) {}
}
   
AST* UnaryNode::getSubTree() const {
   return subTree;
}

AddNode::AddNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

float  AddNode::evaluate() {
   return getLeftSubTree()->evaluate() + getRightSubTree()->evaluate();
}

SubNode::SubNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

float SubNode::evaluate() {
   return getLeftSubTree()->evaluate() - getRightSubTree()->evaluate();
}

TimesNode::TimesNode(AST* left, AST* right):
  BinaryNode(left,right)
{}

float TimesNode::evaluate() {
   return getLeftSubTree()->evaluate() * getRightSubTree()->evaluate();
}


DivideNode::DivideNode(AST* left, AST* right):
  BinaryNode(left,right)
{}

float DivideNode::evaluate() {
  float n = getRightSubTree()->evaluate();
  if(n == 0){
    cerr << "inf" << endl;
  }
   return getLeftSubTree()->evaluate() / getRightSubTree()->evaluate();
}

ModuleNode::ModuleNode(AST* left, AST* right):
  BinaryNode(left, right)
{}

float ModuleNode::evaluate() {
  //return getLeftSubTree()->evaluate() % getRightSubTree()->evaluate();
  return fmod(getLeftSubTree()->evaluate(), getRightSubTree()->evaluate());
}

ABSNode::ABSNode(AST* ast) :
  UnaryNode(ast) { }

float ABSNode::evaluate() {
   float n = getSubTree()->evaluate();
   n = fabs (n);
  return n;
}


SINNode::SINNode(AST* ast) :
  UnaryNode(ast) { }


float SINNode::evaluate() {
  float n = sin(getSubTree()->evaluate());
  return n;
}

COSNode::COSNode(AST* ast) :
  UnaryNode(ast) { }


float COSNode::evaluate() {
  float n = cos(getSubTree()->evaluate());
  return n;
}

TANNode::TANNode(AST* ast) :
  UnaryNode(ast) { }


float TANNode::evaluate() {
  float PI = 3.14159265;
  float n = tan(getSubTree()->evaluate() * PI / 180.0);
  return n;
}

EXPNode::EXPNode(AST* ast) :
  UnaryNode(ast) { }


float EXPNode::evaluate() {
  float n = exp(getSubTree()->evaluate());
  return n;
}

LOGNode::LOGNode(AST* ast) :
  UnaryNode(ast) { }


float LOGNode::evaluate() {
  float n = log(getSubTree()->evaluate());
  return n;
}

SQRTNode::SQRTNode(AST* ast) :
  UnaryNode(ast) { }


float SQRTNode::evaluate() {
  float n = sqrt(getSubTree()->evaluate());
  if (n < 0) {
    cout << "nan" <<endl;
  }
  return n;
}


StoreNode::StoreNode(AST* ast) :
  UnaryNode(ast) { }

float StoreNode::evaluate() {
  
  calc->store(getSubTree()->evaluate());
  return calc->recall();
}

NonNode::NonNode(AST* ast) :
  UnaryNode(ast) { }

float NonNode::evaluate() {
  return getSubTree()->evaluate() * -1;
  //return getSubTree()->evaluate() * -1.0;
  }

PlusNode::PlusNode(AST* ast) :
  UnaryNode(ast) { }

float PlusNode::evaluate() {
  float x = calc->recall();
  calc->store(x + getSubTree()->evaluate());
  return calc->recall();
}

MinusNode::MinusNode(AST* ast) :
  UnaryNode(ast) { }

float MinusNode::evaluate() {
  float x = calc->recall();
  calc->store(x - getSubTree()->evaluate());
  return calc->recall();
}

ClearNode::ClearNode() : AST() { }

float ClearNode::evaluate() {
  return calc->clear();
} 

NumNode::NumNode(float n) :
   AST(),
   val(n)
{}

float NumNode::evaluate() {
   return val;
}

IDNode::IDNode(string m) :
  AST(),
  val(m)
{}

float IDNode::evaluate() {
  return calc->mapS(val);
}

AssignationNode::AssignationNode(AST* ast, string val):
  UnaryNode(ast),
  val(val)
{}

float AssignationNode::evaluate() {
  float n = getSubTree()->evaluate();
  calc->setValue(val, n);
  return n;
}

RecallNode::RecallNode() : AST() { }

float RecallNode::evaluate() {
  return calc->recall();
}

			 

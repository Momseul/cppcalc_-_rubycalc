#pragma once
#include<string>

// using namespace std;

class AST {
 public:
   AST();
   virtual ~AST() = 0;
   virtual float evaluate() = 0;
};

class BinaryNode : public AST {
 public:
   BinaryNode(AST* left, AST* right);
   ~BinaryNode();

   AST* getLeftSubTree() const;
   AST* getRightSubTree() const;

 private:
   AST* leftTree;
   AST* rightTree;
};

class UnaryNode : public AST {
 public:
   UnaryNode(AST* sub);
   ~UnaryNode();

   AST* getSubTree() const;

 private:
   AST* subTree;
};

class AddNode : public BinaryNode {
 public:
   AddNode(AST* left, AST* right);
   
   float evaluate();
};

class SubNode : public BinaryNode {
 public:
   SubNode(AST* left, AST* right);

   float evaluate();
};

class TimesNode : public BinaryNode {
 public:
  TimesNode(AST* left, AST* right);

  float evaluate();
};

class DivideNode : public BinaryNode {
 public:
  DivideNode(AST* left, AST* right);

  float evaluate();
};

class ModuleNode : public BinaryNode {
 public:
  ModuleNode (AST* left, AST* right);

  float evaluate();
};

class ABSNode : public UnaryNode {
 public:
  ABSNode (AST* ast);
  float evaluate();
};

class SINNode : public UnaryNode {
 public:
  SINNode (AST* ast);
  float evaluate();
};

class COSNode : public UnaryNode {
 public:
  COSNode (AST* ast);
  float evaluate();
};

class TANNode : public UnaryNode {
 public:
  TANNode (AST* ast);
  float evaluate();
};

class EXPNode : public UnaryNode {
 public:
  EXPNode (AST* ast);
  float evaluate();
};

class LOGNode : public UnaryNode {
 public:
  LOGNode (AST* ast);
  float evaluate();
};

class SQRTNode : public UnaryNode {
 public:
  SQRTNode (AST* ast);
  float evaluate();
};

class StoreNode : public UnaryNode {
 public:
  StoreNode(AST* ast);
  float evaluate();

 private:
  float val;
};

class NonNode : public UnaryNode {
 public:
  NonNode(AST* ast);
  float evaluate();

 private:
  float val;
  
};

class PlusNode : public UnaryNode {
 public:
  PlusNode(AST* ast);
  float evaluate();
};

class MinusNode : public UnaryNode {
 public:
  MinusNode(AST* ast);
  float evaluate();
};

class ClearNode : public AST {
 public:
  ClearNode();
  float evaluate();
};

class NumNode : public AST {
 public:
   NumNode(float n);

   float evaluate();

 private:
   float val;
};

class IDNode : public AST {
 public:
  IDNode(std::string m);

  float evaluate();

 private:
  std::string val;
};

class AssignationNode : public UnaryNode {
 public:
  AssignationNode(AST* ast, std::string val);

  float evaluate();

 private:
  std::string val;
};

class RecallNode : public AST {
 public:
  RecallNode();
  float evaluate();
};


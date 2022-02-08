#include "parser.h"
#include "calcex.h"
#include <string>
#include <sstream>

Parser::Parser(istream* in) {
  scan = new Scanner(in);
}

Parser::~Parser() {
  try {
    delete scan;
  } catch (...) {}
}

AST* Parser::parse() {
  return Interactive();
}

AST* Parser::Interactive() {
  Token* t = scan->getToken();

  if (t->getType() != identifier){
    cerr << "Parser Error: expected identifier" << endl;
    throw ParseError;
  }
  Token* a = scan->getToken();
  if (a->getType() != equ) {
    cerr << "Parser Error: Expected '='" << endl;
    throw ParseError;
  }
  AST* ca = Expr();
  a = scan->getToken();
  if (a->getType() != semicolon) {
    cerr << "Parser Error: Expected ';'" << endl;
    throw ParseError;
  }
  a = scan->getToken();
  if (a->getType() != eof){
    cerr << "Parser Error: expected eof, found token at column" << a->getCol() << endl;
    throw ParseError;
  }

  return new AssignationNode(ca, t->getLex());
  
  
  //if (t->getType() == identifier) {
  //Token* a = scan->getToken();
  //if (a->getType() == equ) {
  //  AST* ca = Expr();
  //  a = scan->getToken();
  //  if (a->getType() == semicolon) {
  //	a = scan->getToken();
  //	if (a->getType() != eof) {
  //	cerr << "Syntax Error: Expected '\n', found token at column " << a->getCol() << endl;
  //	}
  //	return new AssignationNode(ca, t->getLex());
  //  }
  //  else {
  //	cerr << "Syntax Error: Expected ;, found token at column " << a->getCol() << endl;
  //
  //	throw ParseError;
  //	
  //  }
  //  cerr << "Syntax Error: Expected =, found token at column " << t->getCol() << endl;
  //
  //  throw ParseError;
  //}
    
  // }
  // scan->putBackToken();
  
  //AST* result = Expr();
    //Token* t = scan->getToken();
  //t = scan->getToken();
  //if (t->getType() != semicolon) {
    
  //cerr << "Syntax Error: Expected semicolon, found token at column " << t->getCol() << endl;

  //}
  //t = scan->getToken();
  
  //if (t->getType() != eof) {                                                                                            

  //cerr << "Syntax Error: Expected EOF, found token at column " << t->getCol() << endl;                                    

  //throw ParseError;
  //}

  //return result;
      
}

AST* Parser::Expr() {
  return RestExpr(Term());
}

AST* Parser::RestExpr(AST* e) {
  Token* t = scan->getToken();

  if (t->getType() == add) {
    return RestExpr(new AddNode(e,Term()));
  }

  if (t->getType() == sub)
    return RestExpr(new SubNode(e,Term()));

  scan->putBackToken();

  return e;
}

AST* Parser::Term() {
  return RestTerm(Storable());  
}

AST* Parser::RestTerm(AST* e) {
  Token *t = scan->getToken();

  if(t->getType() == times) {
    return RestTerm(new TimesNode(e, Storable()));  
  }

  if(t->getType() == divide) {
    return RestTerm(new DivideNode(e, Storable()));
  }

  if(t->getType() == module) {
    return RestTerm(new ModuleNode(e, Storable()));
  }

  scan->putBackToken();
  return e;
}

AST* Parser::Storable() {
  return MemOperation(Negation());
}

AST* Parser::MemOperation(AST* m) {
  Token* t = scan->getToken();

  if (t->getType() == keyword) {
    if (t->getLex() == "S") {
      return new StoreNode(m);
    }
    if (t->getLex() == "P") {
      return new PlusNode(m);
    }
    if (t->getLex() == "M") {
      return new MinusNode(m);
    }
    else {
      cerr << "Expected S, P or M; foud: "
	   << t->getLex() << endl;
      throw ParseError;
    }
  }
  
  scan->putBackToken();
  return m;
}

AST* Parser::Negation() {
  Token* t = scan->getToken();
  if (t->getType() == sub) {
    AST* min = Factor();
    return new NonNode(min);
  }
  scan->putBackToken();
  AST* ress = Factor();
  return ress;
}

AST* Parser::Factor() {
  
  Token* t = scan->getToken();

  if (t->getType() == number) {
    // istringstream in(t->getLex());
    //int val;
    //in >> val;
    //return new NumNode(val);

    //string str;
    istringstream ss(t->getLex());
    ss.precision(2);
    float f;
    if (!(ss >> fixed >>f))
      {
      }
    // cout << f << endl; 
    return new NumNode(f);
  }
  
  if (t->getType() == identifier) {
    istringstream in(t->getLex());
    string val;
    in >> val;
    string call = "call";
    string abs = "abs";
    string sin = "sin";
    string cos = "cos";
    string tan = "tan";
    string exp = "exp";
    string log = "log";
    string sqrt = "sqrt";
    int i = 0;
    
    if(val.compare(call) == 0){
      t = scan->getToken();
      if(t->getType() == identifier) {
    	istringstream buff(t->getLex());
    	string ca;
    	buff >> ca;
    	if(ca.compare(abs) == 0){
	  t = scan->getToken();
	  if(t->getType() == lparen){
	    AST* ro = Expr();
	    t = scan->getToken();
	    if(t->getType() == rparen){
	      return new ABSNode(ro);
	    }
	    else{
	      cerr << "Expected ) " << endl;
	    }
	  }
	  else{
	    cerr << "Expected ( " << endl;
	      }
	}
	if(ca.compare(sin) == 0){
	  t = scan->getToken();
	  if(t->getType() == lparen){
	    AST* ro = Expr();
	    t = scan->getToken();
	    if(t->getType() == rparen){
	      return new SINNode(ro);
	    }
	    else{
	      cerr << "Expected ) " << endl; 
	    }
	  }
	  else{
	    cerr << "Expected ( " << endl;
	  }
	}
	if(ca.compare(cos) == 0){
          t = scan->getToken();
          if(t->getType() == lparen){
            AST* ro = Expr();
            t = scan->getToken();
            if(t->getType() == rparen){
              return new COSNode(ro);
            }
            else {
	      cerr << "Expected ) " << endl;
	    }
          }
          else{
	    cerr << "Expected (" << endl;
	  }
	}
	if(ca.compare(tan) == 0){
          t = scan->getToken();
          if(t->getType() == lparen){
            AST* ro = Expr();
            t = scan->getToken();
            if(t->getType() == rparen){
              return new TANNode(ro);
            }
            else{
	      cerr << "Expectes ) "<< endl;
	    }
          }
          else{
	    cerr << "Expected ( " << endl;
	  }
	}
	if(ca.compare(exp) == 0){
          t = scan->getToken();
          if(t->getType() == lparen){
            AST* ro = Expr();
            t = scan->getToken();
            if(t->getType() == rparen){
              return new EXPNode(ro);
            }
            else{
	      cerr << "Expected ) " << endl;
	    }
          }
          else{
	    cerr << "Expecte ( " << endl;
	  }
	}
	if(ca.compare(log) == 0){
          t = scan->getToken();
          if(t->getType() == lparen){
            AST* ro = Expr();
            t = scan->getToken();
            if(t->getType() == rparen){
              return new LOGNode(ro);
            }
            else{
	      cerr << "Expected )" << endl;
	      throw ParseError;
	    }
          }
          else{
	    cerr << "Expected ( " << endl;
	    throw ParseError;
	  }
	}
	if(ca.compare(sqrt) == 0){
          t = scan->getToken();
          if(t->getType() == lparen){
            AST* ro = Expr();
            t = scan->getToken();
            if(t->getType() == rparen){
              return new SQRTNode(ro);
            }
            else{
	      cerr << "Expected ) " << endl;
	      throw ParseError;
	    }
          }
          else{
	    cerr << "Expected ( " << endl;
	    throw ParseError;
	  }
	}
      } //NO TOCAR
      else{
	cerr << "Expected id " << endl;
	throw ParseError;
      }
    }
    // string s = t->getLex();
    return new IDNode(val);
  }
 
  if (t->getType() == keyword) {
    if (t->getLex() == "R") {
      return new RecallNode();
    }

    if (t->getLex() == "C") {
      return new ClearNode();
    }
    else {
      cerr << "Error expected R, found: "
	   << t->getLex() << endl;
      throw ParseError;
    }
  }

  if (t->getType() == lparen) {
    
    AST* result = Expr();
    t = scan->getToken();
    if (t->getType() == rparen) {
      return result;
    }
    else {
      cerr << "Error expected ), found: "
	   << t->getLex() << endl;
      throw ParseError;
    }
  }
  
  cerr << "Expected number, R, C, (" << endl;

  throw ParseError;

}

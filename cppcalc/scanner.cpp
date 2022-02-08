#include "scanner.h"
#include "calcex.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

//Uncomment this to get debug information
//#define debug

const int numberOfKeywords = 5;

const string keywd[numberOfKeywords] = {
  string("S"), string("R"), string("P"), string("M"), string("C")
};

Scanner::Scanner(istream* in):
  inStream(in),
  lineCount(1),
  colCount(-1),
  needToken(true),
  lastToken(0)
{}

Scanner::~Scanner() {
  try {
    delete inStream;
  } catch (...) {}
}

void Scanner::putBackToken() {
  needToken = false;
}

Token* Scanner::getToken() {
  if (!needToken) {
    needToken=true;
    return lastToken;
  }

  Token* t;
  Token* l;
  int state=0;
  bool foundOne=false;
  int c;
  string lex;
  string lexC;
  TokenType type;
  int k;
  int column, line;
  int i;
  int con;

  c = inStream->get();

  while (!foundOne) {
#ifdef debug
    cout << "c :" << c
	 << "c(char) : " << (char) c
	 << "state : " << state
	 << endl;
#endif
    colCount++;
    switch (state) {
    case 0 : 
      lex = "";
      column=colCount;
      line = lineCount;
      if (isalpha(c)) state=1;
      else if (isdigit(c)) state=2;
      else if (c=='+') state=3;
      else if (c=='-') state=4;
      else if (c=='*') state=5;
      else if (c=='/') state=6;
      else if (c=='(') state=7;
      else if (c==')') state=8;
      else if (c=='%') state=9;
      else if (c=='=') state=10;
      else if (c==';') state=11;
      else if (c=='.') state=12;
      else if (c=='\n') {
	colCount=-1;
	lineCount++;
	type = eol;
      }
      else if (isspace(c));
      else if (inStream->eof() or c == -1) {
	foundOne=true;
	type=eof;
      }
      else {
	cout << "Unrecognized Token found at line " << line <<
	  " and column " << column << endl;
	throw UnrecognizedToken;
      }
      break;
    case 1 :
      if (isalpha(c) || isdigit(c)) state=1;
      else {
	for (k=0;k<numberOfKeywords;k++)
	  if (lex == keywd[k]) {
	    foundOne = true;
	    type = keyword;
	  }
	if (!foundOne) {
	  type = identifier;
	  foundOne = true;
	}
      }
      break;
    case 2 :
      if (isdigit(c)) state=2;
      else if (c=='.') state=12;
      else {
	cerr << "Scanner Error: Expected float, found int" << endl;
	throw UnrecognizedToken;
      }
      break;
    case 3 :
      type = add;
      foundOne = true;
      break;
    case 4 :
      type = sub;
      foundOne = true;
      break;
    case 5 :
      type = times;
      foundOne=true;
      break;
    case 6 :
      type = divide;
      foundOne=true;
      break;
    case 7 :
      type = lparen;
      foundOne=true;
      break;
    case 8 :
      type = rparen;
      foundOne=true;
      break;
    case 9 :
      type = module;
      foundOne=true;
      break;
    case 10:
      type = equ;
      foundOne=true;
      break;
    case 11:
      type = semicolon;
      foundOne=true;
      break;
    case 12:
      type = dot;
      state=13;
      break;
    case 13:
      if (isdigit(c)) state=13;
      else if (c=='.') {
	cerr << "Scanner Error: Another dot found " << endl;
	throw UnrecognizedToken;
      }
      else{
	type = number;
	foundOne=true;
      }
      break;
		    
    }
    if (!foundOne) {
      lex = lex + (char) c;
      c = inStream->get();
    }
  }

  inStream->putback(c);
  colCount--;
  
  if (type == number || type == identifier || type == keyword) {
    t = new LexicalToken(type,new string(lex), line, column);
    //    cout << t->getLex() << endl;
  }
  else {
    t = new Token(type,line,column);
  }

#ifdef debug
  cout << "just found " << lex << " with type " << type << endl;
#endif
  
  lastToken = t;
  return t;

}

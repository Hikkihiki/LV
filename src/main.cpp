#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "logic/symbol/symbol.hpp"
#include "version.hpp"
#include "rapidjson/document.h"
#include <cstdio>
#include <unordered_map>
#include <stack>
using namespace std;
using namespace LV;

/*
class Formula : public AtomicFormula {
public:
  Formula(const char symbol, const string proposition) {
    _sym = symbol;
    _prop = proposition;
  }

private:
  char _sym;
  string _prop;
  bool _truth;
  bool _decided;
};
*/
class Syntax {
public:
  virtual void addSymbol(const Symbol &symbol) = 0;
};
class Semantic {};

class PropositionalLogicSyntax : public Syntax {
public:
  PropositionalLogicSyntax() {}
  virtual void addSymbol(const Symbol &symbol) {
    _symbol.insert({symbol.symbol, symbol});
  }

  virtual SymType getSymType(const SymChar &ch) { return _symbol.at(ch).type; }

  const unordered_map<SymChar, Symbol> &getSymbols() { return _symbol; }

  void print() {
    for (auto &sym : _symbol) {
      cout << sym.second.type << ", " << sym.second.symbol << endl;
    }
  }

private:
  unordered_map<SymChar, Symbol> _symbol;
};
class PropositionalLogicSemantic : public Semantic {};

class PropositionalLogic {
private:
};

class Parser {
public:
  virtual bool isValid(string str) = 0;
};
class PropositionalLogicParser : public Parser {
public:
  PropositionalLogicParser(const PropositionalLogicSyntax &syntax)
      : _syn(syntax){};
  virtual bool isValid(string str) override { return true; };
  void parse(const string &str) {
    stack<SymChar> parseStack;
    for (const auto &c : str) {
      SymType type = _syn.getSymType(c);
      // switch(type) {
      //   case ST_NEGATION:
      //}
    }
    cout << endl;
  }

private:
  PropositionalLogicSyntax _syn;
};

using namespace rapidjson;

int main() {
  ifstream in("config/syntax.json");
  stringstream buffer;
  buffer << in.rdbuf();
  cout << buffer.str() << endl;

  Document d;
  d.Parse(buffer.str().c_str());

  PropositionalLogicSyntax syntax;
  const Value &symbols = d["Symbols"];
  unordered_map<string, SymType> mapSymType = {
      {"Negation", ST_NEGATION},
      {"Conjunction", ST_CONJUNCTION},
      {"Left Parentheses", ST_LEFT_PARENTHESES},
      {"Right Parentheses", ST_RIGHT_PARENTHESES},
      {"Atomic Formula", ST_ATOMIC_FORMULA}};

  for (SizeType i = 0; i < symbols.Size(); i++) {
    SymType type = mapSymType.at(symbols[i]["Type"].GetString());
    string syms = symbols[i]["Symbol"].GetString();
    for (auto &sym : syms) {
      Symbol s;
      s.type = type;
      s.symbol = sym;
      syntax.addSymbol(s);
    }
  }
  syntax.print();

  PropositionalLogicParser parser(syntax);

  string str = "~(F&A)";
  parser.parse(str);
  cout << "Formula: " << str << endl;
  cout << "IsFormula: " << (parser.isValid(str) ? "True" : "False") << endl;

  Symbol s;
  // s.print();
  cout << "Version: " << LV_VERSION_MAJOR << "." << LV_VERSION_MINOR << endl;
  return 0;
}

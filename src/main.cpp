#include <iostream>
#include <string>
#include "Symbol.hpp"

using namespace std;

class AtomicFormula {};

class Proposition : public AtomicFormula {
public:
  Proposition(const char symbol, const string proposition) {
    _sym = symbol;
    _prop = proposition;
  }

private:
  char _sym;
  string _prop;
  bool _truth;
  bool _decided;
};

class Syntax {};
class Semantic {};

class PropositionalLogicSyntax : public Syntax {};
class PropositionalLogicSemantic : public Semantic {};

class Not : public Symbol {};
class OpenBracket : public Symbol {};
class CloseBracket : public Symbol {};
class And : public Symbol {};
class PropositionalLogic {
private:
  Syntax _syn;
  Semantic _sem;
};

int main() {
  Symbol s;
  s.print();
  cout << "Hi" << endl;
  return 0;
}

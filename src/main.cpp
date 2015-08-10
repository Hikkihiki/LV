#include <iostream>
#include <string>
#include "logic/symbol/symbol.hpp"
#include "version.hpp"

using namespace std;
using namespace LV;

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
  cout << "Version: " << LV_VERSION_MAJOR << "." << LV_VERSION_MINOR << endl;
  return 0;
}

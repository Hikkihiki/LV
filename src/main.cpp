#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "logic/symbol/symbol.hpp"
#include "rapidjson/document.h"
#include <cstdio>
#include <unordered_map>
#include <stack>
#include <set>
#include "parser/cfg_parser.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>

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
class IParser {};

class LLParser : public IParser {};

class IGrammar {};

class ContextFreeGrammar : public IGrammar {

  typedef char Terminal;
  typedef char NonTerminal;

public:
  void addTerminal(const Terminal &t) { terminal.insert(t); };
  void addNonTerminal(const NonTerminal &nt) { nonTerminal.insert(nt); };

private:
  set<Terminal> terminal;
  set<NonTerminal> nonTerminal;
};

class ParserFactory {};

IGrammar *createGrammar(const string &json) { return new ContextFreeGrammar(); }

LLParser *createParser(const IGrammar &cfg) { return new LLParser(); }

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

namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace lex = boost::spirit::lex;
/*
template <typename Iterator>
struct _PropositionalLogicSyntax : qi::grammar<Iterator, mini
{
}
*/

enum tokenids {
  ID_TERM = lex::min_token_id + 10,
  ID_NON_TERM,
};

template <typename Lexer> struct CFGRulesLexer : lex::lexer<Lexer> {
  CFGRulesLexer() {}
};

template <typename Iterator>
struct CustomContextFreeGrammar : qi::grammar<Iterator, ascii::space_type> {
  CustomContextFreeGrammar() : CustomContextFreeGrammar::base_type(start) {}

  qi::rule<Iterator, ascii::space_type> start;
};

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
  // syntax.print();

  PropositionalLogicParser parser(syntax);

  string input = "~((A&B)&~C)"; // verify this is a formula
  int start = 0;
  int len = 14;

  string demoganFrom = "~(A&B)"; // A,B stands for formula (formula matching)
  string demoganTo = "~A|~B";

  string output = "~(A&B)|~~C";

  // cout << d["Syntax"]["Context-free Grammar"]["Terminals"].GetString() <<
  // endl;
  // cout << d["Syntax"]["Non-Terminals"]["P"]

  // std::vector<std::string> terms{"~", "&", "(", ")", "a", "e"};
  // std::vector<std::string> nonTerms{"S", "Abc"};
  bool bWhiteSpace = true;
  // vector<string> rules{"S -> ~S | ( S & S) | Abc", "Abc->a|e"};

  auto &CFG = d["Syntax"]["Context-free Grammar"];
  auto &terms = CFG["Terminals"];
  auto &nonTerms = CFG["Non-Terminals"];
  auto &rules = CFG["Production Rules"]["Rules"];

  parser::CFGRulesParser cfgParser;
  for (auto itr = terms.Begin(); itr != terms.End(); ++itr) {
    string s = itr->GetString();
    cfgParser.addTerminal(s);
  }
  for (auto itr = nonTerms.Begin(); itr != nonTerms.End(); ++itr) {
    string s = itr->GetString();
    cfgParser.addNonTerminal(s);
  }

  for (auto itr = rules.Begin(); itr != rules.End(); ++itr) {
    string rule = itr->GetString();
    cout << rule << endl;
    auto begin = rule.cbegin();
    auto end = rule.cend();
    bool r = qi::phrase_parse(begin, end, cfgParser, ascii::space);
    if (begin != end) {
      r = false;
    }
    cout << std::boolalpha << r << endl;
  }

  // cout << rules.back() << endl;
  // parser.parse(input);
  // cout << "Formula: " << input << endl;
  // cout << "IsFormula: " << (parser.isValid(input) ? "True" : "False") <<
  // endl;

  // Symbol s;
  // s.print();
  // cout << "Version: " << LV_VERSION_MAJOR << "." << LV_VERSION_MINOR << endl;
  return 0;
}

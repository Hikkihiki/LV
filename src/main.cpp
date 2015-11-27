#include <iostream>
#include <fstream>
#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>

#include "logic/symbol/symbol.hpp"
#include "rapidjson/document.h"

using namespace std;

struct AtomicFormula_ : public boost::spirit::qi::symbols<char, bool> {

} atomicFormula;

template <typename Iterator>
struct Formula_
    : public boost::spirit::qi::grammar<Iterator, bool(),
                                        boost::spirit::ascii::space_type> {
  Formula_() : Formula_::base_type(formula) {
    using boost::spirit::qi::_val;
    using boost::spirit::qi::_1;
    using boost::spirit::ascii::char_;
    using boost::spirit::qi::lit;

    negationFormula %= char_('~') >> formula[_val = !_1];
    andFormula %= char_('(') >> formula[_val = _1] >> char_('&') >>
                  formula[_val = _val && _1] >> char_(')');

    onlyIfFormula %= char_('(') >> formula[_val = !_1] >> lit("->") >>
                     formula[_val = _val || _1] >> char_(')');

    formula %= atomicFormula | negationFormula | andFormula | onlyIfFormula;
    // start = formula;
  }

  boost::spirit::qi::rule<Iterator, bool(), boost::spirit::ascii::space_type>
      formula;
  boost::spirit::qi::rule<Iterator, bool(), boost::spirit::ascii::space_type>
      andFormula;
  boost::spirit::qi::rule<Iterator, bool(), boost::spirit::ascii::space_type>
      negationFormula;
  boost::spirit::qi::rule<Iterator, bool(), boost::spirit::ascii::space_type>
      onlyIfFormula;
};

template <typename Iterator> bool parse_formula(Iterator first, Iterator last) {
  namespace qi = boost::spirit::qi;
  namespace ascii = boost::spirit::ascii;

  using qi::char_;
  using qi::phrase_parse;
  using ascii::space;

  bool r = phrase_parse(first, last,
                        (atomicFormula | char_('~') >> atomicFormula), space);
  if (first != last) // fail if we did not get a full match
    return false;
  return r;
}

int main() {

  /* Reading input like model and premises */
  using namespace rapidjson;

  ifstream in("../input/pl1.json");
  stringstream buffer;
  buffer << in.rdbuf();
  cout << buffer.str() << endl;

  Document d;
  d.Parse(buffer.str().c_str());
  assert(d["Atomic Formulas"].IsArray());
  Value &atomicFormulas = d["Atomic Formulas"];

  for (auto itr = atomicFormulas.Begin(); itr != atomicFormulas.End(); ++itr) {
    assert(itr->IsObject());
    assert((*itr)["Symbol"].IsString());
    assert((*itr)["Truth"].IsBool());
    assert((*itr)["Translation"].IsString());
    std::cout << (*itr)["Symbol"].GetString() << endl;
    // assert symbol does not contain reserve character like ~, & |,
    // (,),<->,->,<-.
    // actually we only allow alphanumeric expression.
    std::cout << (*itr)["Truth"].GetBool() << endl;
    std::cout << (*itr)["Translation"].GetString() << endl;
    atomicFormula.add((*itr)["Symbol"].GetString(), (*itr)["Truth"].GetBool());

    /* Building Parser */
  }

  Value &premises = d["Premises"];

  for (auto itr = premises.Begin(); itr != premises.End(); ++itr) {
    assert(itr->IsObject());
    assert((*itr)["Premise"].IsString());
    string str = (*itr)["Premise"].GetString();
    std::cout << str << endl;
    Formula_<std::string::const_iterator> fo_parser;
    bool truthVal = false;
    bool r = phrase_parse(str.cbegin(), str.cend(), fo_parser,
                          boost::spirit::ascii::space, truthVal);
    cout << "parsed: " << r << " truth value: " << truthVal << endl;

    /* Parse premise and confirm that all premises are modeled */
  }

  return 0;
}

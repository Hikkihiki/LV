#pragma once

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <string>
#include <vector>

namespace parser {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

typedef std::string string;
typedef qi::rule<std::string::const_iterator, ascii::space_type> CFGRule;
typedef std::vector<CFGRule> CFGRules;

struct CFGRulesParser
    : qi::grammar<string::const_iterator, ascii::space_type, CFGRules> {
public:
  CFGRulesParser();

  void addTerminal(string &t);
  void addNonTerminal(string &nt);

private:
  qi::symbols<char, string> nonTerm_;
  qi::symbols<char, string> term_;
  qi::rule<string::const_iterator, ascii::space_type, CFGRules> start;
  qi::rule<std::string::const_iterator, ascii::space_type, CFGRules> rhs;
};

struct CFGParser : qi::grammar<string::const_pointer, ascii::space_type> {

public:
  CFGParser() : CFGParser::base_type(start){};

private:
  qi::rule<string::const_iterator, ascii::space_type> start;
};
}

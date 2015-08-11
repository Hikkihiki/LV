#pragma once

#include <string>

namespace LV {

typedef char SymChar;

enum SymType {
  ST_UNDEFINED,
  ST_NEGATION,
  ST_CONJUNCTION,
  ST_DISJUNCTION,
  ST_LEFT_PARENTHESES,
  ST_RIGHT_PARENTHESES,
  ST_ATOMIC_FORMULA,
};

struct Symbol {
  SymType type;
  SymChar symbol;
};
}

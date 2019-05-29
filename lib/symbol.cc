#include "./symbol.h"

namespace fst {
  Symbol Symbol::Terminal(string te) {
    return Symbol(TERMINAL_SYMBOL_TYPE, te);
  }

  Symbol Symbol::NonTerminal(string te) {
    return Symbol(NON_TERMINAL_SYMBOL_TYPE, te);
  }

  Symbol Symbol::Epsilon() {
    return Terminal(EPSILON);
  }

  Symbol Symbol::EndSymbol() {
    return Terminal(END_SYMBOL_TEXT);
  }

  bool Symbol::isEpsilon() {
    return this->type == TERMINAL_SYMBOL_TYPE && this->text == EPSILON;
  }

  bool Symbol::isTerminal() {
    return this->type == TERMINAL_SYMBOL_TYPE;
  }

  bool Symbol::isNonTerminal() {
    return this->type == NON_TERMINAL_SYMBOL_TYPE;
  }

  bool Symbol::operator==(const Symbol &sym) const {
    return this->type == sym.type && this->text == sym.text;
  }

  string Symbol::toString() {
    return this->text;
  }
};

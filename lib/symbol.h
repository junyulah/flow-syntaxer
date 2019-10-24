#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include "unordered_set"

using namespace std;

/**
 * Terminals: the basic symbols from which strings are formed.
 *
 * Nonterminals: syntactic variables that denote sets of strings.
 *
 * start symbol
 */

namespace fst {
const unsigned int TERMINAL_SYMBOL_TYPE = 0; // terminal symbol
const unsigned int NON_TERMINAL_SYMBOL_TYPE = 1; // none terminal symbol
const static string EPSILON = ""; // epsilon is a special terminal stands for empty
const static string END_SYMBOL_TEXT = "$";

// Symbol {type, text}
class Symbol {
  public:
    unsigned int type;
    string text;

    Symbol(): type(TERMINAL_SYMBOL_TYPE), text(EPSILON) {}
    // default is terminal
    Symbol(string te): type(TERMINAL_SYMBOL_TYPE), text(te) {}
    Symbol(unsigned int ty, string te): type(ty), text(te) {}

    static Symbol Epsilon();
    static Symbol EndSymbol();
    static Symbol Terminal(string te);
    static Symbol NonTerminal(string te);

    bool isEpsilon();
    bool isTerminal();
    bool isNonTerminal();

    bool operator==(const Symbol &sym) const;

    string toString();
};
} // namespace fst

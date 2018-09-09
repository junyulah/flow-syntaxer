#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include "unordered_set"

using namespace std;

namespace fst {
const unsigned int TERMINAL_SYMBOL_TYPE = 0; // terminal symbol
const unsigned int NON_TERMINAL_SYMBOL_TYPE = 1; // none terminal symbol
const static string EPSILON = "";
const static string END_SYMBOL_TEXT = "$";

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

class Production {
public:
  Symbol head;
  vector<Symbol> body;

  Production() {}

  // TODO validation
  Production(Symbol h, vector<Symbol> b): head(h), body(b) {}

  // A -> ε
  bool isEpsilonProduction();
  unsigned int getBodyLength();
  Symbol getFirstBody();

  string toString();
};

/**
 * Terminals: the basic symbols from which strings are formed.
 *
 * Nonterminals: syntactic variables that denote sets of strings.
 *
 * start symbol
 *
 * productions: The productions of a grammer specify the manner in which the terminals and nonterminals can be combined to form strings.
 *
 * production:
 *   (1) A nonterminal called the head or left side of the production; this production defines some of the strings denoted by the head.
 *   (2) The symbol ->, sometimes :=
 *   (3) A body or right side consiting of zero or more terminals and nonterminals.
 *
 *
 *   Notational Conventions:
 *   (1) terminals
 *       Lower-case letters early in the alphabet such as a, b, c
 *       Operator symbols such as +, -
 *       Punctuation symbols such as parentheses, comma, etc.
 *       The digits 0, 1, ..., 9
 *       Boldface strings such as id or if
 *   (2) nonterminals
 *       Upper-case letters early in the alphabet such as A, B, C
 *       The letter S, which, when it appears, is usually the start symbol
 *   (3) Upper-case letters late in the alphabet, such as X, Y, Z, represent grammer sumbols. That is either nonterminals or terminals.
 *   (4) Lower-case letters late in the alphabet, chiefly u, v, ..., z, represent strings of terminals.
 *   (5) Lower-case Greek letters, α, β, for example, represent strings of grammer symbols.
 *   (6) if A -> α1, A -> α2, ..., A -> αk are all productions with A on the left, we may write A -> α1 | α2 | ... | αk. We call α1, α2, ..., the alternatives for A.
 *   (7) Unless otherwise stated, the left side of the first production is the start symbol.
 */

class ContextFreeGrammer {
private:
  unordered_map<string, Symbol> symbolMap;
  unordered_map<string, unordered_set<string>> firstSetMap;

  void generateSymbolMap();
  void generateFirstSetMap();
  bool hasSymbolInFirstSet(Symbol first, string txt);
  bool hasEpsilonInFirstSet(Symbol symbol);
  bool insertToFirstSet(Symbol symbol, string txt);
public:
  Symbol start;
  vector<Production> productions;
  unordered_map<string, vector<Production>> productionMap;

  // constructor
  ContextFreeGrammer(Symbol s, vector<Production> p);

  // first set
  unordered_set<string> getFirstSet(vector<Symbol> seq);
  unordered_set<string> getFirstSetOfSymbol(Symbol symbol);

  unordered_map<string, unordered_set<string>> getFirstSetMap();

  string toString();
};
} // namespace fst

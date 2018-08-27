#pragma once

#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

namespace fst {
class Production {
private:
  string head;
  vector<string> body;
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
  string start;
  unordered_set<string> T;
  unordered_set<string> NT;
  vector<Production> productions;

public:
  ContextFreeGrammer(string s, unordered_set<string> t,
                     unordered_set<string> nt, vector<Production> p)
      : start(s), T(t), NT(nt), productions(p) {}
};
} // namespace fst

#pragma once

#include <iostream>
#include <vector>
#include "./symbol.h"

using namespace std;

/*
 * productions: The productions of a grammer specify the manner in which the terminals and nonterminals can be combined to form strings.
 *
 * production:
 *   (1) A nonterminal called the head or left side of the production; this production defines some of the strings denoted by the head.
 *   (2) The symbol ->, sometimes :=
 *   (3) A body or right side consiting of zero or more terminals and nonterminals.
 */

namespace fst {
// A -> B c D
class Production {
public:
  Symbol head;
  vector<Symbol> body;

  Production() = default;

  // TODO validation
  Production(Symbol h, vector<Symbol> b): head(h), body(b) {}

  // A -> ε
  bool isEpsilonProduction();
  unsigned int getBodyLength();
  Symbol getFirstBody();

  string toString();
};
} // namespace fst

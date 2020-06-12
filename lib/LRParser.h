#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include "token.h"
#include "./cfg.h"
#include "./LRAction.h"
#include "./AST.h"

/**
 * LR syntax analysis algorithm
 *
 * input: grammer G's analysis table and string ω
 * output: if ω ϵ L(G), get the bottom-up analysis, otherwise error
 *
 * configuration = [stack, tokens]
 *
 * stack = [S₀X₁S₁...XmSm], Xi ϵ T U N, Si stands for state
 *
 * - init: (S₀, a₁a₂...an$)
 *
 * - assume current configuration is (S₀X₁S₁...Sm, aiai₊₁...an$)
 *
 *   1. if [Sm, ai] = shift S, S = GOTO[Sm, ai], then we got new configuration: (S₀X₁S₁..XmSm ai S, ai₊₁...an$)
 *
 *   2. if action[Sm, ai] = reduce by A → β, |β| = r,then:
 *      S = GOTO[Sm₋r, A];
 *      (S₀X₁S₁...Xm₋rSm₋rAS, aiai₊₁...an$)
 *
 *   3. if action[Sm, ai] = accept, success
 *
 *   4. if action[Sm, ai] = error, error
 */
namespace fst {
class Configuration {
public:
  vector<string> stateStack;
  deque<ftp::Token> tokenBuffer;
  Configuration() = default;
};

class LRParser {
private:
  ContextFreeGrammer cfg;
  ActionTable actionTable;
  GOTOTable gotoTable;
  Configuration configuration;

  LRAction getAction(string state, ftp::Token token);
  string goTo(string state, string symbolType);

  // (S₀X₁S₁..XmSm, aiai₊₁...an$) -> (S₀X₁S₁..XmSm ai S, ai₊₁...an$)
  // S = GOTO(Sm, ai);
  void shift(string state, ftp::Token token);

  // (S₀X₁S₁..XmSm, aiai₊₁...an$) -> (S₀X₁S₁...Xm₋rSm₋rAS, aiai₊₁...an$)
  // A → β, r = |β|
  // S = GOTO(Sm₋r, A)
  void reduce(Production prod);

  void analysis();
public:
  AstNode ast;

  LRParser(ContextFreeGrammer const &c, ActionTable const &a, GOTOTable &gotoTable, string startState);

  void acceptToken(ftp::Token const &token);
  void endToken();
};
};

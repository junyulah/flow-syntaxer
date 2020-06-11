#pragma once

#include <iostream>
#include <vector>
#include "token.h"

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
private:
  vector<string> stateStack;
  vector<ftp::Token> tokenBuffer;
public:
};

class LRParser {
public:
};
};

#pragma once

#include "./cfg.h"
#include "unordered_set"

namespace fst {
const unsigned int LR1_REDUCE_ITEM = 0;
const unsigned int LR1_SHIFT_ITEM = 1;
const unsigned int LR1_WAIT_REDUCE_ITEM = 2;

// LR1 Item
class LR1Item {
public: 
  fst::Production  production;
  unsigned int position;
  Symbol lookahead; // lookahead terminal symbol

  LR1Item() = default;

  /**
   * position in [0, produciton.body.length]
   */
  LR1Item(fst::Production pro, unsigned int pos, string fol): production(pro), position(pos), lookahead(fol) {}

  /**
   * reduce item: [A -> α., b]
   * shift item: [A -> α.aβ, b]
   * wait to reduce item: [A -> α.Bβ, b]
   */
  unsigned int getItemType();

  bool hasNextSymbol();

  // A -> α.Bβ => B
  Symbol getNextSymbol();

  // A -> α.Bβ => β
  vector<Symbol> getNextRestSymbols();

  string getId();

  /**
   * viable prefix
   * LR(1) item [A -> α.β, a] is valid for viable prefix ρ=δα, if:
   *   (1) exists S *=> δAw => δαβw
   *   (2) a if the first letter of w. if w = ε, a = #
   */

  string toString();
};
}; // namespace fst

#pragma once

#include "./cfg.h"
#include "unordered_set"
#include "./LR1Item.h"

namespace fst {
// LR1 Item Set
class LR1ItemSet {
private:
  string id;
public:
  vector<LR1Item> coreItems; // core items. S'-> .S or other position is not 0 items
  // id -> LR1Item
  unordered_map<string, LR1Item> items; // closure

  LR1ItemSet() = default;
  LR1ItemSet(ContextFreeGrammer &cfg, vector<LR1Item> coreItems);

  string getId(); // the id of core LR1 item
  string toString();
  bool isEmpty();
};

// goto function: transfer state from I when meet symbol X.
LR1ItemSet goTo(LR1ItemSet I, Symbol X, ContextFreeGrammer &cfg);
}; // namespace fst

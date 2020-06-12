#pragma once

#include "./cfg.h"
#include "unordered_set"
#include "./LR1ItemSet.h"
#include "./LRAction.h"

namespace fst {
// get LR1 start item
LR1Item getLR1StartItem(ContextFreeGrammer &cfg);

LR1Item getLR1AcceptItem(ContextFreeGrammer &cfg);

// Sets of LR1 Item Set
class LR1CanonicalCollection {
public:
  // {itemSetId: itemSet}
  unordered_map<string, LR1ItemSet> collection;

  // {itemSetId: {symbol: itemSetId}}
  GOTOTable gotoTable;

  // initial canonical state
  LR1ItemSet start;

  LR1CanonicalCollection() = default;
  LR1CanonicalCollection(ContextFreeGrammer &cfg);

  string toString();
};
}; // namespace fst

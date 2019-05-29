#pragma once

#include "./cfg.h"
#include "unordered_set"
#include "./LR1ItemSet.h"

namespace fst {
const static string EXPAND_START_SYMBOL_TEXT = "S'";
// get LR1 start item
LR1Item getLR1StartItem(ContextFreeGrammer &cfg);

// Sets of LR1 Item Set
class LR1CanonicalCollection {
public:
  // {itemSetId: itemSet}
  unordered_map<string, LR1ItemSet> collection;

  // {itemSetId: {symbol: itemSetId}}
  unordered_map<string, unordered_map<string, string>> GOTO_TABLE;

  LR1CanonicalCollection() = default;
  LR1CanonicalCollection(ContextFreeGrammer &cfg);

  string toString();
};
}; // namespace fst

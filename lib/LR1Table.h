#pragma once

#include "./cfg.h"
#include "unordered_set"
#include "./LR1ItemSet.h"
#include "./LR1CanonicalCollection.h"
#include "./LRAction.h"

namespace fst {
class LR1Table {
public:
  // state, symbol, action
  ActionTable actionTable;
  LR1CanonicalCollection C;

  LR1Table(ContextFreeGrammer &cfg);
};
}; // namespace fst

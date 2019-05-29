#pragma once

#include "./cfg.h"
#include "unordered_set"
#include "./LR1ItemSet.h"
#include "./LR1CanonicalCollection.h"

namespace fst {
const unsigned int ACTION_REDUCE = 0;
const unsigned int ACTION_SHIFT = 1;
const unsigned int ACTION_ACCEPT = 2;

class LR1Action {
public:
  int actionType;
  string target;

  LR1Action(): actionType(-1), target("") {}
  LR1Action(int a): actionType(a), target("") {}
  LR1Action(int a, string t):actionType(a), target(t) {}
};

// {itemSetId: {symbolText: action}}
typedef unordered_map<string, LR1Action> ActionMap;
typedef unordered_map<string, ActionMap> ActionTable;

class LR1Table {
public:
  // state, symbol, action
  ActionTable actionTable;
  LR1CanonicalCollection C;

  LR1Table(ContextFreeGrammer &cfg);

  bool isAcceptLR1Item(LR1Item item);
};
}; // namespace fst

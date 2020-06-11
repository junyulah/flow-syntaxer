#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include "unordered_set"
#include "./symbol.h"
#include "./production.h"

using namespace std;

namespace fst {
const static string EXPAND_START_SYMBOL_TEXT = "S'";
class ContextFreeGrammer {
private:
  unordered_map<string, unordered_set<string>> firstSetMap;

  void generateSymbolMap();
  void generateFirstSetMap();
  bool hasSymbolInFirstSet(Symbol first, string txt);
  bool hasEpsilonInFirstSet(Symbol symbol);
  bool insertToFirstSet(Symbol symbol, string txt);
public:
  Symbol start;
  unordered_map<string, Symbol> symbolMap;
  vector<Production> productions;
  unordered_map<string, vector<Production>> productionMap;

  // constructor
  ContextFreeGrammer() = default;
  ContextFreeGrammer(Symbol s, vector<Production> p);

  // first set, A -> a1a2...ak
  unordered_set<string> getFirstSet(vector<Symbol> seq);
  unordered_set<string> getFirstSetOfSymbol(Symbol symbol);

  unordered_map<string, unordered_set<string>> getFirstSetMap();

  string toString();
};
} // namespace fst

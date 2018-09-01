#include "../../lib/LR1.h"
#include "assert.h"
#include <iostream>

// start = S
// S -> id, S -> S + id, S -> ε
fst::ContextFreeGrammer egGrammer1() {
  auto start = fst::Symbol::NonTerminal("S");

  fst::Production p1(start, vector<fst::Symbol>{
    fst::Symbol::Epsilon()
  });
  fst::Production p2(start, vector<fst::Symbol>{
    fst::Symbol::NonTerminal("S"),
    fst::Symbol::Terminal("id")
  });
  fst::Production p3(start, vector<fst::Symbol>{
    fst::Symbol::Terminal("id")
  });

  return fst::ContextFreeGrammer(start, vector<fst::Production>{p1, p2, p3});
}

void testCFGFirstSet() {
  auto g1 = egGrammer1();
  unordered_set<string> r1({"id", fst::EPSILON});
  unordered_set<string> r2({"id"});
  unordered_set<string> r3({fst::EPSILON});

  assert(g1.getFirstSet(vector<fst::Symbol>{g1.start}) == r1);
  assert(g1.getFirstSet(vector<fst::Symbol>{fst::Symbol::Terminal("id")}) == r2);
  assert(g1.getFirstSet(vector<fst::Symbol>{fst::Symbol::Terminal(fst::EPSILON)}) == r3);
}

void testLR1GetItemType() {
  // E -> F id
  auto production = fst::Production(
    fst::Symbol::NonTerminal("E"),

    vector<fst::Symbol>{
      fst::Symbol::NonTerminal("F"),
      fst::Symbol::Terminal("id")
    }
  );

  auto item1 = fst::LR1Item(production, 0, "a");
  auto item2 = fst::LR1Item(production, 1, "a");
  auto item3 = fst::LR1Item(production, 2, "a");

  assert(item1.getItemType() == fst::LR1_WAIT_REDUCE_ITEM);
  assert(item2.getItemType() == fst::LR1_SHIFT_ITEM);
  assert(item3.getItemType() == fst::LR1_REDUCE_ITEM);
}

int main() {
    testCFGFirstSet();
    testLR1GetItemType();
    return 0;
}

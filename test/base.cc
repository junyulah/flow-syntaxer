#include "../lib/LR1Table.h"
#include "assert.h"
#include "vector"
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
  unordered_map<string, unordered_set<string>> r1 = {{"S", {"id", fst::EPSILON}}, {"id", {"id"}}, {fst::EPSILON, {fst::EPSILON}}};
  assert(g1.getFirstSetMap() == r1);
}

void testLR1Closure() {
  auto g1 = egGrammer1();
  cout << fst::LR1ItemSet(g1, vector<fst::LR1Item>{fst::LR1Item(g1.productions[1], 0, fst::END_SYMBOL_TEXT)}).toString() << endl;
  cout << fst::LR1ItemSet(g1, vector<fst::LR1Item>{fst::LR1Item(g1.productions[0], 0, fst::END_SYMBOL_TEXT)}).toString() << endl;
  cout << fst::LR1ItemSet(g1, vector<fst::LR1Item>{fst::LR1Item(g1.productions[2], 0, fst::END_SYMBOL_TEXT)}).toString() << endl;
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

void testLR1Table() {
  cout << "testLR1Table: " << endl;
  auto g1 = egGrammer1();
  auto t = fst::LR1Table(g1);
  cout << t.C.toString() << endl;
}

int main() {
    try {
      testCFGFirstSet();
      testLR1GetItemType();
      testLR1Closure();
      testLR1Table();
    } catch (const char* msg) {
        cerr << msg << endl;
        throw msg;
    }
    
    return 0;
}

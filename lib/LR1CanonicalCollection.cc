#include "./LR1CanonicalCollection.h"

namespace fst {
  // [S' -> .E, $]
  LR1Item getLR1StartItem(ContextFreeGrammer &cfg) {
    auto pro = Production(Symbol(EXPAND_START_SYMBOL_TEXT),
      vector<Symbol>{cfg.start});
    return LR1Item(pro, 0, END_SYMBOL_TEXT);
  }

  LR1CanonicalCollection::LR1CanonicalCollection(ContextFreeGrammer &cfg) {
    // initialize
    auto incrementSet = unordered_map<string, LR1ItemSet>();

    auto s1 = LR1ItemSet(cfg, vector<LR1Item>{
      getLR1StartItem(cfg)
    });

    incrementSet[s1.getId()] = s1;
    this->collection[s1.getId()] = s1;

    // find all states
    while(true) {
        auto newSet = unordered_map<string, LR1ItemSet>();

        // for each LR1ItemSet
        for(auto elem : incrementSet) {
          auto from = elem.second;
          // for each symbol
          for(auto item: cfg.symbolMap) {
            auto to = goTo(from, item.second, cfg);
            if(to.isEmpty()) {
                continue;
            }
            auto id = to.getId();

            // find new state
            if(this->collection.count(id) <= 0) {
              this->collection[to.getId()] = to;
              newSet[to.getId()] = to;
            }

            // record (from, item, to) to table
            this->GOTO_TABLE[from.getId()][item.second.text] = to.getId();
          }
        }

        if(newSet.size() == 0) break;
        incrementSet = newSet;
    }
  }

  string LR1CanonicalCollection::toString() {
    string text = "cannonical";

    for(auto item: this->collection) {
        text += " - " + item.first;
    }

    return text;
  }
};

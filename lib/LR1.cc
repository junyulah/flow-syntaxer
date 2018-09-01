#include "./LR1.h"

namespace fst {
  unsigned int LR1Item::getItemType() {
    // [A -> α., a]
    if(this->position == this->production.body.size()) {
      return fst::LR1_REDUCE_ITEM;
    }

    // [A -> α.aβ, b]
    if(this->getNextSymbol().type == fst::TERMINAL_SYMBOL_TYPE) {
      return fst::LR1_SHIFT_ITEM;
    }

    // [A -> α.Bβ, b]
    return fst::LR1_WAIT_REDUCE_ITEM;
  }

  Symbol LR1Item::getNextSymbol() {
    return this->production.body[this->position];
  }

  vector<Symbol> LR1Item::getNextRestSymbols() {
    vector<Symbol> ret;
    auto len = this->production.getBodyLength();
    for(int i = this->position; i < len; i++) {
        ret.push_back(this->production.body[i]);
    }
    return ret;
  }

  // closure
  LR1ItemSet::LR1ItemSet(ContextFreeGrammer& cfg, vector<LR1Item> is) {
    this->items = is;
    auto prevItems = this->items;

    while(true) {
      vector<LR1Item> newItems;

      // for every item [A -> α.Bβ, a]
      for(auto item = prevItems.begin(); item != prevItems.end(); ++item) {
        auto symbol = item->getNextSymbol(); // B
        if(symbol.type == fst::NON_TERMINAL_SYMBOL_TYPE) {
          auto rmsential = item->getNextRestSymbols(); // β
          rmsential.push_back(item->follow); // βa

          // for every production B -> ρ in cfg
          auto productions = cfg.productionMap[symbol.text];
          for(auto pro = productions.begin(); pro != productions.end(); ++pro) { // ρ
            auto fstSet = cfg.getFirstSet(rmsential);
            // for every terminal b in First(βa)
            // add [B -> .ρ, b] into items
            for(auto b = fstSet.begin(); b != fstSet.end(); ++b) { // b
              newItems.push_back(LR1Item(*pro, 0, *b));
            }
          }
        }
      }

      if(newItems.size() > 0) {
        // concat items
        this->items.insert(this->items.end(), newItems.begin(), newItems.end());
        prevItems = newItems;
      } else {
        // if no more new items, just stop
        break;
      }
    } 
  }
};

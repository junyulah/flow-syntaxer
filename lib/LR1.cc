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

  // TODO escape special situation
  string LR1Item::getId() {
    return "[" + this->production.toString() + "," + to_string(this->position) + "," + this->follow.toString() + "]";
  }

  string LR1Item::toString() {
    return this->getId();
  }

  namespace {
    bool orderLR1ItemCompare(LR1Item item1, LR1Item item2) {
      return item1.getId().compare(item2.getId());
    }
  } 

  // closure
  LR1ItemSet::LR1ItemSet(ContextFreeGrammer& cfg, vector<LR1Item> coreItems): cfg(cfg) {
    std::sort(coreItems.begin(), coreItems.end(), orderLR1ItemCompare);
    this->id = "";

    // initial
    this->coreItems = coreItems;
    for(auto item = coreItems.begin(); item != coreItems.end(); ++item) {
      auto itemId = item -> getId();
      this->items.insert({item -> getId(), *item});
      this->id += itemId;
    }
   
    auto prevItems = this->items;

    while(true) {
      unordered_map<string, LR1Item> newItems;

      // for every item [A -> α.Bβ, a]
      for(auto kv = prevItems.begin(); kv != prevItems.end(); ++kv) {
        auto item = kv->second;
        auto symbol = item.getNextSymbol(); // B
        if(symbol.type == fst::NON_TERMINAL_SYMBOL_TYPE) {
          auto rmsential = item.getNextRestSymbols(); // β
          rmsential.push_back(item.follow); // βa

          // for every production B -> ρ in cfg
          auto productions = cfg.productionMap[symbol.text];
          for(auto pro = productions.begin(); pro != productions.end(); ++pro) { // ρ
            auto fstSet = cfg.getFirstSet(rmsential);
            // for every terminal b in First(βa)
            // add [B -> .ρ, b] into items
            for(auto b = fstSet.begin(); b != fstSet.end(); ++b) { // b
              auto newItem = LR1Item(*pro, 0, *b);
              auto newItemId = newItem.getId();
              // may have repeated item
              if(this->items.find(newItemId) == this->items.end()) {
                newItems.insert({newItem.getId(), newItem});
              }
            }
          }
        }
      }

      if(newItems.size() > 0) {
        // concat new items
        this->items.insert(newItems.begin(), newItems.end());
        prevItems = newItems;
      } else {
        // if no more new items, just stop
        break;
      }
    } 
  }

  string LR1ItemSet::getId() {
    return this->id;
  }

  // toString
  string LR1ItemSet::toString() {
    string text = "";
    for(auto kv = this->items.begin(); kv != this->items.end(); ++kv) {
      text += kv->second.toString() + "\n";
    }
    return text;
  }

  LR1ItemSet goTo(LR1ItemSet I, Symbol X) {
    vector<LR1Item> J;
    // for every item in I, [A -> α.Xβ, a]
    for(auto p = I.items.begin(); p != I.items.end(); ++p) {
      auto item = p->second;
      if(item.getNextSymbol() == X) { // add [A -> αX.β, a]
        J.push_back(LR1Item(item.production, item.position + 1, item.follow.text));
      }
    }
    // return closure of J
    return LR1ItemSet(I.cfg, J);
  }
};

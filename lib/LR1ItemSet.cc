#include "./LR1ItemSet.h"

namespace fst {
  namespace {
    bool orderLR1ItemCompare(LR1Item item1, LR1Item item2) {
      return item1.getId().compare(item2.getId());
    }
  } 

  // closure
  LR1ItemSet::LR1ItemSet(ContextFreeGrammer &cfg, vector<LR1Item> coreItems) {
    std::sort(coreItems.begin(), coreItems.end(), orderLR1ItemCompare);
    this->id = "";

    // initial
    this->coreItems = coreItems;
    for(auto item: coreItems) {
      auto itemId = item.getId();
      this->items.insert({item.getId(), item});
      this->id += itemId;
    }
  
    auto prevItems = this->items;

    while(true) {
      unordered_map<string, LR1Item> newItems;

      // for every item [A -> α.Bβ, a]
      for(auto kv: prevItems) {
        auto item = kv.second;
        if(!item.hasNextSymbol()) {
            continue;
        }

        auto symbol = item.getNextSymbol(); // B
        if(symbol.isNonTerminal()) {
          auto rmsential = item.getNextRestSymbols(); // β
          rmsential.push_back(item.lookahead); // βa

          // for every production B -> ρ in cfg
          auto productions = cfg.productionMap[symbol.text];
          for(auto pro: productions) { // ρ
            // for every terminal b in First(βa)
            // add [B -> .ρ, b] into items
            auto fstSet = cfg.getFirstSet(rmsential); 
            for(auto b: fstSet) { // b
              auto newItem = LR1Item(pro, 0, b);
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
    for(auto kv: this->items) {
      text += kv.second.toString() + "\n";
    }
    return text;
  }
  
  bool LR1ItemSet::isEmpty() {
    return this->coreItems.size() == 0;
  }

  LR1ItemSet goTo(LR1ItemSet I, Symbol X, ContextFreeGrammer &cfg) {
    vector<LR1Item> J;

    // for every item in I, [A -> α.Xβ, a]
    for(auto p: I.items) {
      auto item = p.second;
      if(item.hasNextSymbol() && item.getNextSymbol() == X) { // add [A -> αX.β, a]
        J.push_back(LR1Item(item.production, item.position + 1, item.lookahead.text));
      }
    }

    // return closure of J
    return LR1ItemSet(cfg, J);
  }
};

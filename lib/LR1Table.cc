#include "./LR1Table.h"

namespace fst {
  LR1Table::LR1Table(ContextFreeGrammer &cfg) {
    this->C = LR1CanonicalCollection(cfg);

    this->actionTable = ActionTable();

    for(auto itemSet: this->C.collection) {
        // item = [head, body, dotPosition, lookahead]
        for (auto item: itemSet.second.items) {
            // is accept item
            if(item.second.getId() == getLR1AcceptItem(cfg).getId()) {
                this->actionTable[itemSet.second.getId()][END_SYMBOL_TEXT] = LRAction(ACTION_ACCEPT);
            } else {
                auto t = item.second.getItemType();
                
                if(t == LR1_REDUCE_ITEM) {
                    this->actionTable[itemSet.second.getId()][item.second.lookahead.text] = LRAction(ACTION_REDUCE, item.second.production);
                } else if(t == LR1_SHIFT_ITEM) {
                    if(item.second.hasNextSymbol()) {
                        auto nextSymbolText = item.second.getNextSymbol().text;
                        this->actionTable[itemSet.second.getId()][nextSymbolText] = LRAction(ACTION_SHIFT, C.gotoTable[itemSet.second.getId()][nextSymbolText]);
                    }
                }
            }
        }
    }
  }
};

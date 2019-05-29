#include "./LR1Table.h"

namespace fst {
  LR1Table::LR1Table(ContextFreeGrammer &cfg) {
    this->C = LR1CanonicalCollection(cfg);

    auto eStartItem = getLR1StartItem(cfg);
    this->actionTable = ActionTable();

    for(auto itemSet: this->C.collection) {
        // item = [head, body, dotPosition, lookahead]
        for (auto item: itemSet.second.items) {
            // is accept item
            if(item.second.getId() == eStartItem.getId()) {
                this->actionTable[itemSet.second.getId()][END_SYMBOL_TEXT] = LR1Action(ACTION_ACCEPT);
            } else {
                auto t = item.second.getItemType();
                
                if(t == LR1_REDUCE_ITEM) {
                    this->actionTable[itemSet.second.getId()][item.second.lookahead.text] = LR1Action(ACTION_REDUCE, item.second.production.toString());
                } else if(t == LR1_SHIFT_ITEM) {
                    if(item.second.hasNextSymbol()) {
                        auto nextSymbolText = item.second.getNextSymbol().text;
                        this->actionTable[itemSet.second.getId()][nextSymbolText] = LR1Action(ACTION_SHIFT, C.GOTO_TABLE[itemSet.second.getId()][nextSymbolText]);
                    }
                }
            }
        }
    }
  }
};

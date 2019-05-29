#include "./LR1Item.h"

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

  bool LR1Item::hasNextSymbol() {
    return this->position < this->production.body.size();
  }

  Symbol LR1Item::getNextSymbol() {
    if(!hasNextSymbol()) {
        throw "Don't have next symbol!";
    }
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
    return "[" + this->production.toString() + "," + to_string(this->position) + "," + this->lookahead.toString() + "]";
  }

  string LR1Item::toString() {
    return this->getId();
  }
};

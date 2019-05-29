#include "./production.h"

namespace fst {
  bool Production::isEpsilonProduction() {
    return this->getBodyLength() == 1 && this->body[0].isEpsilon();
  }

  Symbol Production::getFirstBody() {
    return this->body[0];
  }

  unsigned int Production::getBodyLength() {
    return this->body.size();
  }

  string Production::toString() {
    auto text = this->head.toString();
    text += " ->";
    for(auto item = this->body.begin(); item != this->body.end(); ++item) {
        text += " " + item->toString();
    } 
    return text;
  }
};

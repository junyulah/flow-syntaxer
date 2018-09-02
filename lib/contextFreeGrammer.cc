#include "./contextFreeGrammer.h"

namespace fst {
  Symbol Symbol::Terminal(string te) {
    return Symbol(TERMINAL_SYMBOL_TYPE, te);
  }

  Symbol Symbol::NonTerminal(string te) {
    return Symbol(NON_TERMINAL_SYMBOL_TYPE, te);
  }

  Symbol Symbol::Epsilon() {
    return Terminal(EPSILON);
  }

  Symbol Symbol::EndSymbol() {
    return Terminal(END_SYMBOL_TEXT);
  }

  bool Symbol::isEpsilon() {
    return this->type == TERMINAL_SYMBOL_TYPE && this->text == EPSILON;
  }

  bool Symbol::isTerminal() {
    return this->type == TERMINAL_SYMBOL_TYPE;
  }

  bool Symbol::isNonTerminal() {
    return this->type == NON_TERMINAL_SYMBOL_TYPE;
  }

  string Symbol::toString() {
    return this->text;
  }

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

  // TODO validation
  ContextFreeGrammer::ContextFreeGrammer(Symbol s, vector<Production> p) {
    this->start = s;
    this->productions = p;

    // initialize production map
    for(auto production = p.begin(); production != p.end(); ++production) {
      auto headTxt = production->head.text;

      // if not exists, initialize it
      if(this->productionMap.find(headTxt) == this->productionMap.end()) {
          this->productionMap[headTxt] = vector<Production>{};
      }

      this->productionMap[headTxt].push_back(*production);
    }

    this->generateSymbolMap();
    this->generateFirstSetMap();
  }

  void ContextFreeGrammer::generateSymbolMap() {
    this->symbolMap[this->start.text] = this->start;

    for(auto production = this->productions.begin(); production != this->productions.end(); ++production) {
      auto head = production->head;
      auto body = production->body;
      this->symbolMap[head.text] = head;
      for(auto item = body.begin(); item != body.end(); ++item) {
        this->symbolMap[item->text] = *item;
      }
    }
  }

  bool ContextFreeGrammer::hasSymbolInFirstSet(Symbol first, string txt) {
    if(this->firstSetMap[first.text].find(txt) != this->firstSetMap[first.text].end()) {
      return true;
    }
    return false;
  }

  bool ContextFreeGrammer::hasEpsilonInFirstSet(Symbol symbol) {
    return this->hasSymbolInFirstSet(symbol, EPSILON);
  }

  bool ContextFreeGrammer::insertToFirstSet(Symbol symbol, string txt) {
    if(!this->hasSymbolInFirstSet(symbol, txt)) {
      this->firstSetMap[symbol.text].insert(txt);
      return true;
    }
    return false;
  }

  unordered_map<string, unordered_set<string>> ContextFreeGrammer::getFirstSetMap() {
    return this->firstSetMap;
  }

  /**
   * 1) FIRST(X) = {X}; if X is nonterminal symbol
   * 2) FIRST(X) = {a | X -> a...}; x -> ε in P
   *             | {a | X -> a...} U {ε}; x -> ε in P
   * 3) Repeat until no new items.
   * if X -> Y..., Y in VN, FIRST(X) = FIRST(X) U {FIRST(T) - {ε}};
   * if X -> Y1...Yn, Y1...Yi-1 *=> ε
   *    from k = 1 to i - 1
   *    FIRST(X) = FIRST(X) U (FIRST(Yk) - {ε});
   * if Y1...Yn *=> ε, FIRST(X) = FIRST(X) U {ε};
   */
  void ContextFreeGrammer::generateFirstSetMap() {
    // initialize. 1) 2)
    for(auto item = this->symbolMap.begin(); item != this->symbolMap.end(); ++item) {
      auto txt = item->first;
      auto symbol = item -> second;

      if(item->second.isTerminal()) {
        this->firstSetMap[txt].insert(txt);
      } else {
        auto productions = this->productionMap[txt];
        for(auto pro = productions.begin(); pro != productions.end(); ++pro) {
          if(pro->isEpsilonProduction()) {
            this->insertToFirstSet(symbol, EPSILON); // X -> ε
          } else if(pro->getFirstBody().isTerminal()) { // X -> a...
            this->insertToFirstSet(symbol, pro->getFirstBody().text);
          }
        }
      }
    }

    // repeat until no new items. 3)
    while(true) {
      auto count = 0;
      for(auto item = this->symbolMap.begin(); item != this->symbolMap.end(); ++item) {
        auto txt = item->first;
        auto symbol = item -> second;

        if(symbol.isNonTerminal()) {
          auto productions = this->productionMap[txt];
          for(auto pro = productions.begin(); pro != productions.end(); ++pro) {
            if(pro->getFirstBody().isNonTerminal()) {
              auto curIdx = 0;
              auto bodyLen = pro->getBodyLength();
              while(curIdx < bodyLen) {
                auto bodySymbol = pro->body[curIdx];
                auto fstSet = this->firstSetMap[bodySymbol.text];
                // union FIRST(X) = FIRST(X) U {FIRST(Y) - {ε}
                for(auto token = fstSet.begin(); token != fstSet.end(); ++token) {
                   if(*token != EPSILON && this->insertToFirstSet(symbol, *token)) {
                     count++;
                   }
                }
                if(!this->hasEpsilonInFirstSet(bodySymbol)) {
                  break;
                }
                curIdx++;
              }
              if(curIdx == bodyLen) { // Y1...Yi-1 =>* ε
                // FIRST(X) = FIRST(X) U {ε}
                if(this->insertToFirstSet(symbol, EPSILON)) {
                  count++;
                }
              }
            }
          }
        }
      }
      if(count == 0) break;
    }
  }

  // A -> a1a2...ak
  unordered_set<string> ContextFreeGrammer::getFirstSet(vector<Symbol> seq) {
    unordered_set<string> ret;

    for(auto symbol = seq.begin(); symbol != seq.end(); ++ symbol) {
      auto set = this->getFirstSetOfSymbol(*symbol);

      for(auto text = set.begin(); text != set.end(); ++text) {
        if(*text != EPSILON) {
          ret.insert(*text);
        }
      }

      if(set.find(EPSILON) != set.end()) { // has epsilon
        continue;
      } else {
        return ret;
      }
    }

    ret.insert(EPSILON);
    return ret;
  }

  /**
   * FIRST(α) = { a | α *=> a..., a in T } U if a *=> ε, ε
   */
  unordered_set<string> ContextFreeGrammer::getFirstSetOfSymbol(Symbol symbol) {
    return this->firstSetMap[symbol.text];
  }

  string ContextFreeGrammer::toString() {
    auto text = "start symbol: " + this->start.toString() + "\n";
    for(auto pro = this->productions.begin(); pro != this->productions.end(); ++pro) {
      text += pro->toString() + "\n";
    }
    return text;
  }
};

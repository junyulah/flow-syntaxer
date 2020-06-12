#include "./LRParser.h"

namespace fst {
  namespace {
  };

  LRParser::LRParser(ContextFreeGrammer const &c, ActionTable const &a, GOTOTable &gotoTable, string startState) {
    this->cfg = c;
    this->actionTable = a;
    this->gotoTable = gotoTable;
    this->ast = AstNode::initAst(Symbol(NON_TERMINAL_SYMBOL_TYPE, EXPAND_START_SYMBOL_TEXT));
    this->configuration.stateStack.push_back(startState);
  }

  LRAction LRParser::getAction(string state, ftp::Token token) {
    if(this->actionTable[state].find(token.getName()) == this->actionTable[state].end()) {
        throw "not action for " + token.getName();
    }
    return this->actionTable[state][token.getName()];
  }

  string LRParser::goTo(string state, string symbolType) {
    if(this->gotoTable[state].find(symbolType) == this->gotoTable[state].end()) {
        throw "not goto for " + symbolType;
    }
    return this->gotoTable[state][symbolType];
  }

  // (S₀X₁S₁..XmSm, aiai₊₁...an$) -> (S₀X₁S₁..XmSm ai S, ai₊₁...an$)
  // S = GOTO(Sm, ai);
  void LRParser::shift(string state, ftp::Token token) {
      this->configuration.stateStack.push_back(state);
      this->configuration.tokenBuffer.pop_front();
      AstNode::appendToken(this->ast, token);
  }

  // (S₀X₁S₁..XmSm, aiai₊₁...an$) -> (S₀X₁S₁...Xm₋rSm₋rAS, aiai₊₁...an$)
  // A → β, r = |β|
  // S = GOTO(Sm₋r, A)
  // (1) remove r states from stack
  // (2) get new state s by using GOTO table 
  // (3) push new state to stack
  void LRParser::reduce(Production prod) {
    for(int i = 0; i < prod.getBodyLength(); i++) {
      this->configuration.stateStack.pop_back(); // pop state
    }

    auto topState = this->configuration.stateStack.back();

    this->configuration.stateStack.push_back(
      this->goTo(topState, prod.head.text)
    );

    AstNode::reduceAst(this->ast,
        this->ast.children.size() - prod.getBodyLength(), // start position
        this->ast.children.size() - 1, // end position
        prod.head);
  };

  void LRParser::analysis() {
    auto topState = this->configuration.stateStack.back();
    auto nextToken = this->configuration.tokenBuffer.front();

    // look up action
    auto act = this->getAction(topState, nextToken);

    switch (act.actionType) {
      case ACTION_SHIFT:
        this->shift(act.target, nextToken); 
        break;
      case ACTION_REDUCE:
        this->reduce(act.reduceProduction);
        break;
      case ACTION_ACCEPT:
        this->configuration.tokenBuffer.pop_front();
        this->configuration.stateStack.pop_back();
        break;
    }
  }

  void LRParser::acceptToken(ftp::Token const &token) {
    // add token to configuration
    this->configuration.tokenBuffer.push_back(token);
    while (this->configuration.tokenBuffer.size() > 1) { // TODO
      analysis();
    }
  }

  void LRParser::endToken() {
    // check state of the configuration
    this->configuration.tokenBuffer.push_back(ftp::Token(END_SYMBOL_TEXT, ""));
    while (this->configuration.tokenBuffer.size() > 0) {
      analysis();
    }
  }
}

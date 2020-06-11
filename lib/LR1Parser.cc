#include "./LR1Parser.h"

namespace fst {
  LRParser LR1Parser::getLRParser(ContextFreeGrammer &cfg) {
    auto lr1Table = LR1Table(cfg);
    return LRParser(cfg, lr1Table.actionTable, lr1Table.C.gotoTable, lr1Table.C.start.getId());
  }
}; // namespace fst

#pragma once

#include <iostream>
#include "./cfg.h"
#include "./LRParser.h"
#include "./LR1Table.h"

namespace fst {
class LR1Parser {
  public:
    static LRParser getLRParser(ContextFreeGrammer &cfg);
};
};

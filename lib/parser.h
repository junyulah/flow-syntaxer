#pragma once

namespace fst {
/**
 * accept token one by one, when finished, output an AST
 */
class Parser {
public:
  void parseToken(Token token);
};
}; // namespace fst

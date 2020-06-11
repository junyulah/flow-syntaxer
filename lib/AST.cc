#include<string>
#include "./AST.h"

using namespace std;

namespace fst {
  namespace {
    template<typename T>
    std::vector<T> slice(std::vector<T> const &v, int m, int n)
    {
        int lo = m;
        int hi = n;
        int len = v.size();
        if(1 + hi > len) {
          hi = len - 1;
        }

        if(lo > hi) {
    	  std::vector<T> empty; 
          return empty;
        }

    	auto first = v.cbegin() + lo;
    	auto last = v.cbegin() + hi + 1;    

    	std::vector<T> vec(first, last);
    	return vec;
    }

    template<typename T>
    std::vector<T> concat(std::vector<T> const &v1, std::vector<T> const &v2)
    {
        vector<T> v3;
        v3.insert(v3.end(), v1.begin(), v1.end());
        v3.insert(v3.end(), v2.begin(), v2.end());
        return v3;
    }
  };

  AstNode AstNode::initAst(Symbol start) {
    return AstNode(start);
  }

  void AstNode::appendToken(AstNode &ast, ftp::Token token) {
    ast.children.push_back(
      AstNode(
        fst::Symbol(fst::TERMINAL_SYMBOL_TYPE, token.getName()),
        token));
  }

  void AstNode::reduceAst(AstNode &ast, int start, int end, Symbol leftSymbol) {
    auto beta = slice(ast.children, start, end);

    // generate a new middle node, which will hang beta nodes
    auto midNode = AstNode(leftSymbol, ftp::Token("", ""), beta);
    vector<AstNode> mids;
    mids.push_back(midNode);

    // remove from start to end of children
    ast.children = concat(
      concat(
        slice(ast.children, 0, start - 1), 
        mids),
      slice(ast.children, end + 1, ast.children.size() - 1));
  }
};

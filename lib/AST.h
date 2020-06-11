#pragma once

#include <iostream>
#include <unordered_set>
#include <vector>
#include "token.h"
#include "./cfg.h"

using namespace std;

/**
 * derivation: αAβ => αηβ if A -> η.
 *
 * =>*:
 * (1) α =>* α
 * (2) if a =>*β and β=>η, then α =>* η
 *
 * sentential form of G, s =>* α
 *
 * sentence of G: a sentential form with no nonterminals
 *
 * language generated: L(G)
 *
 * leftmost derivations: the leftmost nonterminal in each sentential is always chosen. (=>lm)
 *
 * rightmost derivations(canonical derivations): the rightmost nonterminal is always chosen. (=>rm)
 *
 * eg: E =>lm -E =>lm -(E) =>lm -(E + E) =>lm -(id + E) =>lm -(id + id)
 */

/**
 * reduce production to generate a AST
 *
 * s *rm=> αAω *rm=> αβω
 *
 * reduce from αβω to αAω by A → β
 *
 * current AST:
 *           S
 *        /  |  \
 *       /  / \  \
 *      α    β    ω
 *     / \  / \  / \
 *     ...  ...  ...
 *
 * reduce by A → β
 *
 * result AST:
 *           S
 *        /  |  \
 *       /   A   \
 *      /   / \   \
 *     α     β     ω
 *    / \   / \   / \
 *    ...   ...   ...
 *
 * AST data structure
 * node = {
 *      type: terminal | none-terminal,
 *      symbol,
 *      token,
 *      children: [node]
 * }
 *
 * reduce start point: a token list
 * reduce end point: S → r
 *
 * 1. init AST from a list of token
 *
 * 2. reduce production to expand AST
 */

namespace fst {
class AstNode {
public: 
    Symbol symbol;
    ftp::Token token; // leaf has the token
    vector<AstNode> children;

    AstNode(Symbol s, ftp::Token t, vector<AstNode> c): symbol(s), token(t), children(c) {}

    // initial an ast tree
    static AstNode initAst(Symbol start);
    
    //  add new token to ast
    static void appendToken(AstNode &ast, ftp::Token token);
    
    /**
     * s *rm=> αAω *rm=> αβω
     *
     * reduce from αβω to αAω by A → β
     *
     * @param ast
     * @param start
     * @param end
     * @param leftSymbol
     *
     * @return ast
     *
     * β = ast.children[start] ~ ast.children[end]
     *
     * 1. remove β from ast, replace with A
     * 2. make every elements of β as A's children
     */
    static void reduceAst(AstNode &ast, int start, int end, Symbol leftSymbol);
};
} // namespace fst

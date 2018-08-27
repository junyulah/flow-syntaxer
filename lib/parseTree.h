#pragma once

#include <iostream>
#include <unordered_set>
#include <vector>

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

namespace fst {
} // namespace fst

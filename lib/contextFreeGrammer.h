#pragma once

#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

namespace fst {
class Production {
private:
  string head;
  vector<string> body;
};

class ContextFreeGrammer {
private:
  string start;
  unordered_set<string> T;
  unordered_set<string> NT;
  vector<Production> productions;

public:
  ContextFreeGrammer(string s, unordered_set<string> t,
                     unordered_set<string> nt, vector<Production> p)
      : start(s), T(t), NT(nt), productions(p) {}
};
} // namespace fst

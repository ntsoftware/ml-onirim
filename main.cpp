#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include "card.h"
#include "state.h"

int main() {
  State s;
  auto v = s.draw_n_cards(5);
  std::cout << v << std::endl;
  return 0;
}


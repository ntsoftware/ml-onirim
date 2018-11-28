#pragma once

static const size_t INIT_VALUES[N_COLORS][N_SYMBOLS] = {
  { 9, 4, 3 },
  { 8, 4, 3 },
  { 7, 4, 3 },
  { 6, 4, 3 },
};

class State {
  private:
    std::default_random_engine rng;

    std::vector<Card> draw_pile;

    std::vector<Card> discard_pile;

    std::vector<Card> limbo_pile;

    std::array<int, N_COLORS> n_open_doors;

    std::vector<Card> labyrinth;

  public:
    State() {
      const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

      rng.seed(seed);

      for (size_t i=0; i<N_COLORS; ++i) {
        for (size_t j=0; j<N_SYMBOLS; ++j) {
          for (size_t k=0; k<INIT_VALUES[i][j]; ++k) {
            const Color color = static_cast<Color>(i);
            const Symbol symbol = static_cast<Symbol>(j);
            draw_pile.push_back(Card::make_location(color, symbol));
          }
        }
      }

      for (size_t i=0; i<N_COLORS; ++i) {
        for (size_t j=0; j<N_DOORS; ++j) {
          const Color color = static_cast<Color>(i);
          draw_pile.push_back(Card::make_door(color));
        }
      }

      for (size_t i=0; i<N_NIGHTMARES; ++i) {
        draw_pile.push_back(Card::make_nightmare());
      }

      n_open_doors.fill(0);

      shuffle_deck();
    }

    void shuffle_deck() {
      draw_pile.insert(std::end(draw_pile), std::begin(limbo_pile), std::end(limbo_pile));
      limbo_pile.clear();
      std::shuffle(std::begin(draw_pile), std::end(draw_pile), rng);
    }

    Card draw_card() {
      assert(!draw_pile.empty());
      const Card c = draw_pile.back();
      draw_pile.pop_back();
      return c;
    }

    std::vector<Card> draw_n_cards(const size_t max) {
      assert(!draw_pile.empty());
      const size_t n = std::min(draw_pile.size(), max);
      const auto first = std::end(draw_pile) - n;
      const auto last = std::end(draw_pile);
      std::vector<Card> v(first, last);
      draw_pile.erase(first, last);
      return v;
    }

    void set_aside(const Card& c) {
      assert(c.is_door() || c.is_nightmare());
      limbo_pile.push_back(c);
    }

    friend std::ostream& operator<< (std::ostream&, const State&);
};

std::ostream& operator<< (std::ostream& os, const State& s) {
  os << "draw pile:" << std::endl;
  for (const auto& c : s.draw_pile) {
    os << c << std::endl;
  }
  return os;
}


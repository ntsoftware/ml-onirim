#pragma once

enum {
  N_COLORS = 4,
  N_SYMBOLS = 3,
  N_DOORS = 2,
  N_NIGHTMARES = 10,
};

enum class Color {
  NONE = -1,
  RED = 0,
  BLUE = 1,
  GREEN = 2,
  BROWN = 3,
};

enum class Symbol {
  NONE = -1,
  SUN = 0,
  MOON = 1,
  KEY = 2,
};

class Card {
  private:
    enum class Type {
      LOCATION,
      DOOR,
      NIGHTMARE,
    } _type;

    Color _color;
    Symbol _symbol;

    Card(const Type type, const Color color, const Symbol symbol) :
      _type(type),
      _color(color),
      _symbol(symbol) {}

  public:
    static Card make_location(const Color color, const Symbol symbol) {
      return Card(Type::LOCATION, color, symbol);
    }

    static Card make_door(const Color color) {
      return Card(Type::DOOR, color, Symbol::NONE);
    }

    static Card make_nightmare() {
      return Card(Type::NIGHTMARE, Color::NONE, Symbol::NONE);
    }

    bool is_location() const {
      return _type == Type::LOCATION;
    }

    bool is_door() const {
      return _type == Type::DOOR;
    }

    bool is_nightmare() const {
      return _type == Type::NIGHTMARE;
    }

    Color color() const {
      return _color;
    }

    Symbol symbol() const {
      return _symbol;
    }
};

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[1;37m"
#define ANSI_COLOR_RESET   "\x1b[0m"

std::ostream& operator<< (std::ostream& os, const Color color) {
  switch (color) {
    case Color::NONE:
      return os;
    case Color::RED:
      return os << ANSI_COLOR_RED << "red" << ANSI_COLOR_RESET;
    case Color::BLUE:
      return os << ANSI_COLOR_BLUE << "blue" << ANSI_COLOR_RESET;
    case Color::GREEN:
      return os << ANSI_COLOR_GREEN << "green" << ANSI_COLOR_RESET;
    case Color::BROWN:
      return os << ANSI_COLOR_YELLOW << "brown" << ANSI_COLOR_RESET;
  }
  assert(false);
}

std::ostream& operator<< (std::ostream& os, const Symbol symbol) {
  switch (symbol) {
    case Symbol::NONE:
      return os;
    case Symbol::SUN:
      return os << "sun";
    case Symbol::MOON:
      return os << "moon";
    case Symbol::KEY:
      return os << "key";
  }
  assert(false);
}

std::ostream& operator<< (std::ostream& os, const Card& c) {
  if (c.is_location()) {
    return os << c.color() << " " << c.symbol();
  } else if (c.is_door()) {
    return os << c.color() << " door";
  } else if (c.is_nightmare()) {
    return os << ANSI_COLOR_WHITE << "nightmare" << ANSI_COLOR_RESET;
  } else {
    return os;
  }
}

std::ostream& operator<< (std::ostream& os, const std::vector<Card>& v) {
  os << "[";
  for (size_t i=0; i<v.size(); ++i) {
    if (i == 0) {
      os << v[i];
    } else {
      os << ", " << v[i];
    }
  }
  os << "]";
  return os;
}


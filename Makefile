CXXFLAGS+=-Wall -Werror -std=c++11

all: onirim

onirim: main.cpp card.h state.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	$(RM) onirim


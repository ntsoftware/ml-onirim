CXXFLAGS += -Wall 

all: onirim

onirim: main.cpp card.h state.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	$(RM) onirim


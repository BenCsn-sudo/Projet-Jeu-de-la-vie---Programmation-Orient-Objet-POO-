CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -IComponents -IServices -IIhm -IRules -IGame

COMPONENTS = Components
SERVICES = Services
IHM = Ihm
RULES = Rules
GAME = Game

SRCS = \
    $(wildcard $(COMPONENTS)/*.cpp) \
    $(wildcard $(SERVICES)/*.cpp) \
    $(wildcard $(IHM)/*.cpp) \
    $(wildcard $(RULES)/*.cpp) \
    $(wildcard $(GAME)/*.cpp) \
    main.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = game_of_life

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

mrproper: clean
	rm -f $(TARGET)

.PHONY: all clean mrproper

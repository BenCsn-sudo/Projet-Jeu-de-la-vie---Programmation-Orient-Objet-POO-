CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2

COMPONENTS = Components
SERVICES = Services
IHM = Ihm

SRCS = \
    $(wildcard $(COMPONENTS)/*.cpp) \
    $(wildcard $(SERVICES)/*.cpp) \
    $(wildcard $(IHM)/*.cpp) \
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

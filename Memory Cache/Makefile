CXX := g++
CXXFLAGS := -std=c++11 -Wall
LDFLAGS :=
TARGET := simulator

SRCS := Simulation.cc Memory.cc Cache.cc Set.cc Block.cc AddressDecoder.cc PerformanceCounter.cc
OBJS := $(SRCS:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
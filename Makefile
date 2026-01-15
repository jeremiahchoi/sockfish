# Variables
CXX = g++
CXXFLAGS = -std=c++17 -I./src -O3
TARGET = sockfish

# The 'all' target compiles the code
all: $(TARGET)

$(TARGET): src/main.cpp src/engine.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp src/engine.cpp -o $(TARGET)

# A custom command to compile AND run immediately
run: all
	./$(TARGET)

# Clean up the executable
clean:
	rm -f $(TARGET)
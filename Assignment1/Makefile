# Compiler to use
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++11 -Wall
# Linker flags for GoogleTest
GTEST_LIBS = -lgtest -lgtest_main -pthread

# Targets
all: ascii85 test_ascii85

# Main program
ascii85: ascii85.cpp
	$(CXX) $(CXXFLAGS) -o ascii85 ascii85.cpp

# Unit tests
test_ascii85: test_ascii85.cpp
	$(CXX) $(CXXFLAGS) -o test_ascii85 test_ascii85.cpp $(GTEST_LIBS)

# Clean up compiled files
clean:
	rm -f ascii85 test_ascii85

# Phony targets (not actual files)
.PHONY: all clean
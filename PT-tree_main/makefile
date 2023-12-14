# Compiler
CXX := g++
# Compiler flags with optimization (-O3)
CXXFLAGS := -std=c++11 -Wall -Wextra -O3 -I../IO -I../OBJECT -I../METHOD

# Source files
SRCS := ptMain.cpp ../IO/IO_TEST/inputFile_test.cpp ../IO/input_v1.cpp ../IO/output_v1.cpp ../OBJECT/basis.cpp ../METHOD/PTtree.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Executable name
TARGET := my_program.exe

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	del $(TARGET) $(OBJS)

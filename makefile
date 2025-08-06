CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -O2 -g

OBJDIR = obj
BINDIR = bin
SRCDIR = src

# Find all .cpp files in src/
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# Convert source files in src/ to object files in obj/
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

TARGET = $(BINDIR)/robin

# Create directories as needed
$(shell mkdir -p $(BINDIR) $(OBJDIR))

all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp files from src/ into .o files in obj/
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)

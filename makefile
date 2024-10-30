# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Wreorder -g

# Source files
SOURCES = main.cpp \
          Views/repl.cpp \
          DataRepository/data_repository.cpp \
          Models/City/city.cpp \
          Models/Mayor/mayor.cpp \
          Controllers/City/city_controller.cpp \
          Views/command_decider.cpp \
          Router/router.cpp \
          Router/command_router.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE = exec

# Default target
all: $(EXECUTABLE)

# Rule to link the program
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

# Rule to compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Phony targets
.PHONY: all clean
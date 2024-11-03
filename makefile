# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Wreorder -g

# Source files
SOURCES = main.cpp \
          CommandLineInterface/repl.cpp \
          Models/City/city.cpp \
          Models/Mayor/mayor.cpp \
          Controllers/City/city_controller.cpp \
		  Controllers/Mayor/mayor_controller.cpp \
          CommandLineInterface/command_decider.cpp \
          Services/DataRepository/data_repository.cpp \
          Services/Router/command_router.cpp \
		  Services/services.cpp \
		  Views/City/views_city.cpp \
		  Views/Mayor/views_mayor.cpp \
		  Views/Helpers/city_helpers.cpp 

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
# Variables
PROJ = sun-earth-moon
COMP = g++
VAL = --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck
#CFLAGS = -g -Wall -std=c++11 -pedantic
CFLAGS = -framework OpenGL -framework GLUT -Wno-deprecated

# Sources
#SRC = main.cpp
SRC = main.cpp

# Create object for each SRC file
OBJ = $(SRC:.cpp=.o)

# Create binary with project name
BIN = $(PROJ)

# Special Symbols:
# 	@		Suppresses the command from being printed to the terminal
# 	$@		Name of tag
# 	$^ 		Name of dependency
#   @echo	Prints to the console the message that follows
#	$(NAME)	Calls a variable

# clean the recompile project
default: clean $(BIN)

.PHONY : run   	# Tags as a command that doesn't actually make anything
run: default
	./$(PROJ)

# debug option adds valgrind flags
debug: $(BIN)
	@valgrind $(VAL) ./$(BIN)
	
# Binary depends on Object files
$(BIN): $(OBJ)
	@echo "CC	$@"
	@$(COMP) $(CFLAGS) $^ -o $@

# Object file depends on .cpp file
# -c flag (compiles source files without linking)
%.o: %.cpp
	@echo "CC	$^"
	@$(COMP) $(CFLAGS) -c $^

# Remove object files and binary
clean:
	@echo "RM	*.o"
	@echo "RM	$(BIN)"
	@rm -f -r *.o $(BIN) *.dSYM

# Zip files - cpp, hpp, makefile
zip:
	zip $(PROJ)_Brown_Jason.zip makefile *.cpp *.hpp

# Make command from sample.cpp
# sample:		sample.cpp
# 	g++ -framework OpenGL -framework GLUT sample.cpp -o sample -Wno-deprecated


################################################################################
# SOURCES: 
################################################################################
# Intermediate Makefile Example - Harlan James <waldroha@oregonstate.edu>  <-- Primarily this one
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
# http://mrbook.org/blog/tutorials/make/
# ftp://ftp.gnu.org/old-gnu/Manuals/make-3.79.1/html_chapter/make_2.html
# CS162 Resources - Video - How to Create a Simple Makefile
# CS162 Resources - TA's Makfile Example - Harlan James
# https://www.cs.bu.edu/teaching/cpp/writing-makefiles/



################################################################################
# NOTES
################################################################################
# *dSYM/

# GENERAL FORMAT:
# target: dependencies
# 	action

# -c flag will create an object file (*.o)

# First non-special target is the default. 
# It gets called without choosing a target. e.g - "make"

# Special Symbols:
#     @     Suppresses the command from being printed to the terminal)
#     $@    Name of tag
#     $^    Name of dependency

# % is a wildcard. Anything that ends in ".o" will match this tag, and each
# tag depends on the same matching wildcard, but ending in ".cpp"

# %.o: %.cpp
# 	@echo "CC	$^"
# 	@$(COMP) $(CFLAGS) -c $^

################################################################################
# Optional Version - greater control over dependencies
################################################################################
# Targets
# default: main.o validate.o menu.o fileIO.o
# 	$(COMP) main.o validate.o menu.o fileIO.o -o $(PROJ)

# main.o: main.cpp
# 	$(COMP) $(CFLAGS) main.cpp		

# validate.o: validate.cpp validate.hpp
# 	$(COMP) $(CFLAGS) validate.cpp

# menu.o: menu.cpp menu.hpp
# 	$(COMP) $(CFLAGS) menu.cpp

# fileIO.o: fileIO.cpp fileIO.hpp
# 	$(COMP) $(CFLAGS) fileIO.cpp

# zip Lab02_Brown_Jason.zip makefile *.cpp *.hpp
# zip Lab02_Brown_Jason.zip makefile main.cpp menu.cpp menu.hpp validate.hpp validate.cpp fileIO.hpp fileIO.cpp input.txt
# Define link target.
linkTarget = executable

# Define required libraries.
LIBS = -lSDL2

# Define any flags needed for compilation.
CFLAGS = -std=c++17

# Define object files needed to use
objects = main.o \
		  app.o \
		  $(patsubst %.cpp, %.o, $(wildcard ./src/*.cpp))	

# Define the rebuildable targets.
rebuildables = $(objects) $(linkTarget)

# Rule to perform the build. Basically the command to run in the terminal.
$(linkTarget): $(objects)
	g++ -g -o $(linkTarget) $(objects) $(LIBS) $(CFLAGS)

# Rule to create the .o (object) files. Compiles the .cpp files.
%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)

# Rule to clean the directory. 'make' ...
.PHONEY:
clean:
	rm $(rebuildables)
# Define the link target.
linkTarget = cpp-tracer

# Define needed libraries.
LIBS = -lSDL2

# Define any flags.
CFLAGS = -std=c++17

# Define object files needed to use
objects = main.o \
		  CApp.o \
		  $(patsubst %.cpp, %.o, $(wildcard ./cppTracer/*.cpp))	

# Define the rebuildable targets.
rebuildables = $(objects) $(linkTarget)

# Rule to perform the build.
$(linkTarget): $(objects)
	g++ -g -o $(linkTarget) $(objects) $(LIBS) $(CFLAGS)

# Rule to create the .o (object) files.
%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)

.PHONEY:
clean:
	rm $(rebuildables)
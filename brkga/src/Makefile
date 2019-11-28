# Compiler binary:
CPP= g++

# Recommended compiler flags for speed:
#	OpenMP enabled
#	full binary code optimization
#	full error and warning reports
#	no range checking within BRKGA:
CFLAGS= -O3 -fopenmp -Wextra -Wall -Weffc++ -ansi -pedantic -Woverloaded-virtual -Wcast-align -Wpointer-arith -std=c++11

# Compiler flags for debugging; uncomment if needed:
#	range checking enabled in the BRKGA API
#	OpenMP disabled
#	no binary code optimization
#CFLAGS= -DRANGECHECK -Wextra -Wall -Weffc++ -ansi -pedantic -Woverloaded-virtual -Wcast-align -Wpointer-arith

# Objects:
OBJECTS= SampleDecoder.o main.o

# Load Object
LOAD = load.o

# Targets:
all: main

main: $(OBJECTS)
	$(CPP) $(CFLAGS) $(OBJECTS) -o main

main.o:
	$(CPP) $(CFLAGS) -c main.cpp

SampleDecoder.o:
	$(CPP) $(CFLAGS) -c SampleDecoder.cpp

load: $(LOAD)
	$(CPP) $(CFLAGS) $(LOAD) -o load

load.o:
	$(CPP) $(CFLAGS) -c load.cpp

clean:
	rm -f main $(OBJECTS) load $(LOAD)
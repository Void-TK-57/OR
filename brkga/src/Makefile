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
OBJECTS= SampleDecoder.o main.o instance.o qtps.o

# Targets:
all: main

main: $(OBJECTS)
	$(CPP) $(CFLAGS) $(OBJECTS) -o main

main.o:
	$(CPP) $(CFLAGS) -c main.cpp

SampleDecoder.o:
	$(CPP) $(CFLAGS) -c SampleDecoder.cpp

instance.o:
	$(CPP) $(CFLAGS) -c instance.cpp

qtps.o:
	$(CPP) $(CFLAGS) -c qtps.cpp

clean:
	rm -f main $(OBJECTS)
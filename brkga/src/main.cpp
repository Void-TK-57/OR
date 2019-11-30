#include <iostream>
#include "SampleDecoder.h"
#include "API/MTRand.h"
#include "API/BRKGA.h"
#include "instance.h"
#include "qtps.h"

void show_vector(std::vector<bool> const &input) {
	for (int i = 0; i < input.size(); i++) {
		std::cout << input.at(i) << ' ';
	}
    std::cout << std::endl;
}

// function to show progress
void show_progress(int value, int max_value, int n = 10) {
    // start ====================
    std::cout << "Progress: [";
    for (int i = 0; i < n; i++) {
        if ((i+1)*max_value < value*n) {
            std::cout<<"=";
        } else if (i*max_value < value*n) {
            std::cout<<">";
        } else {
            std::cout<<" ";
        }
    }
    std::cout<<"] ";
    
}

/*0 1 2 3 4 5
0 _ x x x x x 
1 _ _ x x x x
2 _ _ _ x x x
3 _ _ _ _ x x
4 _ _ _ _ _ x
5 _ _ _ _ _ _

*/

// function to get number of chromosomes
int chromosome_size(int n) {
    int sum = 0;
    for (int i = 1; i < n; i++) {
        sum += i;
    }
    return sum;
}

int main(int argc, char* argv[]) {
    // check number of arguments
	if (argc < 2) {
		// Tell user and exit
		std::cout <<"Error: Invalid Number of paramters" << std::endl;;
		return -1;
	} 

    // get qtps problema
    qtps* problem = load( "./../data/" + std::string( argv[1]) + ".txt" );

    const unsigned n = chromosome_size(problem->v);		// size of chromosomes
	const unsigned p = 100;	// size of population
	const double pe = 0.20;		// fraction of population to be the elite-set
	const double pm = 0.10;		// fraction of population to be replaced by mutants
	const double rhoe = 0.70;	// probability that offspring inherit an allele from elite parent
	const unsigned K = 3;		// number of independent populations
	const unsigned MAXT = 2;	// number of threads for parallel decoding
	
	SampleDecoder decoder(problem);			// initialize the decoder
	
	const long unsigned rngSeed = 2;	// seed to the random number generator
	MTRand rng(rngSeed);				// initialize the random number generator
	
	// initialize the BRKGA-based heuristic
	BRKGA< SampleDecoder, MTRand > algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);
	
	unsigned generation = 0;		// current generation
	const unsigned X_INTVL = 100;	// exchange best individuals at every 100 generations
	const unsigned X_NUMBER = 2;	// exchange top 2 best
	const unsigned MAX_GENS = 4000;	// run for 1000 gens

	do {
        // show progress bar
        show_progress(generation, MAX_GENS, 40);
        // show per centage
        float per_centage = ( ( (float) generation) * 100.0 / ( (float) MAX_GENS ) );
        std::cout << per_centage << "%" << std::endl;
        // show fitness
        std::cout << "Best Fitness " << algorithm.getBestFitness() << std::endl;
        
        algorithm.evolve();	// evolve the population for one generation
		
		if((++generation) % X_INTVL == 0) {
			algorithm.exchangeElite(X_NUMBER);	// exchange top individuals
		}
	} while (generation < MAX_GENS);

    std::cout << "====================================================" << std::endl;

    std::cout <<"Best Chromosome: ";
    show_vector( as_boolean( algorithm.getBestChromosome() ) );
    // get number of vertices

	instance* graph = create_instance( algorithm.getBestChromosome() );
    // print graph

    //std::cout << "Graph: " << std::endl;
    //print(graph);

    instance* total = create_instance( problem->v );
    // write graph
    write_graph( create_edges( total ) , create_edges(graph) , "./../output/" + std::string(argv[1]) + ".dot");
    std::cout << "Best Fitness " << algorithm.getBestFitness() << std::endl;
	
	return 0;
}
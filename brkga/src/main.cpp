#include <iostream>
#include "SampleDecoder.h"
#include "API/MTRand.h"
#include "API/BRKGA.h"

void show_vector(std::vector<double> const &input) {
	for (int i = 0; i < input.size(); i++) {
		std::cout << input.at(i) << ' ';
	}
    std::cout << std::endl;
}

// function to show progress
void show_progress(int value, int max_value, int n = 10) {
    // 
    int arrow_draw = 1;
    // start
    std::cout << "Progress: [";
    for (int i = 0; i < n; i++) {
        if (i*max_value < value*n) {
            std::cout<<"=";
        } else if (arrow_draw == 1) {
            std::cout<<">";
            arrow_draw--;
        } else {
            std::cout<<" ";
        }
    }
    std::cout<<"] ";
    
}

int main(int argc, char* argv[]) {
    const unsigned n = 100;		// size of chromosomes
	const unsigned p = 1000;	// size of population
	const double pe = 0.20;		// fraction of population to be the elite-set
	const double pm = 0.10;		// fraction of population to be replaced by mutants
	const double rhoe = 0.70;	// probability that offspring inherit an allele from elite parent
	const unsigned K = 3;		// number of independent populations
	const unsigned MAXT = 2;	// number of threads for parallel decoding
	
	SampleDecoder decoder;			// initialize the decoder
	
	const long unsigned rngSeed = 2;	// seed to the random number generator
	MTRand rng(rngSeed);				// initialize the random number generator
	
	// initialize the BRKGA-based heuristic
	BRKGA< SampleDecoder, MTRand > algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);
	
	unsigned generation = 0;		// current generation
	const unsigned X_INTVL = 100;	// exchange best individuals at every 100 generations
	const unsigned X_NUMBER = 2;	// exchange top 2 best
	const unsigned MAX_GENS = 1000;	// run for 1000 gens

	do {
        // print current generation
        show_progress(generation, MAX_GENS, 20);
        std::cout << (generation*100/MAX_GENS) << "%" << std::endl;
        algorithm.evolve();	// evolve the population for one generation
		
		if((++generation) % X_INTVL == 0) {
			algorithm.exchangeElite(X_NUMBER);	// exchange top individuals
		}
	} while (generation < MAX_GENS);

    std::cout << "====================================================" << std::endl;
    std::cout <<"Best Chromosome: ";
    show_vector(algorithm.getBestChromosome());
    std::cout << "Best Fitness " << algorithm.getBestFitness() << std::endl;
	
	return 0;
}
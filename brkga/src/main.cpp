#include <iostream>
#include "SampleDecoder.h"
#include "API/MTRand.h"
#include "API/BRKGA.h"
#include "instance.h"
#include "qtps.h"
#include <sstream>
#include <chrono>
#include <ctime>

// function to print boolean vector
void print(std::vector<bool> const &input) {
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

// result struct
typedef struct result {
    double time;
    int n_routes;
    int cost;
    int prize;
} result;


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

    // number of instances to test
    int number_instance;
    // if given, update number os instance
    if (argc >= 3) {
        // convert to string
        std::string number = argv[2];
        // create string stream
        std::istringstream iss ( number );
        iss >> number_instance;
    } else {
        number_instance = 1;
    }

    // file
    std::string file = argv[1];

    // get qtps problema
    qtps* problem = load( "./../data/" + file + ".txt" );

    // parameters
    const unsigned n = chromosome_size(problem->v);		// size of chromosomes
	const unsigned p = 300;	// size of population
	const double pe = 0.20;		// fraction of population to be the elite-set
	const double pm = 0.10;		// fraction of population to be replaced by mutants
	const double rhoe = 0.70;	// probability that offspring inherit an allele from elite parent
	const unsigned K = 3;		// number of independent populations
	const unsigned MAXT = 2;	// number of threads for parallel decoding
	const unsigned X_INTVL = 100;	// exchange best individuals at every 100 generations
	const unsigned X_NUMBER = 2;	// exchange top 2 best
	const unsigned MAX_GENS = 6000;	// run for 1000 gens

    // result offstream
    std::ofstream output ("./../output/" + file +".txt");

    output << "Number of instances: " << number_instance << " \n";
	
    // for each instance to check
    for (int i = 0; i < number_instance; i++) {
        SampleDecoder decoder(problem);			// initialize the decoder
	
	    const long unsigned rngSeed = i*7;	// seed to the random number generator
	    MTRand rng(rngSeed);				// initialize the random number generator
    
	    // initialize the BRKGA-based heuristic
	    BRKGA< SampleDecoder, MTRand > algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);
    
	    unsigned generation = 0;		// current generation

        // get start time
        auto start = std::chrono::system_clock::now();

	    do {
            // show progress bar
            show_progress(generation, MAX_GENS, 40);
            // show per centage
            float per_centage = ( ( (float) generation) * 100.0 / ( (float) MAX_GENS ) );
            // print per centage
            std::cout << per_centage << "%" << std::endl;
            // show fitness
            std::cout << "Best Fitness " << algorithm.getBestFitness() << std::endl;
            // envolve algorithm
            algorithm.evolve();	// evolve the population for one generation
            // exchange
	    	if((++generation) % X_INTVL == 0) {
	    		algorithm.exchangeElite(X_NUMBER);	// exchange top individuals
	    	}
	    } while (generation < MAX_GENS);

        // create result
        result r;

        // end time
        auto end = std::chrono::system_clock::now();
        // get time differnece
        std::chrono::duration<double> elapsed_seconds = end-start;
        // get as double
        r.time = elapsed_seconds.count();
        
        std::cout << "====================================================" << std::endl;

        // create graph from best choromosome
	    instance* graph = create_instance( algorithm.getBestChromosome() );

        // get cost prizes
        int* cost_prizes = get_cost_prizes(graph, problem);
        // copy values
        r.cost = cost_prizes[0];
        r.prize = cost_prizes[1];
        delete[] cost_prizes;
        // get total edges
        r.n_routes=  count( as_boolean( algorithm.getBestChromosome() ) );

        // ofstream for result
        output << "============================================================\n";
        // show instance
        output << "Instance: " << i << "\n";
        output << "Total Time: " << r.time << " \n";
        output << "Total Edges: " << r.n_routes << " \n";
        output << "Total Cost: " << r.cost << " \n";
        output << "Total prize: " << r.prize << " \n";
        
        // write graph
        write_graph( create_edges( create_instance( problem->v ) ) , create_edges(graph) , "./../results/" + file + ".dot");

        // delete graph
        delete_instance(graph);
    }
    //close file
    output.close();

    // delete problem
    delete_qtps(problem);

    std::cout << "Done." << std::endl;
    
	
	return 0;
}
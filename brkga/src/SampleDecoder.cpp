/*
 * SampleDecoder.cpp
 *
 *  Created on: Jan 14, 2011
 *      Author: rtoso
 */

#include "SampleDecoder.h"
#include "instance.h"
#include "qtps.h"
#include <math.h>
#include <iostream>

SampleDecoder::SampleDecoder(qtps* p) : problem(p) { }

SampleDecoder::~SampleDecoder() { }

// Runs in \Theta(n \log n):
double SampleDecoder::decode(const std::vector< double >& chromosome) const {
	// convert graph instance
	instance* graph = create_instance(chromosome);

	// total cost
	double cost = 0;
	// total prizes collected
	double prize = 0;

	// for every vertex
	for (int i = 0; i < graph->v; i++) {
		// get number of connection
		int number_of_connections = graph->sizes[i];
		// if number of connections > 0, then the node was visited and add its prize
		if (number_of_connections > 0) { 
			// add its prizes
			prize += problem->prizes[i];
		}
		// for every connection to the other graphs
		for (int j = 0; j < number_of_connections; j++) {
			cost += problem->dist[i][j];
		}
	}

	// get quota
	double quota = get_quota(problem, 0.75);
	
	// if prize is higher then the quota, the
	if (prize < quota) {
		// return infinity
		return INFINITY;
	}

	// check if it is valid
	if ( ! is_valid( graph ) ) {
	 	// return infinity
	 	return INFINITY;
	}

	// sample fitness is the first allele
	return cost;
}

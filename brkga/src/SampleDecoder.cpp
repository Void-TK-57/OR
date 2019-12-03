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

	// convert to graph instance
	instance* graph = create_instance(chromosome);

	// get prize and cost
	int* prize_cost = get_cost_prizes(graph, problem);
	
	// total cost
	double prize = (double) prize_cost[0];
	// total prizes collected
	double cost = (double) prize_cost[1];
	// delete prize_cost
	delete[] prize_cost;
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

	// delete graph
	delete_instance(graph);

	// sample fitness is the first allele
	return cost;
}

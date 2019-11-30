/*
 * SampleDecoder.cpp
 *
 *  Created on: Jan 14, 2011
 *      Author: rtoso
 */

#include "SampleDecoder.h"
#include "instance.h"
#include <iostream>

SampleDecoder::SampleDecoder() { }

SampleDecoder::~SampleDecoder() { }

// Runs in \Theta(n \log n):
double SampleDecoder::decode(const std::vector< double >& chromosome) const {

	
	// sample fitness is the first allele
	return chromosome.front();
}

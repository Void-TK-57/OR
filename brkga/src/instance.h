
#ifndef INSTANCE_H
#define INSTANCE_H


#include <vector>
#include <iostream>
#include <math.h> 
#include <set>
#include <utility>
#include <set>
#include <fstream>
#include "instance.h"

// struct of a instance
typedef struct instance {
    int** map;
    int* sizes;
    int v;
} instance;

typedef std::pair<int, int> edge;
typedef std::set<edge> edges;

// function to create edges from an instance
edges create_edges(instance* );

//function to calculate number of vertices based on total of values
int get_vertices(int);

// function to check if the instance is valid
bool is_valid(instance* graph);

// function to create a instance from a chromosome
instance* create_instance( const std::vector< double >& );

// function to create a fully conncted instance from a number of vertices
instance* create_instance( int);

// function to delete instance
void delete_instance(instance* );

// create a graph from instance in dot language
void write_graph(edges, edges, std::string);

// function to convert chromosome
std::vector<bool> as_boolean(const std::vector< double >& chromosome);

// function to print instance
void print(instance* );

#endif

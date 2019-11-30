
#ifndef INSTANCE_H
#define INSTANCE_H


#include <vector>

// struct of a instance
typedef struct instance {
    std::vector< std::vector< int > > map;
    int v;
} instance;

//function to calculate number of vertices based on total of values
int get_vertices(int);

// function to create a instance from a chromosome
void create_instance( const std::vector< double >& chromosome );

// function to delete instance
void delete_instance(instance* inst);

#endif

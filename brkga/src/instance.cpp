
#include <vector>
#include <iostream>
#include <math.h> 
#include "instance.h"

/* function to calculate number of vertices based on total of values
    base on the formula:
        n(n-1)/2 = v
        n^2 - n -2v = 0
        n = 0.5 + sqrt( 1 + 8v )/ 2
*/

int get_vertices(int n_values) {
    return (1 + ( (int) sqrt(1 + 8*n_values)) )/2;
}

//0 1 2 3 4 5        10 11 12 13 14
/*  0 1 2 3 4 5 6 7 8 9 A B C D E
0 _ x x x x x|x x x x|x x x|x x|x
1 _ _ x x x x
2 _ _ _ x x x
3 _ _ _ _ x x
4 _ _ _ _ _ x
5 _ _ _ _ _ _

 0 1 2
0  x x
1    x
2

n = 6

*/

// function to create a instance from a chromosome
void create_instance( const std::vector< double >& chromosome ) {
    // create instance
    // instance* graph = new instance;
    // number of vertices
    int n = get_vertices(chromosome.size());
    // set vertices
    // graph->v = n;
    // create sizes
    // graph->sizes = new int[n];
    // vector start empty
    std::vector< std::vector< int > > map = {};
    // for each v
    for (int i = 0; i < n; i++) {
        // actual index
        int actual_index = i-1;
        // map for the row
        std::vector< int > row = {};
        // size of the row
        int row_size = n-1;
        // actual row index
        int row_index = 0;
        // while row is before columns i
        while (row_index < i) {
            // check if the value in actual index is higher than 0.5
            if (chromosome.at(actual_index) >= 0.5) {
                // add to row
                row.insert(row.end(), row_index);
            }
            // increase actual index and decrease row sizel
            actual_index += --row_size;
            // increase row index
            row_index++;
            
        }
        // increase actual index and row_index (skip connection from itself)
        actual_index++;
        row_index++;
        // now add the rest of row size
        while (row_size > 0) {
            // check if the value in actual index is higher than 0.5
            if (chromosome.at(actual_index) >= 0.5) {
                // add to row
                row.insert(row.end(), row_index);
            }
            // increase actual index and decrease row sizel
            actual_index++;
            --row_size;
            // increase row index
            row_index++;
        }
        // add row to map
        map.insert(map.end(), row);
        
    }

    // for each vector
    for (int i = 0; i < map.size(); i++) {
        std::vector< int > v = map.at(i);
        std::cout << i << ": [ ";
        for (int j = 0; j < v.size(); j++) {
            std::cout << v.at(j) << " ";
        }
        std::cout << "] " << std::endl;
        
    }
    
    
}

/*
// function to delete instance
void delete_instance(instance* inst) {
    // for each vertices
    for (int i = 0; i < inst->v; i++) {
        delete[] inst->map[i];
    }
    // delete map and sizes
    delete[] inst->map;
    delete[] inst->sizes;
    
}
*/
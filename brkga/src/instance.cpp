
#include <vector>
#include <iostream>
#include <math.h> 
#include <set>
#include <utility>
#include <set>
#include <fstream>
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

n = 6

*/

// function comparatetor of 2 nodes connection


void show_edges(const edges& s) { 
    bool found = false; 
  
    // range-based for loop 
    for (auto const &x : s) { 
        found = true; 
        std::cout << "(" << x.first << ", "
             << x.second << ")"
             << " "; 
    } 
  
    if (not found) { 
        std::cout << "No valid pair\n"; 
    } else {
        std::cout<<std::endl;
    }
} 

// function to check if the instance is valid
bool is_valid(instance* graph) {
    // check sizes (for each node it can only visit at most 1, size == 0 or size == 2)
    for (int i = 0; i < graph->v; i++) {
        if (graph->sizes[i] % 2 != 0 ) {
            // return false
            return(false);
        }
    }
    
    // return true
    return(true);
}

// function to creates edges from instance
edges create_edges(instance* graph) {
    // deges
    edges tuples;
    // for each vertice
	for (int i = 0; i < graph->v; i++) {
        // for each connection
		for (int j = 0; j < graph->sizes[i]; j++) {
            // create edge 
            edge p( std::min(i, graph->map[i][j]), std::max(i, graph->map[i][j]) );
            // add to  set
            tuples.insert(p);
        }
	}
    // return edges
    return tuples;
}

// create a graph from instance in dot language
void write_graph(edges graph, edges tuple, std::string filename) {
    // create file stram
	std::ofstream file (filename);
	// if file was opened, starte writing
	if (file.is_open() ) {
		// add first lines
		file << "// Graph Generated from Load File\ngraph graphname {\n";
		// for each graph
		for (edges::iterator i = graph.begin(); i != graph.end(); ++i) {
            // get edge
            edge p = *i;
            // add to file
            file << "\t" << p.first << " -- " << p.second ;
            // check if the edge is in the selecte tuple
            if ( tuple.count(p) > 0 ) {
                // add the color option
                file << " [color=blue]";
            }
            // end line
            file << ";\n";
        }
		// add end in the file
		file << "}";
		// close file
		file.close();
	} else {
		std::cout << "Error: Could not write to file";
	}

}

// function to print instance
void print(instance* graph) {
    // for each vertices
    for (int i = 0; i < graph->v; i++) {
        std::cout << i << ": [ ";
        // for each vert
        for (int j = 0; j < graph->sizes[i]; j++) {
            std::cout << graph->map[i][j] << " ";
        }
        std::cout<<"]"<<std::endl;
    }
    
}

// function to convert chromosome
std::vector<bool> as_boolean(const std::vector< double >& chromosome) {
    // boolean vector
    std::vector<bool> binary;
    // for each value
    for (int i = 0; i < chromosome.size(); i++) {
        // check if it is higher than 0.5
        if (chromosome.at(i) > 0.5) {
            binary.insert(binary.end(), true);
        } else {
            binary.insert(binary.end(), false);
        }
    }
    // return vector
    return binary;
}

// function to create a instance from a chromosome
instance* create_instance( int n ) {
    // create instance
    instance* graph = new instance;
    // set vertices
    graph->v = n;
    // create sizes
    graph->sizes = new int[n];
    // create map
    graph->map = new int*[n];
    // for each v
    for (int i = 0; i < n; i++) {
        // add n to sizes
        graph->sizes[i] = n-1;
        // create row
        graph->map[i] = new int[n];
        // column index
        int col = 0;
        // for each other vector
        for (int j = 0; j < n; j++) {
            // if i != j
            if (i != j) {
                // then add j to row
                graph->map[i][col++] = j;
            }
        }
    }
    // return graph
    return graph;
}

// function to create a instance from a chromosome
instance* create_instance( const std::vector< double >& chromosome ) {
    // create instance
    instance* graph = new instance;
    // number of vertices
    int n = get_vertices(chromosome.size());
    // set vertices
    graph->v = n;
    // create sizes
    graph->sizes = new int[n];
    // create map
    graph->map = new int*[n];
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
        // get vector
        std::vector<int> v = map.at(i); 
        // add size to sizes
        graph->sizes[i] = v.size();
        // then alocate memory for that vector
        graph->map[i] = new int[graph->sizes[i]]; 
        // for each element in the vector
        for (int j = 0; j < v.size(); j++) {
            graph->map[i][j] = v.at(j);
        }
    }

    // return graph
    return graph;
    
}

// function to delete instance
void delete_instance(instance* graph) {
    // for each vertices
    for (int i = 0; i < graph->v; i++) {
        delete[] graph->map[i];
    }
    // delete map and sizes
    delete[] graph->map;
    delete[] graph->sizes;
    
}

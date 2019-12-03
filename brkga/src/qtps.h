
#ifndef LOAD_H
#define LOAD_H

#include <iostream>
#include <fstream>
#include <string>
#include "instance.h"

// struct of the problem
typedef struct qtps {
	int v;
	int* prizes;
	int** dist;
} qtps;

// function to delete qtps
void delete_qtps(qtps*);

// function to get the total cost prize
int* get_cost_prizes(instance* graph, qtps* p);

// function to get the quota
double get_quota(qtps* problem, double per_centage);

// print function
void print(int number);

// print function
void print(int* numbers, int size);

// print function
void print(int** numbers, int size_m, int size_n);

// print function
void print(std::string message);

// function to generate a graph based on the dot language
void write_graph(int n_vertices, std::string filename);

// function to get vector based on string
int* line_to_numbers(std::string line, int size);

// function to load a qtps
qtps* load(std::string filename);

// main function
int test(int argc, char* argv[]);


#endif
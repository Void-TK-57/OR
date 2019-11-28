#include <iostream>
#include <fstream>
#include <string>

// print function
void print(int number) {
	std::cout<<number<<std::endl;
}

// print function
void print(int* numbers, int size) {
	for (int i = 0; i < size; i++) {
		std::cout<<numbers[i]<<'\t';
	}
	std::cout<<std::endl;
}

// print function
void print(int** numbers, int size_m, int size_n) {
	for (int i = 0; i < size_m; i++) {
		print(numbers[i], size_n);
	}
}

/* print function
void print(char* message) {
	std::cout<<message<<std::endl;
}
*/

// print function
void print(std::string message) {
	std::cout<<message<<std::endl;
}


// function to generate a graph based on the dot language
void write_graph(int n_vertices, std::string filename) {
	// create file stram
	std::ofstream file (filename);
	// if file was opened, starte writing
	if (file.is_open() ) {
		// add first lines
		file << "// Graph Generated from Load File\ngraph {\n";
		// for each pair
		for (int i = 0; i < n_vertices; i++) {
			for (int j = i + 1; j < n_vertices; j++) {
				file << "\t" << std::to_string(i) << " -- " << std::to_string(j) << ";\n";
			}
			
		}
		// add end in the file
		file << "}";
		// close file
		file.close();
	} else {
		std::cout << "Error: Could not write to file";
	}
}

// function to get vector based on string
int* line_to_numbers(std::string line, int size) {
	size_t pos = 0;
	int number, *numbers, i = 0;
	// allocate
	numbers = new int[size];
	// while thre is still numbers
	while ((pos = line.find(' ')) != std::string::npos) {
		// get number
	    number = std::stoi( line.substr(0, pos) );
		
		// add to numbers
		if (i < size) {
			numbers[i++] = number;
		}
		// erase from line
	    line.erase(0, pos + 1);
	}
	// return numbers
	return numbers;
		
}

int main(int argc, char* argv[]) {
	// check number of arguments
	if (argc < 2) {
		// Tell user and exit
		print("Error: Invalid Number of paramters");
		return -1;
	} 
	// else, first create a file stream
	std::ifstream file (argv[1]);
	// line string
	std::string line;

	// number of vertices, prizes and distances
	int n_vertices, *prizes, **distances;

	
	if (file.is_open()) {
		// get first line
		std::getline(file,line);
		// check line
		while (line[0] == '#') std::getline(file,line);

		// get number of vertices
		n_vertices = std::stoi(line);
		
		// get other line
		std::getline(file,line);
		// check line
		while (line[0] == '#') std::getline(file,line);

		// get as numbers
		prizes = line_to_numbers(line, n_vertices);

		// allocate distances
		distances = new int*[n_vertices]; int i = 0;
		
		// while there is still line
  	  	while ( std::getline(file,line) ) {
			// check line
			if (line[0] == '#') continue;
			
			// get numbers of the line
			distances[i++] = line_to_numbers(line, n_vertices);
	
			if (i > 10) break;
		}

  	  	// close file 
		file.close();

		print(n_vertices);
		print(prizes, n_vertices);
		print(distances, n_vertices, n_vertices);
		
	} else {
		// inform User
		print("Error: Unable to open file");
		return -1;
	}
	// set filename to either graph.gv or parameter given
	std::string filename = (argc >= 3) ? argv[2] : "graph.gv";
	// write graph
	write_graph(n_vertices, filename);

	// clear memory
	delete[] prizes;
	for (int i = 0; i < n_vertices;) delete[] distances[i++];
	delete[] distances;
	
	// end function
	return 0;
	
}
#ifndef QTPS_H
#define QTPS_H

// qtps class

class QTPS {
public:

    QTPS(std::string filename);
    ~QTPS();

private:

    unsigned int number_vertices;
    std::vector<unsigned int> prizes;
    unsigned int quota;
    std::vector< std::vector< unsigned int > > costs;
}



#endif
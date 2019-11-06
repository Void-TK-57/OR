#!/usr/bin/python

import sys
import os

# change working directory to the data folder
os.chdir("./../data/")

# main function to read file passed and write a new one in the right format
def main(path):
    # open file
    file = open(path, "r")
    # split path
    path = path.split(".")[0]
    # read header
    header = file.readline()
    # split
    header = header.split(" ")
    # open formated file
    formatted_file = open("./formatted/" + path + ".csv", "w+")
    # add header to the formatted file
    formatted_file.write( "x" + ",x".join([str(i) for i in range( int(header[-2]) ) ] ) + ",p1" + ",p2" + "\n"  )
    # for each line
    for i in range( int( header[-1].rstrip() ) ):
        # read line
        line = file.readline().split(" ")
        # get 2 points
        p1 = int( line[1] )
        p2 = int( line[2].rstrip() )
        # vector of 0s
        zeros = ["0" for _ in range( int(header[-2]) )]
        # change zeros at point index to 1
        zeros[p1-1] = zeros[p2 -1] = "1"
        # add the point to the end
        zeros.append( str(p1) )
        zeros.append( str(p2) )
        # transform to text
        text = ",".join(zeros) + "\n"
        # wrtie to formatted file
        formatted_file.write( text )

    # close formatted file
    formatted_file.close()

    # close file
    file.close()

if __name__ == "__main__":
    # check argv
    if len(sys.argv) <= 1:
        print("[Error] No Args passed ")
    else:
        main(sys.argv[1])
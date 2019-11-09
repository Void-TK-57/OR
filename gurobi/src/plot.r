#!/usr/bin/env Rscript

# load libraries
library("igraph", warn.conflicts=FALSE)

# main function to plot the graph
main <- function(file, vertex_size) {
    # load data
    print(noquote("Loading Data..."))
    data <- read.csv( paste("./../data/formatted/", file, ".csv", sep="") )

    # get columns of first and second points
    p1 <- data$p1
    p2 <- data$p2

    # get coordinates for the igraph function
    coordinates <- as.vector( rbind(p1, p2) )
    # get number of vertices
    n_vertex <- ncol(data)-2
    print(noquote("Creating Graph...") )
    # create graph
    graph <- igraph::graph( edges=coordinates, n = n_vertex, directed = FALSE )

    # file path
    file_path <- paste("./../graphs/", file, ".jpeg", sep="")
    print( noquote( paste("Generating: ", file_path, sep="") ) )
    # create graph jpeg
    jpeg(file_path, width=(13*n_vertex*4)/3, height = 13*n_vertex, quality = 100)
    # plot to the jpeg
    plot(graph, vertex.color="#FFFFFF", vertex.size = vertex_size, vertex.label.color= "#000000" )
}

# get args of the script
args <- commandArgs(trailingOnly=TRUE)
# check args
if (length(args) == 0) {
    print("[Error]: No arguments passed")
} else {
    print(noquote("Reading Input..."))
    # load the input dataframe
    input <- read.csv(paste("./../input/", args[1], sep=""))
    print(input)
    # apply main for each row of the input
    apply(input, 1, function(row) { print(noquote(paste("Solving for: ", row[["file"]], sep =""))); main( row[["file"]], as.numeric(row[["size"]]) )  } )
    print(noquote("Saving..."))
} 
    
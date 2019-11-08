#!/usr/bin/env Rscript

# load libraries
library("igraph", warn.conflicts=FALSE)

# main function to plot the graph
main <- function(file, size) {
    # load data
    print(noquote("Loading Data..."))
    data <- read.csv( paste("./../data/formatted/", file, ".csv", sep="") )

    # get columns of first and second points
    p1 <- data$p1
    p2 <- data$p2

    # get coordinates for the igraph function
    coordinates <- as.vector( rbind(p1, p2) )
    print(noquote("Creating Graph...") )
    # create graph
    graph <- igraph::graph( edges=coordinates, n = ncol(data)-2, directed = FALSE )

    # file path
    file_path <- paste("./../graphs/", file, ".jpeg", sep="")
    print( noquote( paste("Generating: ", file_path, sep="") ) )
    # create graph jpeg
    jpeg(file_path, width=3200, height = 2400, quality = 100)
    # plot to the jpeg
    plot(graph, vertex.color="#FFFFFF", vertex.size = size, vertex.label.cex = size/3 )
    
}

# get args of the script
args <- commandArgs(trailingOnly=TRUE)
# check args
if (length(args) == 0) {
    print("[Error]: No arguments passed")
} else {
    print(noquote("Reading Input..."))
    # load the input dataframe
    input <- read.csv(paste("./../", args[1], sep=""))
    # apply main for each row of the input
    apply(input, 1, function(row) { print(noquote(paste("Solving for: ", row[["file"]], sep =""))); main( row[["file"]], as.numeric(row[["size"]]) )  } )
    print(noquote("Done."))
} 
    
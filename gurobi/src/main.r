#!/usr/bin/env Rscript

# load libraries
library("rjson", warn.conflicts=FALSE)
library("gurobi", warn.conflicts=FALSE)
library("igraph", warn.conflicts=FALSE)
library("dplyr", warn.conflicts=FALSE)


# solve ppl 
create.model <- function(A, obj, rhs, sense, modelsense, vtype) {
    # create model list
    model            <- list()
    model$A          <- A
    model$obj        <- obj
    model$modelsense <- modelsense
    model$rhs        <- rhs
    model$sense      <- sense
    model$vtype      <- vtype
    # create model solved
    model <- gurobi(model, list(OutputFlag = 0))
    # return model
    return(model)
}

# function to get a matrix and points from the dataframe data
filter <- function(data_frame) {
    # number of cols
    number_of_cols <- ncol(data_frame)
    # get the points itself
    p1 <- data_frame$p1
    p2 <- data_frame$p2
    # select the data itself
    data <- dplyr::select(data_frame, -c(number_of_cols, number_of_cols-1))
    # list return
    data_list <- list()
    # set data and points
    data_list$data <- data
    data_list$p1 <- p1
    data_list$p2 <- p2
    # return the data filtered
    return(data_list)
}

# main function
main <- function(file, vertex_size = 15) {
    print( noquote("Reading Data...") )
    # load data
    data <- read.csv( paste("./../data/formatted/", file, ".csv", sep="") )
    # filter data
    data <- filter(data)

    # get restriction matrix
    A <- data.matrix(data$data)
    # get objective
    z <- rep(1, ncol(A) )
    # get rhs
    rhs <- rep(1, nrow(A) )
    # set sense to <=
    sense <- rep('<', nrow(A))

    print( noquote( "Solving...") )
    # create model
    model <- create.model(A, z, rhs, sense, "max", "B")

    # get coordinates
    coordinates <- as.vector( rbind(data$p1, data$p2) )
    
    print( noquote( "Generating Graphs:") )
    # create graph
    graph <- igraph::graph( edges=coordinates, n = ncol(A), directed = FALSE )
    # set independent atribute for the nodes of the graph
    V(graph)$independent <- model$x
    # random colors code and name
    colors <- list("#2ded72", "#36d9cb", "#e8832a", "#963bff", "#ff73b4", "#ff3333")
    names(colors) <- c("Green", "Blue", "Orange", "Purple", "Pink", "Red")
    # path of the folder
    path <- paste("./../results/", file, "/", sep="")
    # create foler
    dir.create(path, showWarnings = FALSE)
    # for each color
    for (color in names(colors) ) {
        # file
        file_name <- paste(file, "-", color, ".jpeg", sep="")
        print( noquote( paste("Generating: ", path, file_name, sep="") ) )
        # create graph jpeg
        jpeg(paste(path, file_name, sep=""))
        # plot to the jpeg
        plot(graph, vertex.color=c( "#FFFFFF", colors[[color]] )[1 + V(graph)$independent], vertex.size = vertex_size, vertex.label.cex = vertex_size/15)
    }
    
}

# get args of the script
args <- commandArgs(trailingOnly=TRUE)
# check args
if (length(args) == 0) {
    print("[Error]: No arguments passed")
} else if (length(args) == 1) {
    main(args[1])
} else if (length(args) == 2) {
    main(args[1], as.numeric( args[2]) )
} else {
    print("[Error]: Invalid number of paramters passed")
}

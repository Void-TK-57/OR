#!/usr/bin/env Rscript

# load json library
library("rjson")
library("gurobi")
library("igraph")


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

# get graph connections coordinates
connection.coordinates <- function(data_frame) {
    # restrictions
    coordinates <- vector()
    # for each row
    for (row in 1:nrow(data_frame) ) {
        # for each col after row
        for (col in row:ncol(data_frame[row, ]) ) {
           # check if has a connection
           if (data_frame[row, col] == 1) {
               coordinates <- c(coordinates, row, col)
           }
        }
    }
    # return coordinates
    return(coordinates)
}

# main function
main <- function(file) {
    data_frame <- read.csv( paste("./../data/formatted/", file, ".csv", sep="") )
    
     # get restriction matriz
    A <- data.matrix(data_frame)
    # get objective
    z <- rep(1, ncol(A) )
    # get rhs
    rhs <- rep(1, nrow(A) )
    # set sense to <=
    sense <- rep('<', nrow(A))

    # create model
    model <- create.model(A, z, rhs, sense, "max", "B")

    print("================================")
    print("X:")
    print(model$x)
    print("================================")
    print("Obj:")
    print(model$objval)
    print("================================")
    return(0)

    
    # create graph
    g <- graph( edges=connection.coordinates(data_frame), n = nrow(A), directed = FALSE )
    # set independent atribute for the nodes of the graph
    V(g)$independent <- model$x
    # create graph jpeg
    jpeg(paste("./../results/", file, ".jpeg", sep=""))
    plot(g, vertex.color=c( "white", "green" )[1 + V(g)$independent])
}

# get args of the script
args <- commandArgs(trailingOnly=TRUE)
# check args
if (length(args) == 0) {
    print("[Error]: No arguments passed")
} else {
    main(args[1])
}

# fucntion to create restriction matrix
restriction.matrix <- function(data_frame) {
    # restrictions
    restrictions <- vector()
    # number of rows
    n_rows <- 0
    # for each row
    for (row in 1:nrow(data_frame) ) {
        # for each col after row
        for (col in row:ncol(data_frame[row, ]) ) {
           # check if has a connection
           if (data_frame[row, col] == 1) {
               # create restriction vector
               restriction <- rep(0, nrow(data_frame))
               # change  restriction at row and col to 1
               restriction[row] <- 1
               restriction[col] <- 1
               # add to restrictions
               restrictions <- c(restrictions, restriction)
               # increase n_rows
               n_rows <- n_rows + 1
           }
        }
    }
    # create as matrix
    restriction_matrix <- matrix(restrictions, nrow = n_rows, ncol =nrow(data_frame), byrow=TRUE)
    # return restriction matrix
    return(restriction_matrix)
}

# functio to load a json file to dataframe
load.json <- function(name, path = "../data/") {
    # get path of the file
    file_path <- paste(path, name, ".json",sep="")
    # load json
    result <- fromJSON(file = file_path)
    # convert to data frame
    data_frame <- as.data.frame(result)
    # change row names
    row.names(data_frame) <- names(data_frame)
    # return the daframe
    return(data_frame )
}
# load json library
library("rjson")

# functio to load a json file to dataframe
load.json <- function(name, path = "../data/") {
    # get path of the file
    file_path <- paste(path, name, sep="")
    # load json
    result <- fromJSON(file = file_path)
    # convert to data frame
    data_frame <- as.data.frame(result)
    # change row names
    row.names(data_frame) <- names(data_frame)
    # return the daframe
    return(data_frame )
}

# main function
main <- function(file) {
    # load json file
    data_frame = load.json(file)
    # print data frmae
    print(data_frame)
}

# get args of the script
args <- commandArgs(trailingOnly=TRUE)
# check args
if (length(args) == 0) {
    print("[Error]: No arguments passed")
} else {
    main(args[1])
}
Database<-setClass(
    "Database",
  
    slots = c(
    dbpath ="character"
    ),
  
    validity=function(object)
    {
        if((length(object@dbpath) < 1) || any(sapply(object@dbpath, is.na)) || any(sapply(object@dbpath, is.null))) {
            return("Invalid Path")
        }
        return(TRUE)
    }
)

setGeneric(name="xapian_inspectDB",
           def=function(DBObj)
           {
             standardGeneric("xapian_inspectDB")
           }
)

setMethod(f="xapian_inspectDB",
          signature="Database",
          definition=function(DBObj)
          {
              info<-inspectDB(DBObj@dbpath)
              cat("UUID =", info[["uuid"]], "\n")
              cat("number of documents =", info[["doccount"]], "\n")
              cat("average document length =", info[["avlength"]], "\n")
              cat("document length lower bound =", info[["doc_low"]], "\n")
              cat("document length upper bound =", info[["doc_up"]], "\n")
              cat("highest document id ever used =", info[["docid"]], "\n")
              cat("has positional information =", info[["hasPos"]], "\n")
          }
)






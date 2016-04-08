xapian_index <- function(dbpath, 
                         datapath, 
                         idField=NULL,
                         indexFields=NULL, 
                         stemmer = c(
                           "none",
                           "english", "en",
                           "danish", "da",
                           "dutch", "nl",
                           "english_lovins", "lovins",
                           "english_porter", "porter",
                           "finnish", "fi",
                           "french", "fr",
                           "german", "de", "german2",
                           "hungarian", "hu",
                           "italian", "it",
                           "kraaij_pohlmann",
                           "norwegian", "nb", "nn", "no",
                           "portuguese", "pt",
                           "romanian", "ro",
                           "russian", "ru",
                           "spanish", "es",
                           "swedish", "sv",
                           "turkish", "tr"))
{
    if (missing(dbpath))
        stop("Database path is not specified")
    if (missing(datapath))
        stop("Datapath is not specified")
    if (missing(idField))
        stop("idField is not specified")
    if (missing(indexFields))
        stop("Fields to be indexed is not specified")
    stemmer <- match.arg(stemmer)
        if (identical(stemmer, "none"))
        stemmer <- NULL 
  
    ##Field Validation
  
    index(dbpath,datapath,idField,indexFields,stemmer);

    new("Database", dbpath = dbpath)
}

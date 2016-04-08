#include <Rcpp.h>
#include <xapian.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
List inspectDB(CharacterVector & dbpath){
  
    std::string pathToDb=as<std::string>(dbpath);
    Xapian::Database db(pathToDb);
  
    std::string uuid=db.get_uuid().c_str();
    int doccount=db.get_doccount();
    int avlength=db.get_avlength();
    int doc_low=db.get_doclength_lower_bound();
    int doc_up=db.get_doclength_upper_bound();
    int docid=db.get_lastdocid();
    bool hasPos=db.has_positions();
  
    return List::create(Named("uuid", uuid),
                        Named("doccount", doccount),
                        Named("avlength", avlength),
                        Named("doc_low", doc_low),
                        Named("doc_up", doc_up),
                        Named("docid", docid),
                        Named("hasPos", hasPos)); 
}

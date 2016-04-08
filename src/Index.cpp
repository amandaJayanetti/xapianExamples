#include <Rcpp.h>
#include <xapian.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "support.h"

using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
void index(CharacterVector & dbpath,CharacterVector & datapath,NumericVector & idField,List & indexFields,CharacterVector & stemmer){
  
    std::string pathToDb=as<std::string>(dbpath);
  
    Xapian::WritableDatabase db(pathToDb, Xapian::DB_CREATE_OR_OPEN);
  
    Xapian::TermGenerator termgenerator;
  
    if(stemmer){
        std::string lang=as<std::string>(stemmer);
        termgenerator.set_stemmer(Xapian::Stem(lang));
    }
  
    std::string pathToData=as<std::string>(datapath);
    ifstream csv(pathToData.c_str());
    vector<string> fields;
    csv_parse_line(csv, fields);
  
    while (csv_parse_line(csv, fields)) {
    
        Xapian::Document doc;
        termgenerator.set_document(doc);
    
        int idCol=as<int>(idField);
        const string & identifier= fields.at(idCol);
        string docString=identifier;
        bool oneElement=true;
        int listPos=0;
    
        for( List::iterator it = indexFields.begin(); it != indexFields.end(); ++it ) {
      
            switch( TYPEOF(*it) ) { 
      
                case VECSXP: {
        
                    Rcpp::List list=it.operator*();
                    int colNo=as<int>(list[0]);
                    std::string prefix=as<std::string>(list[1]);
                    std::string fieldName=as<std::string>(list[2]); 
        
                    const string & field = fields.at(colNo);
                    termgenerator.index_text(field, 1,prefix);
                    docString =+"\n"+field;
                    oneElement=false;
                }
        
                default:{
                    //
                }
            }
        }
    
        if(oneElement){
      
            int colNo=as<int>(indexFields[0]);
            std::string prefix=as<std::string>(indexFields[1]);
            std::string fieldName=as<std::string>(indexFields[2]);  
            const string & field = fields.at(colNo);
      
            termgenerator.index_text(field, 1,prefix);
            docString =+"\n"+field;
      
        }
    
        oneElement=true;
    
        for( List::iterator it = indexFields.begin(); it != indexFields.end(); ++it ) {
        
            switch( TYPEOF(*it) ) { 
            
                case VECSXP: {
                    Rcpp::List list=it.operator*();
                    int colNo=as<int>(list[0]);
                    const string & field = fields.at(colNo);
                    termgenerator.index_text(field);
                    termgenerator.increase_termpos();
                    oneElement=false;
                }
        
                default:{
                    //do nothing
                }
            }
        }
    
        if(oneElement){
      
            int colNo=as<int>(indexFields[0]);
            const string & field = fields.at(colNo);
            termgenerator.index_text(field);
       
        }
    
        doc.set_data(docString);
        string idterm = "Q" + identifier;
        doc.add_boolean_term(idterm);
        db.replace_document(idterm, doc);
  
    }
}


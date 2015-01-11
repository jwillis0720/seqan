//
//  DatabaseIO.cpp
//  seqan_sandbox
//
//  Created by Jordan Willis on 12/6/14.
//
//

#include <seqan/seq_io.h>
#include <iostream>
#include "DatabaseHandler.h"
#include "StructDefs.h"

DatabaseHandler::DatabaseHandler(std::string const &Databasename){
    
    //dbname must be c_string for SeqIO
    dbname = Databasename.c_str();
    
    //Sequence Stream constructor with c_string defined in .h
    seqan::SequenceStream SeqIO(dbname);
    
    //readall sets ids and seqs that were init in .h
    seqan::readAll(ids,seqs,SeqIO);
    
    //Then we set a map called dbcontainer to have all our shit
    for(unsigned i= 0;i< length(seqs);i++){
        dbcontainer[ids[i]] = seqs[i];
    }
}

void DatabaseHandler::print_pretty(){
    for(MapIterator dbiter = dbcontainer.begin(); dbiter != dbcontainer.end(); dbiter++)
        std::cout << dbiter->first << " -> " << dbiter->second << std::endl;
}


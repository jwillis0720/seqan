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

//Constructor
DatabaseHandler::DatabaseHandler(std::string const &Databasename){
    _dbname = Databasename.c_str();
}

void DatabaseHandler::Open(){
    
    //Sequence Stream constructor with c_string defined in .h
    seqan::SequenceStream SeqIO(_dbname);
    
    //readall sets ids and seqs that were init in .h
    _rresult = seqan::readAll(_ids,_seqs,SeqIO);
    
    if (_rresult != 0)
    {
        // Could not read file.
        throw DatabaseHandlerExceptions("Can't Read FASTA File " +
                                        std::string(_dbname) + "\n");
    }
    
    //Then we set a map called dbcontainer to have all our databases
    for(unsigned i= 0;i< length(_seqs);i++){
        _dbcontainer[_ids[i]] = _seqs[i];
    }
}

void DatabaseHandler::PrintPretty()
{
    for(MapIterator dbiter = _dbcontainer.begin(); dbiter != _dbcontainer.end(); dbiter++)
        std::cout << dbiter->first << " -> " << dbiter->second << std::endl;
}

seqan::StringSet<seqan::Dna5String> DatabaseHandler::GetAllSeqs(){
    return _seqs;
};

Tdbcontainer DatabaseHandler::GetDbContainer(){
    return _dbcontainer;
}
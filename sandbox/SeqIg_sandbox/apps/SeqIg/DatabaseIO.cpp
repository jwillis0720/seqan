//
//  DatabaseIO.cpp
//  seqan_sandbox
//
//  Created by Jordan Willis on 12/6/14.
//
//


#include <seqan/seq_io.h>
#include <seqan/sequence.h>
#include <seqan/basic.h>
#include <seqan/align.h>
#include <seqan/modifier.h>
#include <iostream>
#include <fstream>
#include "DatabaseIO.h"
#include "StructDefs.h"

typedef seqan::CharString cs;
typedef seqan::Dna5String ds;
typedef std::map<cs,ds> Tdbcontainer;
typedef Tdbcontainer::const_iterator MapIterator;

Tdbcontainer ReadFastaSetDb(std::string const &filepath){
    seqan::StringSet<seqan::CharString> ids;
    seqan::StringSet<seqan::Dna5String> seqs;
    const char * dbname = filepath.c_str();
    seqan::SequenceStream seqIO(dbname);
    readAll(ids,seqs,seqIO);
    Tdbcontainer dbcontainer;
    for(unsigned i = 0; i< length(seqs); i++)
    {
        dbcontainer[ids[i]] = seqs[i];
    }
    return dbcontainer;
}

void printdb(Tdbcontainer const & container){
    for(MapIterator iter = container.begin(); iter != container.end(); iter++)
        std::cout << iter->first << " " << iter->second << std::endl;
}

bool parseDatabase(DatabasePaths const &db_paths){
    Tdbcontainer VGeneDB = ReadFastaSetDb(db_paths.Vgene_db);
    Tdbcontainer DGeneDB = ReadFastaSetDb(db_paths.Dgene_db);
    Tdbcontainer JGeneDB = ReadFastaSetDb(db_paths.Jgene_db);
    
    printdb(VGeneDB);
    printdb(DGeneDB);
    printdb(JGeneDB);
    
return 1;
}
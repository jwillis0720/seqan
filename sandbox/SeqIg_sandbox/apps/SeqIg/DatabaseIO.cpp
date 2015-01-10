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

using namespace seqan;
bool parseDatabase(DatabasePaths const &db_paths){
    
        seqan::StringSet<seqan::CharString> ids;
        seqan::StringSet<seqan::Dna5String> seqs;
    
        //Sequence Stream Takes a const pointe char
        const char * c = db_paths.Vgene_db.c_str();
        seqan::SequenceStream seqIO(c);
        readAll(ids, seqs, seqIO);
    
    
        Tdbcontainer VGeneDB;
        for(unsigned i = 0; i< length(seqs); i++)
        {
            std::cout << ids[i] << "\t" << seqs[i] << "\n\n\n";
        }
    
        return 1;
}
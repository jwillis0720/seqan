//
//  DatabaseIO.h
//  seqan_sandbox
//
//  Created by Jordan Willis on 12/6/14.
//
//

#ifndef __seqan_sandbox__DatabaseHandler__
#define __seqan_sandbox__DatabaseHandler__

#include <stdio.h>
#include <seqan/sequence.h>
#include "SeqIg.h"
#include "StructDefs.h"


typedef seqan::CharString cs;
typedef seqan::Dna5String ds;
typedef std::map<cs,ds> Tdbcontainer;
typedef Tdbcontainer::const_iterator MapIterator;

class DatabaseHandler {
    private :
        const char * dbname;
        seqan::StringSet<seqan::CharString> ids;
        seqan::StringSet<seqan::Dna5String> seqs;
        Tdbcontainer dbcontainer;
    public:
        DatabaseHandler(std::string const &);
        void print_pretty();
};


#endif /* defined(__seqan_sandbox__DatabaseHandler__) */

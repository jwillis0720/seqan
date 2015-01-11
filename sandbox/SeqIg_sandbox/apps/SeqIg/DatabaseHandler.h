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
        int rresult;
    public:
        DatabaseHandler(std::string const &);
        void open();
        void print_pretty();
};


class DatabaseHandlerExceptions : public std::exception {
    private:
    std::string err_msg;
    
    public:
    DatabaseHandlerExceptions(const std::string msg) : err_msg(msg) {};
        ~DatabaseHandlerExceptions() throw() {};
        const char *what() const throw() { return this->err_msg.c_str(); };
};

#endif /* defined(__seqan_sandbox__DatabaseHandler__) */

//
//  SeqIgUtility.h
//  seqan_sandbox
//
//  Created by Jordan Willis on 1/14/15.
//
//



#ifndef seqan_sandbox_SeqIgUtility_h
#define seqan_sandbox_SeqIgUtility_h
#include <seqan/seq_io.h>
class SeqIgUtility
{
public:
    typedef std::map<seqan::CharString,char> Tcodonmap;
    static Tcodonmap CodonMap;
    static Tcodonmap CreateCodonTable();

};




#endif

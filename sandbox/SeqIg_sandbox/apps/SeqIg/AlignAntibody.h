//
//  AlignAntibody.h
//  seqan_sandbox
//
//  Created by Jordan Willis on 1/11/15.
//
//

#ifndef __seqan_sandbox__AlignAntibody__
#define __seqan_sandbox__AlignAntibody__

#include <stdio.h>
#include <seqan/sequence.h>
#include "DatabaseHandler.h"
#include <seqan/align.h>

class AlignAntibody
{

private:
    //primatives
    bool _verbose;
    int _top_score;
    
    //best alignment holders
    seqan::Dna5String _current_seq;
    seqan::CharString _current_id;
    seqan::CharString _best_gene;
    TAlignmnet _best_align;
    
    //private methods
    void DoPairWiseLocalAgainstDb(seqan::CharString const &,
                                  seqan::Dna5String const &);

public:
    AlignAntibody(seqan::CharString const &,
                      seqan::Dna5String const &,
                      Tdbcontainer const &,
                      bool const &);
    
    //Getters
    int GetTopScore();
    TAlignmnet GetTopAlignment();
    seqan::CharString GetTopGene();
    int GetBeginQueryMatch();
    int GetEndQueryMatch();
    int GetBeginGeneMatch();
    int GetEndGeneMatch();
    
    //For verbose
    void PrintBestAlignment();
};

#endif /* defined(__seqan_sandbox__AlignAntibody__) */

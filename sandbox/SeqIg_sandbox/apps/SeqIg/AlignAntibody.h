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
    seqan::Dna5String current_seq;
    seqan::CharString current_id;
    seqan::CharString best_gene;
    bool _verbose;
    int top_score;
    Tdbcontainer current_container;
    TAlignmnet best_align;
    
    //private methods
    void DoPairWiseLocalAgainstDb(seqan::CharString const &, seqan::Dna5String const &);
    //int findNoverhang(int const &, int const &);

public:
    AlignAntibody(seqan::CharString const &,
                      seqan::Dna5String const &,
                      Tdbcontainer const &,
                      bool const &);
    GeneScores GetBestAlignment();
};

#endif /* defined(__seqan_sandbox__AlignAntibody__) */

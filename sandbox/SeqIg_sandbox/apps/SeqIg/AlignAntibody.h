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
        Tdbcontainer current_container;
        bool _verbose;
        void DoPairWiseLocalAgainstDb(seqan::CharString const &, seqan::Dna5String const &);
        int top_score = -1000;
        seqan::Align<seqan::Dna5String,seqan::ArrayGaps> best_align;

    public:
        AlignAntibody(seqan::CharString const &,
                      seqan::Dna5String const &,
                      Tdbcontainer const &,
                      bool const &);
};

#endif /* defined(__seqan_sandbox__AlignAntibody__) */

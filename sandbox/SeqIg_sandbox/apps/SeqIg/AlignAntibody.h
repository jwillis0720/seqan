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

class AlignAntibody {
    private:
        seqan::Dna5String current_seq;
        seqan::CharString current_id;
    public:
        AlignAntibody(seqan::Dna5String const & , seqan::CharString const &, DatabaseHandler const &);
};

#endif /* defined(__seqan_sandbox__AlignAntibody__) */

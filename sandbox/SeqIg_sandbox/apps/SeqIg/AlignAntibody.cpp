//
//  AlignAntibody.cpp
//  seqan_sandbox
//
//  Created by Jordan Willis on 1/11/15.
//
//

#include "AlignAntibody.h"

AlignAntibody::AlignAntibody(seqan::Dna5String const & seq, seqan::CharString const & id, seqan::StringSet<seqan::Dna5String> const & allseqs){
    current_seq = seq;
    current_id = id;
};
//
//  AntibodyJunction.h
//  seqan_sandbox
//
//  Created by Jordan Willis on 1/14/15.
//
//

#ifndef __seqan_sandbox__AntibodyJunction__
#define __seqan_sandbox__AntibodyJunction__

#include <stdio.h>
#include "AlignAntibody.h"

class AntibodyJunction
{
private:
    //V Gene Members
    TAlignmnet _VGeneAlignment;
    int _VGeneScore;
    seqan::CharString _VGeneGene;
    int _VGeneGeneStart;
    int _VGeneGeneEnd;
    int _VGeneQueryStart;
    int _VGeneQueryEnd;
    
    //D Gene Member
    TAlignmnet _DGeneAlignment;
    int _DGeneScore;
    seqan::CharString _DGeneGene;
    int _DGeneGeneStart;
    int _DGeneGeneEnd;
    int _DGeneQueryStart;
    int _DGeneQueryEnd;

    //J Gene Member
    TAlignmnet _JGeneAlignment;
    int _JGeneScore;
    seqan::CharString _JGeneGene;
    int _JGeneGeneStart;
    int _JGeneGeneEnd;
    int _JGeneQueryStart;
    int _JGeneQueryEnd;
    
    //Newly assigned Variables
    int _VGeneQueryStartTranslation;
    Tds _EntireAntibodySeq;
    
public:
    //V and J
    AntibodyJunction(AlignAntibody &, AlignAntibody &);
    //V D and J
    AntibodyJunction(AlignAntibody &, AlignAntibody &, AlignAntibody &, Tds &);
    ~AntibodyJunction() {};
};

#endif /* defined(__seqan_sandbox__AntibodyJunction__) */

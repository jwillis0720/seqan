//
//  AntibodyJunction.cpp
//  seqan_sandbox
//
//  Created by Jordan Willis on 1/14/15.
//
//

#include "AntibodyJunction.h"

//Constructor One if we have just V and J Gene
AntibodyJunction::AntibodyJunction(AlignAntibody & VGene, AlignAntibody & JGene)
{
    _VGeneAlignment = VGene.GetTopAlignment();
    _JGeneAlignment = JGene.GetTopAlignment();
};

AntibodyJunction::AntibodyJunction(AlignAntibody & VGene, AlignAntibody &JGene,AlignAntibody & DGene, Tds & raw_sequence)
{
    //VGene Members Assignment From AlignAntibody Class
    _VGeneAlignment = VGene.GetTopAlignment();
    _VGeneScore = VGene.GetTopScore();
    _VGeneGene = VGene.GetTopGene();
    _VGeneGeneStart = VGene.GetBeginGeneMatch();
    _VGeneGeneEnd = VGene.GetEndGeneMatch();
    _VGeneQueryStart = VGene.GetBeginGeneMatch();
    _VGeneQueryEnd= VGene.GetEndQueryMatch();
    
    //DGene Members Assignment From AlignAntibody Class
    _DGeneAlignment = DGene.GetTopAlignment();
    _DGeneAlignment = DGene.GetTopAlignment();
    _DGeneScore = DGene.GetTopScore();
    _DGeneGene = DGene.GetTopGene();
    _DGeneGeneStart = DGene.GetBeginGeneMatch();
    _DGeneGeneEnd = DGene.GetEndGeneMatch();
    _DGeneQueryStart = DGene.GetBeginGeneMatch();
    _DGeneQueryEnd= DGene.GetEndQueryMatch();
    
    //JGene Members Assignment From AlignAntibody Class
    _JGeneAlignment = JGene.GetTopAlignment();
    _JGeneAlignment = JGene.GetTopAlignment();
    _JGeneScore = JGene.GetTopScore();
    _JGeneGene = JGene.GetTopGene();
    _JGeneGeneStart = JGene.GetBeginGeneMatch();
    _JGeneGeneEnd = JGene.GetEndGeneMatch();
    _JGeneQueryStart = JGene.GetBeginGeneMatch();
    _JGeneQueryEnd= JGene.GetEndQueryMatch();


    //This will go into its own fuction, but I need to make sure it translates first. It works great for the time being.
    for(int i = _VGeneGeneStart, j = _VGeneQueryStart; i < _VGeneGeneEnd ; i++, j++)
    {
        if(i % 3 == 0)
        {
            _VGeneQueryStartTranslation = j;
            break;
        }
    }

    _EntireAntibodySeq = infix(raw_sequence, _VGeneQueryStartTranslation, _JGeneQueryEnd);
    std::cout << "V Gene Start " << _VGeneQueryStartTranslation << std::endl;;
    std::cout << "Entire Antibody In Frame : " << _EntireAntibodySeq;
    
    
};

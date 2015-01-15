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

    
    if(_VGeneQueryStartTranslation > _JGeneQueryEnd){
        std::cerr << "J gene is becoming before V Gene \n \n";
        throw AntibodyJunctionException("J Gene coming before V Gene for Gene \n");

    }
    _EntireAntibodySeq = infix(raw_sequence, _VGeneQueryStartTranslation, _JGeneQueryEnd);
    std::cout << "V Gene Start " << _VGeneQueryStartTranslation << std::endl;;
    std::cout << "Entire Antibody In Frame : " << _EntireAntibodySeq << std::endl;
    
    //seqan::StringSet<seqan::String<seqan::AminoAcid>, seqan::Owner<seqan::ConcatDirect<> > > aaSeqs;
    //int trans;
    //trans = seqan::translate(aaSeqs,_EntireAntibodySeq);
    
//    for(unsigned int i=0; i < length(_EntireAntibodySeq); i=i+3)
//    {
//        seqan::CharString codon;
//        char amino_acid;
//        codon = seqan::infix(_EntireAntibodySeq,i,i+3);
//        amino_acid = SeqIgUtility::CodonMap[codon];
//        AASequence += amino_acid;
//    }
    
    std::cout << std::endl;
    //std::cout << &aaSeqs << std::endl;
    
};

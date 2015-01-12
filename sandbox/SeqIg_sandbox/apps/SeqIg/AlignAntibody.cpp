//
//  AlignAntibody.cpp
//  seqan_sandbox
//
//  Created by Jordan Willis on 1/11/15.
//
//

#include "AlignAntibody.h"
#include "StructDefs.h"


AlignAntibody::AlignAntibody(seqan::CharString const & id,
                             seqan::Dna5String const & seq,
                             Tdbcontainer const & dbcontainer,
                             bool const & verbose)
{
    current_seq = seq;
    current_id = id;
    current_container = dbcontainer;
    _verbose = verbose;
    
    for(MapIterator dbiter = current_container.begin(); dbiter != current_container.end(); dbiter++)
    {
         seqan::CharString const _gene_id = dbiter->first;
         seqan::Dna5String const _gene_sequence =  dbiter->second;
         AlignAntibody::DoPairWiseLocalAgainstDb(_gene_id,_gene_sequence);
     
    }

    if(_verbose)
    {
        std::cout << "The best score is " << top_score << std::endl;
        std::cout << "The best gene is " << best_gene << std::endl;
        std::cout << "Alignment: \n" << best_align << std::endl;
    }
};

void AlignAntibody::DoPairWiseLocalAgainstDb(seqan::CharString const & _gene_id, seqan::Dna5String const & _gene_sequence)
{
    
    if(!_verbose)
        std::cout << "Aligning Current Sequence: "
        << current_id
        << " To the Database Gene "
        << _gene_id
        << std::endl;
    
        seqan::Align<seqan::Dna5String,seqan::ArrayGaps> align;
        resize(rows(align),2);
        assignSource(row(align,1), _gene_sequence);
        assignSource(row(align,0), current_seq);
    
    int score = globalAlignment(align, seqan::Score<int,seqan::Simple>(0,-1,-1));
        std::cout << score << " " << top_score << "\n";
    
        if(score > top_score){
              top_score = score;
              best_align = align;
            best_gene = _gene_id;
        }
    if(_verbose)
       std::cout << "Score: " << score << ::std::endl;

};


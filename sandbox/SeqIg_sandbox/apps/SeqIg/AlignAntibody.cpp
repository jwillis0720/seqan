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
    top_score = -1000;
    
    
    for(MapIterator dbiter = current_container.begin(); dbiter != current_container.end(); dbiter++)
    {
         seqan::CharString _gene_id = dbiter->first;
         seqan::Dna5String _gene_sequence =  dbiter->second;
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
    
    if(_verbose){
        std::cout << "Aligning Current Sequence: "
        << current_id
        << " To the Database Gene "
        << _gene_id
        << std::endl;
    }
        TAlignmnet align;
        resize(rows(align),2);
        assignSource(row(align,1), _gene_sequence);
        assignSource(row(align,0), current_seq);
    
    //int score = globalAlignment(align, seqan::Score<int,seqan::Simple>(0,-1,-1));
    int score = localAlignment(align, seqan::Score<int>(3,-2,-10,-5));

    //std::cout << score << " " << top_score << "\n";
    
        if(score > top_score){
              top_score = score;
              best_align = align;
              best_gene = _gene_id;
        }
    if(_verbose)
       std::cout << "Score: " << score << ::std::endl;

};

GeneScores AlignAntibody::GetBestAlignment(){
    GeneScores top_score_struct;
    
    if(_verbose)
    {
        std::cout << "The best score is ->" <<top_score << std::endl;
        std::cout << "The best gene is ->" << best_gene << std::endl;
        std::cout << "The best align is ->\n\n" << best_align << std::endl;
        std::cout << "Aligns Query Seq[" << clippedBeginPosition(row(best_align , 0)) << ":" << (clippedEndPosition(row(best_align, 0))-1) << "]";
        std::cout << " and Gene Seq[" << clippedBeginPosition(row(best_align, 1)) << ":" <<  (clippedEndPosition(row(best_align, 1))-1) << "]" << std::endl << std::endl;
    };
    
    top_score_struct.topscore = top_score;
    top_score_struct.topgene = best_gene;
    top_score_struct.align = best_align;
    top_score_struct.begin_query_match = clippedBeginPosition(row(best_align , 1));
    top_score_struct.end_query_match = (clippedEndPosition(row(best_align, 1)), -1);
    top_score_struct.begin_subject_match = clippedBeginPosition(row(best_align , 0));
    top_score_struct.end_subject_match = (clippedEndPosition(row(best_align, 0)) -1);
    //top_score_struct.translate_begin = AlignAntibody::findNoverhang(top_score_struct.begin_query_v_match, top_score_struct.end_query_v_match);
    
        return top_score_struct;
}

//int AlignAntibody::findNoverhang(int const & begin_query_v_match, int const & end_query_v_match)
//{
//    int count = 1;
//    for (int i = begin_query_v_match+1;i < end_query_v_match+1; i++)
//    {
//        if(i%3 == 0 || i == 1){
//            return count;
//        }
//        count ++;
//    }
//    
//    return 0;
//}
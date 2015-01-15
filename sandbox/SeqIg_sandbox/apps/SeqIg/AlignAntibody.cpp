//
//  AlignAntibody.cpp
//  seqan_sandbox
//
//  Created by Jordan Willis on 1/11/15.
//
//

//Project headers
#include "AlignAntibody.h"
#include "StructDefs.h"

//One constructor that does the alignment at time of construction
AlignAntibody::AlignAntibody(seqan::CharString const & id,
                             seqan::Dna5String const & seq,
                             Tdbcontainer const & dbcontainer,
                             bool const & verbose)
{
    //take in references and assign them to member variables
    _current_seq = seq;
    _current_id = id;
    _verbose = verbose;
    
    /*I don't know what this number should be yet, but it should default to something
     that will not return an alignment unless it beats this score */
    _top_score = -1000;
    
    //Iterate through database and do an alignment for each member
    for(MapIterator dbiter = dbcontainer.begin(); dbiter != dbcontainer.end(); dbiter++)
    {
        seqan::CharString _gene_id = dbiter->first;
        seqan::Dna5String _gene_sequence =  dbiter->second;
        //Pass the database gene and id
        AlignAntibody::DoPairWiseLocalAgainstDb(_gene_id,_gene_sequence);
    }
};

//Private method for now, does pairwise local alignment
void AlignAntibody::DoPairWiseLocalAgainstDb(seqan::CharString const & gene_id, seqan::Dna5String const & gene_sequence)
{

    //if verbose, explain output
    if(_verbose)
    {
        std::cout << "Aligning Current Sequence: "
        << _current_id
        << " To the Database Gene "
        << gene_id
        << std::endl;
    }
    
    //Make current alignment
    TAlignmnet align;
    //Will only be two objects
    resize(rows(align),2);
    
    //Gene sequence comes first that was passed in method arguments
    assignSource(row(align,1), gene_sequence);
    //Current sequence comes second that is set as const member variable
    assignSource(row(align,0), _current_seq);
    
    //Where the magic hapens
    //*TODO make score dynamic so the user can input
    int score = localAlignment(align, seqan::Score<int>(3,-2,-10,-5));
    
    //Find best score.
    //*TODO - Return that has these scores sorted so you can get top sequence(s) and not just the top one
    if(score > _top_score)
    {
        _top_score = score;
        _best_align = align;
        _best_gene = gene_id;
    }
    
    if(_verbose)
       std::cout << "Computes Score: " << score << ::std::endl;

};


//GETTERS are all public
int AlignAntibody::GetTopScore(){
    return _top_score;
};

TAlignmnet AlignAntibody::GetTopAlignment()
{
    return _best_align;
}

seqan::CharString AlignAntibody::GetTopGene()
{
    return _best_gene;
}

int AlignAntibody::GetBeginQueryMatch()
{
    return clippedBeginPosition(row(_best_align , 0));
};

int AlignAntibody::GetEndQueryMatch()
{
    return (clippedEndPosition(row(_best_align, 0))-1);
};

int AlignAntibody::GetBeginGeneMatch()
{
    return clippedBeginPosition(row(_best_align , 1));
};

int AlignAntibody::GetEndGeneMatch()
{
    return (clippedEndPosition(row(_best_align, 1))-1);
};


//One last method can print the summary of the alignment for verbose output
void AlignAntibody::PrintBestAlignment (){
    std::cout << "The best score is ->" << _top_score << std::endl;
    std::cout << "The best gene is ->" << _best_gene << std::endl;
    std::cout << "The best align is ->\n\n" << _best_align << std::endl;
    std::cout << "Aligns Query Seq[" << GetBeginQueryMatch() << ":" << GetEndGeneMatch() << "]";
    std::cout << " and Gene Seq[" << GetBeginGeneMatch() << ":" <<  GetEndGeneMatch() << "]" << std::endl;
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
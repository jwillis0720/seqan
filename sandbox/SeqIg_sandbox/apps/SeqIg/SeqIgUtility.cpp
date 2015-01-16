//
//  SeqIgUtility.cpp
//  seqan_sandbox
//
//  Created by Jordan Willis on 1/14/15.
//
//

#include "SeqIgUtility.h"
SeqIgUtility::Tcodonmap SeqIgUtility::CodonMap = SeqIgUtility::CreateCodonTable();
SeqIgUtility::Tcodonmap SeqIgUtility::CreateCodonTable()
{
    std::map<seqan::CharString,char> m;
    m["TTT"] = 'F';
    m["TTC"] = 'F';
    m["TTA"] = 'L';
    m["TTG"] = 'L';
    m["CTT"] = 'L';
    m["CTC"] = 'L';
    m["CTA"] = 'L';
    m["CTG"] = 'L';
    m["ATT"] = 'I';
    m["ATC"] = 'I';
    m["ATA"] = 'I';
    m["ATG"] = 'M';
    m["GTT"] = 'V';
    m["GTC"] = 'V';
    m["GTA"] = 'V';
    m["GTG"] = 'V';
    m["TCT"] = 'S';
    m["TCC"] = 'S';
    m["TCA"] = 'S';
    m["TCG"] = 'S';
    m["CCT"] = 'P';
    m["CCC"] = 'P';
    m["CCA"] = 'P';
    m["CCG"] = 'P';
    m["ACT"] = 'T';
    m["ACC"] = 'T';
    m["ACA"] = 'T';
    m["ACG"] = 'T';
    m["GCT"] = 'A';
    m["GCC"] = 'A';
    m["GCA"] = 'A';
    m["GCG"] = 'A';
    m["TAT"] = 'Y';
    m["TAC"] = 'Y';
    m["TAA"] = '*';
    m["TAG"] = '*';
    m["CAT"] = 'H';
    m["CAC"] = 'H';
    m["CAA"] = 'Q';
    m["CAG"] = 'Q';
    m["AAT"] = 'N';
    m["AAC"] = 'N';
    m["AAA"] = 'K';
    m["AAG"] = 'K';
    m["GAT"] = 'D';
    m["GAC"] = 'D';
    m["GAA"] = 'E';
    m["GAG"] = 'E';
    m["TGT"] = 'C';
    m["TGC"] = 'C';
    m["TGA"] = '*';
    m["TGG"] = 'W';
    m["CGT"] = 'R';
    m["CGC"] = 'R';
    m["CGA"] = 'R';
    m["CGG"] = 'R';
    m["AGT"] = 'S';
    m["AGC"] = 'S';
    m["AGA"] = 'R';
    m["AGG"] = 'R';
    m["GGT"] = 'G';
    m["GGC"] = 'G';
    m["GGA"] = 'G';
    m["GGG"] = 'G';
    return m;
};






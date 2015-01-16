// ==========================================================================
//                                StructDefs.h
// ==========================================================================
// Copyright (c) 2006-2013, Knut Reinert, FU Berlin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Knut Reinert or the FU Berlin nor the names of
//       its contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL KNUT REINERT OR THE FU BERLIN BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ==========================================================================
// Author: Your Name <your.email@example.net>
// ==========================================================================

#include <seqan/align.h>


#ifndef SANDBOX_SEQIG_SANDBOX_APPS_SEQIG_STRUCTDEFS_H_
#define SANDBOX_SEQIG_SANDBOX_APPS_SEQIG_STRUCTDEFS_H_
typedef seqan::CharString Tcs;
typedef seqan::Dna5String Tds;
typedef std::map<Tcs,Tds> Tdbcontainer;
typedef Tdbcontainer::const_iterator MapIterator;
typedef seqan::StringSet<seqan::String<seqan::AminoAcid>, seqan::Owner<seqan::ConcatDirect<> > > TAASeq;

//alignment
typedef seqan::Align<seqan::Dna5String,seqan::ArrayGaps> TAlignmnet;

//Set by ArgParser in main method
struct SeqIgOptions
{
    std::string database_path;
    std::string chain;
    std::string receptor;
    std::string species;
    std::string input_file;
    bool verbose;
};

//The database paths are computed and set in main
struct DatabasePaths
{
    std::string Vgene_db;
    std::string Vgene_family;
    std::string Dgene_db;
    std::string Jgene_db;
    std::map <std::string,std::string> Vgene_files; 
};


#endif  // #ifndef SANDBOX_SEQIG_SANDBOX_APPS_SEQIG_STRUCTDEFS_H_

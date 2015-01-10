// ==========================================================================
//                                   SeqIg
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

#include <seqan/basic.h>
#include <seqan/sequence.h>
#include <seqan/arg_parse.h>
#include "DatabaseIO.h"
#include "SeqIg.h"
#include "StructDefs.h"

void setUpArgumentParser(seqan::ArgumentParser & parser) {
    setAppName(parser, "SeqIg");
    setShortDescription(parser, "SeqIg - Immunoglobulin Germline Gene Assignment");
    setCategory(parser, "Database Locations");
    setDate(parser, "December 2014");
    
    //Database Options
    addOption(parser, seqan::ArgParseOption("d","database_path",
                                            "The database path", seqan::ArgParseArgument::STRING));
    addOption(parser, seqan::ArgParseOption("r","receptor",
                                            "The receptor type", seqan::ArgParseArgument::STRING));
    addOption(parser, seqan::ArgParseOption("c","chain",
                                            "The chain type", seqan::ArgParseArgument::STRING));
    addOption(parser, seqan::ArgParseOption("s","species",
                                            "The species type", seqan::ArgParseArgument::STRING));
    
    //Set Database Default Values
    setDefaultValue(parser, "database_path","/Users/jordanwillis/Git_repos/pyig/data_dir");
    setDefaultValue(parser, "receptor","Ig");
    setDefaultValue(parser, "chain","heavy");
    setDefaultValue(parser, "species","human");
    
}

              
seqan::ArgumentParser::ParseResult extractOptions(seqan::ArgumentParser const & parser, SeqIgOptions & options) {
    bool stop = false;
    
    //getOptionvalue sets structure in place
    getOptionValue(options.database_path, parser, "database_path");
    getOptionValue(options.receptor,parser, "receptor");
    getOptionValue(options.chain, parser, "chain");
    getOptionValue(options.species, parser, "species");
    
    return (stop) ? seqan::ArgumentParser::PARSE_ERROR : seqan::ArgumentParser::PARSE_OK;
}


void setDatabaseFastas(SeqIgOptions const &options, DatabasePaths &dbpaths){
    std::string top_leve_dir =  options.database_path + "/" + options.receptor + "/" +options.chain + "/" + options.species + "/" + options.species;
    dbpaths.Vgene_db = top_leve_dir +  "_gl_V.fasta";
    dbpaths.Dgene_db = top_leve_dir +  "_gl_D.fasta";
    dbpaths.Jgene_db = top_leve_dir +  "_gl_J.fasta";
};

int main(int argc, char const ** argv)
{
    // Parse the command line.
    seqan::ArgumentParser parser;
    
    //structs
    SeqIgOptions options;
    DatabasePaths dbpaths;
    
    
    setUpArgumentParser(parser);
    seqan::ArgumentParser::ParseResult res = parse(parser, argc, argv);
    if (res != seqan::ArgumentParser::PARSE_OK)
        return res == seqan::ArgumentParser::PARSE_ERROR;
    
    res = extractOptions(parser, options);
    if (res != seqan::ArgumentParser::PARSE_OK)
        return res == seqan::ArgumentParser::PARSE_ERROR;
    
    setDatabaseFastas(options, dbpaths);
    
    bool rtd = parseDatabase(dbpaths);
        if(!rtd){
            std::cerr << "Fatal Error: Problem with database " << options.database_path << "\n";
            return 1;
        }
    return 0;
}

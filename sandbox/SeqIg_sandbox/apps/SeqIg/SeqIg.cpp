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
// Author: Your Name jwillis0720@gmail.com>
// ==========================================================================

#include <seqan/basic.h>
#include <seqan/seq_io.h>
#include <seqan/sequence.h>
#include <seqan/arg_parse.h>
#include "DatabaseHandler.h"
#include "SeqIg.h"
#include "StructDefs.h"
#include "AlignAntibody.h"

inline bool check_if_dir_exists (const std::string &name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

void setUpArgumentParser(seqan::ArgumentParser & parser) {
    setAppName(parser, "SeqIg");
    setShortDescription(parser, "SeqIg - Immunoglobulin Germline Gene Assignment");
    setCategory(parser, "Database Locations");
    setDate(parser, "December 2014");
    
    
    //Database Options
    addSection(parser, "Sample Options");
    addOption(parser, seqan::ArgParseOption("d","database_path",
                                            "The database path", seqan::ArgParseOption::STRING));
    addOption(parser, seqan::ArgParseOption("r","receptor",
                                            "The receptor type", seqan::ArgParseOption::STRING));
    addOption(parser, seqan::ArgParseOption("c","chain",
                                            "The chain type", seqan::ArgParseOption::STRING));
    addOption(parser, seqan::ArgParseOption("s","species",
                                            "The species type", seqan::ArgParseOption::STRING));
    
    addSection(parser, "Other Options");
    addOption(parser, seqan::ArgParseOption("v","verbose","Verbose Output"));
    
    addSection(parser, "Input Options");
    addOption(parser, seqan::ArgParseOption("f","input_file",
                                            "The input file to be considered",seqan::ArgParseOption::INPUTFILE));
    //Set Valid Values
    setValidValues(parser, "receptor", "Ig TCR");
    setValidValues(parser, "chain", "heavy lambda kappa");
    setValidValues(parser, "species", "human mouse rat llama rhesus");
    
    //Set required - This should be an argument, but working with all options is so much easier, and I'm a madman
    setRequired(parser, "f");
    
    //Set Database Default Values
    setDefaultValue(parser, "database_path","/Users/jordanwillis/Git_repos/pyig/data_dir");
    setDefaultValue(parser, "receptor", "Ig");
    setDefaultValue(parser, "chain", "heavy");
    setDefaultValue(parser, "species", "human");
}

              
seqan::ArgumentParser::ParseResult extractOptions(seqan::ArgumentParser const & parser, SeqIgOptions & options) {
    
    //getOptionvalue sets structure in place
    bool rdp = getOptionValue(options.database_path, parser, "database_path");
    bool rr = getOptionValue(options.receptor,parser, "receptor");
    bool rc = getOptionValue(options.chain, parser, "chain");
    bool rs = getOptionValue(options.species, parser, "species");
    
    //bool options
    options.verbose = isSet(parser,"verbose");
    
    //getinput options
    bool rfn = getOptionValue(options.input_file,parser,"input_file");
    
    if(!check_if_dir_exists(options.database_path)){
        std::cerr << "\n Can't find database path " << options.database_path << std::endl;
        return seqan::ArgumentParser::PARSE_ERROR;
    }
    
    if(!rdp || !rr || !rc || !rs){
        std::cerr << "\n Problem loading databases" << std::endl;
        return seqan::ArgumentParser::PARSE_ERROR;
    }
    
    if(!rfn){
        std::cerr << "\n Problem with input file" << std::endl;
        return seqan::ArgumentParser::PARSE_ERROR;
    }
    
    return seqan::ArgumentParser::PARSE_OK;
}


void setDatabaseFastas(SeqIgOptions const &options, DatabasePaths &dbpaths){
    std::string top_leve_dir =  options.database_path + "/" + options.receptor + "/" +options.chain + "/" + options.species + "/" + options.species;
    dbpaths.Vgene_db = top_leve_dir +  "_gl_V.fasta";
    dbpaths.Dgene_db = top_leve_dir +  "_gl_D.fasta";
    dbpaths.Jgene_db = top_leve_dir +  "_gl_J.fasta";
};

int main(int argc, char const ** argv)
{
    
    //structs
    SeqIgOptions options;
    DatabasePaths dbpaths;
    
    
    // Parse the command line.
    seqan::ArgumentParser parser;
    setUpArgumentParser(parser);
    parse(parser, argc, argv);
    seqan::ArgumentParser::ParseResult res = extractOptions(parser, options);
    
    //check that the parser didn't blow it
    if (res != seqan::ArgumentParser::PARSE_OK)
    {
        std::cerr << "\n Problem parsing arguments \n" << std::endl;
        return 1;
    }
    
    setDatabaseFastas(options, dbpaths);
    DatabaseHandler VGeneDB(dbpaths.Vgene_db);
    DatabaseHandler JGeneDB(dbpaths.Jgene_db);
    
    try {
        VGeneDB.open();
        if(options.verbose)
        {
            std::cout << "Loading DB at -> " << dbpaths.Vgene_db << std::endl;
            VGeneDB.print_pretty();
        }
    }catch(DatabaseHandlerExceptions &msg){
            std::cerr << "Couldn't open Database" << std::endl;
            std::cerr << msg.what();
            return 1;
    }
    
    try {
        JGeneDB.open();
        if(options.verbose)
        {
            std::cout << "Loading DB at -> " << dbpaths.Jgene_db << std::endl;
            JGeneDB.print_pretty();
        }
    }catch(DatabaseHandlerExceptions &msg){
        std::cerr << "Couldn't open Database" << std::endl;
        std::cerr << msg.what();
        return 1;
    }

    if(options.chain == "heavy")
    {
        DatabaseHandler DGeneDB(dbpaths.Dgene_db);
        try {
            DGeneDB.open();
            if(options.verbose)
            {
                std::cout << "Loading DB at -> " << dbpaths.Dgene_db << std::endl;
                DGeneDB.print_pretty();
            }
        }catch(DatabaseHandlerExceptions &msg) {
            std::cerr << "Couldn't open Database" << std::endl;
            std::cerr << msg.what();
            return 1;
        }
    }
    
    const char * input_file = options.input_file.c_str();
    seqan::CharString id;
    seqan::Dna5String seq;
    seqan::SequenceStream seqStream(input_file);
    
    
    ///Containers i.e.maps
    Tdbcontainer VGeneContainer = VGeneDB.GetDbContainer();
    Tdbcontainer JGeneContainer = JGeneDB.GetDbContainer();
    
    if (!isGood(seqStream))
    {
        std::cerr << "ERROR: Could not open the file " << input_file << "\n";
        return false;
    }
    
    while (!atEnd(seqStream))
    {
        if (readRecord(id, seq, seqStream) != 0)
        {
            std::cerr << "ERROR: Could not read from " << input_file << "\n";
            return false;
        }
        
        //Align V Gene
        AlignAntibody VGeneAlign(id, seq, VGeneContainer, options.verbose);
        if (options.verbose)
            VGeneAlign.PrintBestAlignment();
        
        //Align J Gene
        AlignAntibody JGeneAlign(id, seq, JGeneContainer, options.verbose);
        if(options.verbose)
            JGeneAlign.PrintBestAlignment();
    
    }
    return 0;
}

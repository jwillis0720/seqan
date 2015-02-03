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

#include "boost/filesystem.hpp"

//Seqan Headers
#include <seqan/basic.h>
#include <seqan/seq_io.h>
#include <seqan/sequence.h>
#include <seqan/arg_parse.h>

//Project Headers
#include "DatabaseHandler.h"
#include "SeqIg.h"
#include "StructDefs.h"
#include "AlignAntibody.h"
#include "AntibodyJunction.h"

//An inline function to quickly check if a file or directory exists
inline bool check_if_dir_exists (const std::string &name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}


inline TSVector &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
};


inline TSVector Split(const std::string &s, char delim) {
    TSVector elems;
    split(s, delim, elems);
    return elems;
};


inline TCMap GetDatabaseFiles(const std::string & db_path, const bool & verbose)
{
    //You could put any file path in here, e.g. "/home/me/mwah" to list that directory
    boost::filesystem::path idbpath(db_path);
    boost::filesystem::directory_iterator end_itr;
    TCMap map_of_files;
    
    // cycle through the directory
    //This used to not segfault!!!
    //TODO -- Segfaults here
    for (boost::filesystem::directory_iterator itr(idbpath); itr != end_itr; ++itr)
    {
        // If it's not a directory, list it. If you want to list directories too, just remove this check.
        if (is_regular_file(itr->path()))
        {
            // assign current file name to current_file and echo it out to the console.
            std::string current_file = itr->path().string();
            
            //Split by directory path and return a vector of the split
            TSVector split_lines = Split(current_file,'/');
            
            //Then we get the last thing in there to get the filename
            std::string file_name = split_lines.back();
            
            //Gene DB class will handle parsing this into memory
            DatabaseHandler GeneDB(current_file);
            //Try to open
            try {
                GeneDB.Open();
                if(verbose)
                {
                    std::cout << "Loading DB at -> " << current_file << std::endl;
                    GeneDB.PrintPretty();
                }
            }catch(DatabaseHandlerExceptions &msg){
                std::cerr << "Couldn't open Database file" << std::endl;
                std::cerr << msg.what();
                exit(1);
            }
            seqan::CharString sub_file = file_name.substr(0, file_name.size()-6);
            map_of_files[sub_file] = GeneDB.GetDbContainer();
        }
    }
    return map_of_files;
}


//Setup Argument Parser takes the parser class and adds all the arguments to it
void SetUpArgumentParser(seqan::ArgumentParser & parser)
{
    //Basic info about the application
    setAppName(parser, "SeqIg");
    setShortDescription(parser, "SeqIg - Immunoglobulin Germline Gene Assignment");
    setCategory(parser, "Database Locations");
    setDate(parser, "December 2014");
    
    
    /*Database or sample options, basically asking what are the properties of your query,
    and making the database path from that*/
    addSection(parser, "Sample Options");
    addOption(parser, seqan::ArgParseOption("d","database_path",
                                            "The database path", seqan::ArgParseOption::STRING));
    addOption(parser, seqan::ArgParseOption("r","receptor",
                                            "The receptor type", seqan::ArgParseOption::STRING));
    addOption(parser, seqan::ArgParseOption("c","chain",
                                            "The chain type", seqan::ArgParseOption::STRING));
    addOption(parser, seqan::ArgParseOption("s","species",
                                            "The species type", seqan::ArgParseOption::STRING));
    
    //Other options
    addSection(parser, "Other Options");
    addOption(parser, seqan::ArgParseOption("v","verbose","Verbose Output"));
    
    //The required options like the input
    addSection(parser, "Input Options");
    addOption(parser, seqan::ArgParseOption("f","input_file",
                                            "The input file to be considered",seqan::ArgParseOption::INPUTFILE));
    //Set valid values for all options
    setValidValues(parser, "receptor", "Ig TCR");
    setValidValues(parser, "chain", "heavy lambda kappa");
    setValidValues(parser, "species", "human mouse rat llama rhesus");
    
    //Set required - This should be an argument, but working with all options is so much easier, and I'm a madman
    setRequired(parser, "f");
    
    //Set Database Default Values
    setDefaultValue(parser, "database_path", "/Users/jordanwillis/Git_repos/seqan/seqig_data");
    setDefaultValue(parser, "receptor", "Ig");
    setDefaultValue(parser, "chain", "heavy");
    setDefaultValue(parser, "species", "human");
}


//This method is different. After the arg parse is set up, this takes the argument values set by user
seqan::ArgumentParser::ParseResult ExtractOptions(seqan::ArgumentParser const & parser, SeqIgOptions & options)
{
    /*Everything is pretty much set through a structure defined in StructDefs.h, these structures are passed
     pretty much everywhere in SeqIg*/
    
    
    //getOptionvalue - Pass in a structure, and the method sets it in place
    //The bool returns just asks if everything went alright
    bool rdp = getOptionValue(options.database_path, parser, "database_path");
    bool rr = getOptionValue(options.receptor,parser, "receptor");
    bool rc = getOptionValue(options.chain, parser, "chain");
    bool rs = getOptionValue(options.species, parser, "species");
    
    //This is an actual bool option
    options.verbose = isSet(parser,"verbose");
    
    //Get the input file options
    bool rfn = getOptionValue(options.input_file,parser,"input_file");
    
    //Check if the database path set by user exists
    if(!check_if_dir_exists(options.database_path)){
        std::cerr << "\n Can't find database path " << options.database_path << std::endl;
        return seqan::ArgumentParser::PARSE_ERROR;
    }
    
    //All these bool values set earlier check that everything went smoothly with loading the databases
    if(!rdp || !rr || !rc || !rs){
        std::cerr << "\n Problem loading databases" << std::endl;
        return seqan::ArgumentParser::PARSE_ERROR;
    }
    
    
    //I seperated the input option bool so I can get a seperate message if it screwed up
    if(!rfn){
        std::cerr << "\n Problem with input file" << std::endl;
        return seqan::ArgumentParser::PARSE_ERROR;
    }
    
    //if everything went okay, it shouldn't enter any if statement and return ok
    return seqan::ArgumentParser::PARSE_OK;
}

/*This method takes in the all the sample info and creates the exact path to the
database file*/
void SetDatabaseFastas(SeqIgOptions const &options, DatabasePaths &dbpaths)
{
    std::string top_level_dir;
    top_level_dir =  options.database_path +
                    "/" + options.receptor +
                    "/" + options.chain +
                    "/" + options.species;
    dbpaths.Vgene_db = top_level_dir + "/V";
    dbpaths.Vgene_family = dbpaths.Vgene_db + "/family.fasta";
    dbpaths.Vgene_files = GetDatabaseFiles(dbpaths.Vgene_db + "/genes/", options.verbose);
    dbpaths.Dgene_db = top_level_dir + "/D";
    dbpaths.Dgene_family = dbpaths.Dgene_db  + "/family.fasta";
    //dbpaths.Dgene_files = GetDatabaseFiles(dbpaths.Dgene_db + "/genes/", options.verbose);
    dbpaths.Jgene_family = top_level_dir + "/J/family.fasta";
};


//The main method runs the executable for those new to C++
int main(int argc, char const ** argv)
{
    //Structures defined in StructDefs, options and the resulting db paths
    SeqIgOptions options;
    DatabasePaths dbpaths;
    
    // Parse the command line.
    seqan::ArgumentParser parser;
    SetUpArgumentParser(parser);
    seqan::parse(parser, argc, argv);
    
    //And extract the results
    seqan::ArgumentParser::ParseResult res;
    res = ExtractOptions(parser, options);
    
    //check that the parser didn't blow it
    if (res != seqan::ArgumentParser::PARSE_OK)
    {
        std::cerr << "\n Problem parsing arguments \n" << std::endl;
        return 1;
    }
    
    //This takes the options and makes a valid path to the databases
    SetDatabaseFastas(options, dbpaths);
    
    //V Gene DB class will handle parsing this into memory
    DatabaseHandler VGeneDB(dbpaths.Vgene_family);

    //Try to open
    try {
        VGeneDB.Open();
        if(options.verbose)
        {
            std::cout << "Loading DB at -> " << dbpaths.Vgene_family << std::endl;
            VGeneDB.PrintPretty();
        }
    }catch(DatabaseHandlerExceptions &msg){
            std::cerr << "Couldn't open Database" << std::endl;
            std::cerr << msg.what();
            return 1;
    }
    
    //Containers i.e.maps changes the database into a map structure we can iterate in memory
    Tdbcontainer VGeneFamilyContainer = VGeneDB.GetDbContainer();
    
    //J Gene DB class will handle parsing this into memory
    DatabaseHandler JGeneDB(dbpaths.Jgene_family);

    //Try to  open
    try
    {
        JGeneDB.Open();
        if(options.verbose)
        {
            std::cout << "Loading DB at -> " << dbpaths.Jgene_family << std::endl;
            JGeneDB.PrintPretty();
        }
    }catch(DatabaseHandlerExceptions &msg){
        std::cerr << "Couldn't open Database" << std::endl;
        std::cerr << msg.what();
        return 1;
    }
    
    //Loads the database
    Tdbcontainer JGeneContainer = JGeneDB.GetDbContainer();

    /*Lastly if it is a heavy chain, it will have a D gene and corresponding database*/
    Tdbcontainer DFamilyContainer;
    if(options.chain == "heavy")
    {
        DatabaseHandler DGeneDB(dbpaths.Dgene_family);
        try {
            DGeneDB.Open();
            if(options.verbose)
            {
                std::cout << "Loading DB at -> " << dbpaths.Dgene_db << std::endl;
                DGeneDB.PrintPretty();
            }
        }catch(DatabaseHandlerExceptions &msg) {
            std::cerr << "Couldn't open Database" << std::endl;
            std::cerr << msg.what();
            return 1;
        }
        DFamilyContainer = DGeneDB.GetDbContainer();
    }
    
    /////////////////
    //INPUT SECTION//
    /////////////////
    
    //This goes through the input file, but needs to be a c_str for seqan
    const char * input_file_name;
    input_file_name = options.input_file.c_str();
    
    //init an id and sequence variable to hold everything
    seqan::CharString id;
    seqan::Dna5String seq;
    seqan::SequenceStream seqStream(input_file_name);
    
    //See that we can open input file
    if (!seqan::isGood(seqStream))
    {
        std::cerr << "ERROR: Could not open the file " << input_file_name << "\n";
        return false;
    }
    
    //Go through stream with a while loop
    while (!seqan::atEnd(seqStream))
    {
        if (seqan::readRecord(id, seq, seqStream) != 0)
        {
            std::cerr << "ERROR: Could not read from " << input_file_name << "\n";
            return 1;
        }
                
        //Align V Gene Family to narrow down which V Gene family is it in
        AlignAntibody VGeneFamilyAlign(id, seq, VGeneFamilyContainer, options.verbose);
        if (options.verbose)
            VGeneFamilyAlign.PrintBestAlignment();

        //Get best V Gene family
        seqan::CharString best_v_family = VGeneFamilyAlign.GetTopGene();
        
        //Gets best container based on which family
        Tdbcontainer VGeneContainer = dbpaths.Vgene_files[best_v_family];
        AlignAntibody VGeneAlign(id, seq, VGeneContainer, options.verbose);
        
        //Print bast alignment
        if(options.verbose)
            VGeneAlign.PrintBestAlignment();
        
        
        //Align J Gene. There are few enough J genes we don't have to narrow down family first
        AlignAntibody JGeneAlign(id, seq, JGeneContainer, options.verbose);
        if(options.verbose)
          JGeneAlign.PrintBestAlignment();
    
        //if heavy, align D gene too
        
        if(options.chain == "heavy")
        {
            AlignAntibody DFamilyAlign(id, seq, DFamilyContainer, options.verbose);
            if(options.verbose)
            {
                DFamilyAlign.PrintBestAlignment();
            }
            
            //*Todo might implement a subdir but not yet
            //Get best D Gene family
            //seqan::CharString best_d_family = DFamilyAlign.GetTopGene();
            //Tdbcontainer DGeneContainer = dbpaths.Dgene_files[best_d_family];
            //AlignAntibody DGeneAlign(id, seq, DFamilyContainer, options.verbose);
            
            try
            {
                AntibodyJunction AJ(VGeneAlign, JGeneAlign, DFamilyAlign, seq);
            }catch(AntibodyJunctionException &msg) {
                std::cerr << "Problem with id -> " << id << std::endl;
                std::cerr << msg.what() << std::endl;
                std::cerr << "Skipping" << std::endl;
            }
        }
    }
    
    //Program exited successfully
    return 0;
}

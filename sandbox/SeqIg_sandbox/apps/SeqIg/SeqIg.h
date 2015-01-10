//
//  SeqIg.h
//  seqan
//
//  Created by Jordan Willis on 12/7/14.
//
//

#include <seqan/arg_parse.h>
#include "StructDefs.h"


#ifndef seqan_SeqIg_h
#define seqan_SeqIg_h
void setUpArgumentParser(seqan::ArgumentParser &);
void setDatabaseFastas(SeqIgOptions const &options, DatabasePaths &);
seqan::ArgumentParser::ParseResult extractOptions(seqan::ArgumentParser const &, SeqIgOptions &);
#endif

#ifndef PROGRAMHELPER_H
#define PROGRAMHELPER_H

#include "Eqlogger.h"

enum ProgramMode {
    HELP = -1,
    UNIT_TEST = 0,
    UNIT_TEST_OF_THE_FILE = 1,
    RANDOM_TEST = 2,
    SOLVE = 3
};

//--------------------------------------------------------------------
//! Get program mode
//!
//! \param logfile pointer to the file with program logs
//! \param argc number of cmd argument
//! \param argv massive of the char* cmd arguments
//!
//! \return program mode
//-------------------------------------------------------------------
ProgramMode getProgramMode(FILE *logfile, const int argc, const char **argv);

//--------------------------------------------------------------------
//! Get helper info
//--------------------------------------------------------------------
void helperMode();

#endif // PROGRAMHELPER_H

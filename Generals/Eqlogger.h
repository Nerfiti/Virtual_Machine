#ifndef EQLOGGER_H
#define EQLOGGER_H

#include "stdio.h"

enum TypeLogMessage {
    EMPTY,
    INFO,
    ERROR,
    COMPLETE,
    FAIL
};

//---------------------------------------------------------
//! Get start program log
//---------------------------------------------------------
void startProgramLog(FILE *logfile);

//---------------------------------------------------------
//! Get end program log
//---------------------------------------------------------
void endProgramLog(FILE *logfile);

//---------------------------------------------------------
//! Get input log
//!
//! \param [in] numberOfVariables number of variables
//---------------------------------------------------------
void inputLog(FILE *logfile, int numberOfVariables);

//---------------------------------------------------------
//! Get output log
//!
//! \param [in] output output text
//---------------------------------------------------------
void outputLog(FILE *logfile, const char *output);

//---------------------------------------------------------
//! Get test complete log
//!
//! \param [in] num test number
//---------------------------------------------------------

//---------------------------------------------------------
//! Get open file log
//!
//! \param filename name of opened file
//---------------------------------------------------------
void openFileLog(FILE *logfile, const char *filename);

//---------------------------------------------------------
//! Get close file log
//!
//! \param filename name of opened file
//---------------------------------------------------------
void closeFileLog(FILE *logfile, const char *filename);

//---------------------------------------------------------
//! Get log with given text
//---------------------------------------------------------
void textToLog(FILE *logfile, TypeLogMessage type, const char *text);

#endif // EQLOGGER_H
#ifndef UNITTESTEQUATION_H
#define UNITTESTEQUATION_H

#include "enumberOfRoots.h"
#include "Eqlogger.h"
#include "stdio.h"

struct Test_case {
    double a = 0;
    double b = 0;
    double c = 0;
    double ans1 = 0;
    double ans2 = 0;
    NumberOfRoots nRoots = NO_ROOTS;
};

enum FailReasons {
    WrongNumberOfRoots,
    WrongAnswer,
    WrongAnswers
};

//----------------------------------------------------------------------
//! Test of the SolveEquation's work with standard test cases
//!
//! \param logfile pointer to the file with program logs
//!
//! \return have the test been completed (true or false)
//----------------------------------------------------------------------
bool stdTestEquation(FILE *logfile);

//----------------------------------------------------------------------
//! Test of the SolveEquation's work
//!
//! \param logfile pointer to the file with program logs
//! \param num number of the test
//! \param a First coefficient
//! \param b Second coefficient
//! \param c Third coefficient
//! \param expectedAns1 First expected answer
//! \param expectedAns2 Second expected answer (if number of roots == TWO_ROOTS)
//! \param expectedNRoots expected number of roots
//!
//! \return have the test been completed (true or false)
//----------------------------------------------------------------------
bool TestEquation(FILE *logfile, int num, double a, double b, double c, double expectedAns1, double expectedAns2, NumberOfRoots expectedNRoots);

//----------------------------------------------------------------------
//! Test of the SolveEquation's work
//!
//! \param [in] logfile pointer to the file with program logs
//! \param [in] num test number
//! \param [in] testCase test case
//!
//! \return have the test been completed (true or false)
//----------------------------------------------------------------------
bool TestEquation(FILE *logfile, int num, Test_case testCase);

//----------------------------------------------------------------------
//! Test of the SolveEquation's work
//!
//! \param [in] logfile pointer to the file with program logs
//! \param [in] testCase test case
//! \param [in] count number of test cases
//!
//! \return have all the tests been completed (true or false)
//----------------------------------------------------------------------
bool TestEquation(FILE *logfile, Test_case testCase[], int count);

//----------------------------------------------------------------------
//! Test of the SolveEquation's work
//!
//! \param logfile pointer to the file with program logs
//! \param filename name of file
//!
//! \return have all the tests been completed (true or false)
//----------------------------------------------------------------------
bool TestEquation(FILE *logfile, const char *filename);

//----------------------------------------------------------------------
//! Get 3 random coefficients and result of SolveEquation's work
//!
//! \param logfile pointer to the file with program logs
//! \param [in] num number of tests
//----------------------------------------------------------------------
void RandomTestEquation(FILE *logfile, int num);

//----------------------------------------------------------------------
//! Write about complete test
//!
//! \param [in] logfile pointer to the file with program logs
//! \param [in] x number of test
//!
//! \return true
//----------------------------------------------------------------------
bool complete(FILE *logfile, int x);

//----------------------------------------------------------------------
//! Skip line in the file
//!
//! \param file Pointer to the target file
//!
//! \return have all the tests been completed (true or false)
//----------------------------------------------------------------------
void skipLine(FILE *file);

//----------------------------------------------------------------------
//! Write about fail test and reason of fail
//!
//! \param logfile pointer to the file with program logs
//! \param [in] x number of the test
//! \param [in] reason reason of the fail
//! \param [in] nRoots number of roots
//! \param [in] ans1 first answer
//! \param [in] ans2 second answer
//! \param [in] expectedNRoots expected number of roots
//! \param [in] expectedans1 expected first answer
//! \param [in] expectedans2 expexted second answer
//! \param [out] allTests pointer to the flag
//! \param [in] lastTime time since start the test
//!
//! \return false
//-----------------------------------------------------------------------
bool fail(FILE *logfile, int x, FailReasons reason, NumberOfRoots nRoots,         double ans1,         double ans2,
                                                    NumberOfRoots expectedNRoots, double expectedAns1, double expectedAns2);

#endif // UNITTESTEQUATION_H
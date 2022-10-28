#ifndef SOLVEEQUATION_H
#define SOLVEEQUATION_H

#include "enumberOfRoots.h"
#include "Eqlogger.h"

//-----------------------------------------------------------------------
//! Read coefficients from stdin
//!
//! \param logfile pointer to the file with program logs
//! \param [out] a Pointer on the first coefficient
//! \param [out] b Pointer on the second coefficient
//! \param [out] c Pointer on the third coefficient
//-----------------------------------------------------------------------
void inputCoefficients(FILE *logfile, double *a, double *b, double *c);

//-----------------------------------------------------------------------
//! Solve square equation ax^2 + bx + c = 0
//!
//! \param [in] a First coefficient
//! \param [in] b Second coefficient
//! \param [in] c Third coefficient
//! \param [out] x1 Pointer on the first root
//! \param [out] x2 Pointer on the second root
//!
//! \return NO_ROOTS, ONE_ROOT, TWO_ROOTS or INF_ROOTS
//-----------------------------------------------------------------------
NumberOfRoots solveSquare(double a, double b, double c, double *x1, double *x2);

//-----------------------------------------------------------------------
//! Solve linear equation ax + b = 0
//!
//! \param [in] a First coefficient
//! \param [in] b Second coefficient
//! \param [out] ans Pointer on the answer
//!
//! \return NO_ROOTS, ONE_ROOT, or INF_ROOTS
//-----------------------------------------------------------------------
NumberOfRoots solveLinear(double a, double b, double *ans);

//-----------------------------------------------------------------------
//!
//! Calculate Dicriminant of square equation
//!
//! \param [in] a First coefficient
//! \param [in] b Second coefficient
//! \param [in] c Third coefficient
//!
//! \return Discriminant
//-----------------------------------------------------------------------
double discriminant(double a, double b, double c);

//-----------------------------------------------------------------------
//! Write answer of the equation to stdout
//!
//! \param logfile pointer to the file with program logs
//! \param [in] nRoots Number of the Roots
//! \param [in] root1 First root
//! \param [in] root2 Second root
//-----------------------------------------------------------------------
void printAnswer(FILE *logfile, NumberOfRoots nRoots, double root1, double root2);

//-----------------------------------------------------------------------
//! Write answer of the equation to target
//!
//! \param [out] target Pointer on the target string
//! \param [in] nRoots Number of the Roots
//! \param [in] root1 First root
//! \param [in] root2 Second root
//-----------------------------------------------------------------------
void sPrintAnswer(char *target, NumberOfRoots nRoots, double root1, double root2);

//-----------------------------------------------------------------------
//! Compare two double variables
//!
//! \param [in] a First number
//! \param [in] b Second number
//!
//! \return 1 (if a > b), 0 (if a == b) -1 (if a < b)
//-----------------------------------------------------------------------
int compareDoubleNumbers(double a, double b);

#endif // SOLVEEQUATION_H



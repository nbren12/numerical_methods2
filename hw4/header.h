/*  Code for Assignment 4 of Numerical Methods II

 http://www.math.nyu.edu/faculty/goodman/teaching/NumericalMethodsII2014/index.html

 The author gives permission for anyone to use this publically posted
 code for any purpose.  The code was written for teaching, not research
 or commercial use.  It has not been tested thoroughly and probably has
 serious bugs.  Results may be inaccurate, incorrect, or just wrong. */


// header file header.h

// Assume the generic headers have been given already

// Procedures in the problem sepcific file

void init( double x0[]);         // initialize dynamics, get initial configuration

void f( double f[], double x[]); // compute and return f(x), which defines the ODE system.

void exact_soln (double x[], double t);

// The solver

void RK3( double dx[], double x[],  double dt, int n,
          double v1[], double v2[], double v3[]);

// Common parameters
extern int p;




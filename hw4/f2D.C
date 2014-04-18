/*  Code for Assignment 4 of Numerical Methods II

 http://www.math.nyu.edu/faculty/goodman/teaching/NumericalMethodsII2014/index.html

The author gives permission for anyone to use this publically posted
code for any purpose.  The code was written for teaching, not research
or commercial use.  It has not been tested thoroughly and probably has
serious bugs.  Results may be inaccurate, incorrect, or just wrong. */


// Source file f2D.C

/*  Problem specific code for an n-body gravitational interaction simulation

There are two procedures,

init: initialized variables and sets initial configuration

f:   computes the time derivatives of the positions and velocities

*/

#include <iostream>
#include <math.h>
using namespace std;

void init(double x0[]) {
    x0[0] = 0;
    x0[1] = 1;
}

void f( double f[], double x[]){

    double xsq;

    xsq = x[0]*x[0] + x[1]*x[1];

    f[0] = ( 1 + xsq ) * x[1];
    f[1] = - ( 1 + xsq ) * x[0];

  }

void exact_soln (double x[], double t){
    x[0] = sin( 2.0 * t );
    x[1] = cos( 2.0 * t );
}


























/*  Code for Assignment 3 of Numerical Methods II

 http://www.math.nyu.edu/faculty/goodman/teaching/NumericalMethodsII2014/index.html

The author gives permission for anyone to use this publically posted
code for any purpose.  The code was written for teaching, not research
or commercial use.  It has not been tested thoroughly and probably has
serious bugs.  Results may be inaccurate, incorrect, or just wrong. */


// Source file init.cpp

/*  write initial conditions into u

A wave Gaussian packet centered on x_0 with half-width r_0 and wave number k

u_0(x) = exp( - (x-x_0)^2/(2r_0^2) ) * sin(kx)

set u[j] = u_0(x_j)

*/

#include <iostream>
#include <math.h>
#include <vector>         // so you can use the vector class/template system
#define l(j,k,nx) ((j) + ((nx)*(k)))    // Lots of harmless parens to avoid confusion
using namespace std;


void init( vector<double>& u,      // initial data, to be set
           double&         sMax,   // fastest speed in the problem, to be computed
           double          L,      // length of the computational interval
           double          x0,     // center of the wave packet, see above
           double          r0,     // half width of the wave packet, see above
           double          k,      // wave number of the wave packet, see above
           double          g,      // gravity
           double          hbar,   // mean height
           int             nx) {   // number of grid points

  const double dx = L/(nx-1);      // so x_0 = 0 and x_{nx-1} = L

  double x;

  for ( int j = 0; j < nx; j++ ) {
    x    = j*dx;
    u[l(j, 0, nx)] = exp( - (x-x0)*(x-x0)/(2.*r0*r0) ) * sin(k*x);
   }

  for ( int j = 0; j < nx; j++ ) {
    u[l(j, 1, nx)] = - sqrt (g / hbar ) * u[l(j,0,nx)];
   }

  sMax = sqrt ( g * hbar );                        // A real PDE solver would have to put some physics here.

  return;
 }



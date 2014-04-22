/*  Code for Assignment 4 of Numerical Methods II

 http://www.math.nyu.edu/faculty/goodman/teaching/NumericalMethodsII2014/index.html

The author gives permission for anyone to use this publically posted
code for any purpose.  The code was written for teaching, not research
or commercial use.  It has not been tested thoroughly and probably has
serious bugs.  Results may be inaccurate, incorrect, or just wrong. */


// Source file fnb.C

/*  Problem specific code for an n-body gravitational interaction simulation

There are two procedures,

init: initialized variables and sets initial configuration

f:   computes the time derivatives of the positions and velocities

*/

#include <iostream>
#include <math.h>
using namespace std;

double *m;            // The mass array is global, but allocated in init

double *rx;           // array pointers defined here, allocated in init, and used in f
double *ry;
double *vx;
double *vy;
double *ax;           // x and y components of acceleration
double *ay;

#define p 3                            // p is the number of bodies

void init( double x0[])  {             // return the initial configuration

  cout << "initialize" << endl;
  double *rx0;                         // where the initial positions and speeds are set
  double *ry0;
  double *vx0;
  double *vy0;

  rx0 = new double (p);
  ry0 = new double (p);
  vx0 = new double (p);
  vy0 = new double (p);
  m   = new double (p);

  rx = new double (p);       // allocations for the arrays used in the dynamics
  ry = new double (p);
  vx = new double (p);
  vy = new double (p);
  ax = new double (p);
  ay = new double (p);

//   Problem specific, give the masses and initial positions and velocities individually
//   This is the part you have to change to do a different simulation

  rx0[0] = 1.;
  ry0[0] = 0.;
  vx0[0] = 0.;
  vy0[0] = .05;
  m[0]   = 2.;

  rx0[1] = -1.;
  ry0[1] = 0.;
  vx0[1] = 0.;
  vy0[1] = -.05;
  m[1]   = 2.;

  rx0[2] = 0.;
  ry0[2] = 0.;
  vx0[2] = 0.;
  vy0[2] = 0.;
  m[2]   = 4.;

//    Copy, is not simulation specific

  for (int k = 0; k < p; k++) {   // The indices are different than in the assignment statement because ...
     x0[ (4*k)    ] = rx0[k];     // ... indices start at 0, not 1.
     x0[ (4*k) +1 ] = ry0[k];
     x0[ (4*k) +2 ] = vx0[k];
     x0[ (4*k) +3 ] = vy0[k];
    }

  return;
 }


void f( double f[], double x[]){

   for (int k = 0; k < p; k++) {   // Unpack the positions and velocities from the configuration array, x.
     rx[k] = x[ (4*k)    ];
     ry[k] = x[ (4*k) +1 ];
     vx[k] = x[ (4*k) +2 ];
     vy[k] = x[ (4*k) +3 ];
    }

   double drx, dry;     // dr = r[k] - r[j], the vector from body j to body k
   double d;            // d = |dr| = distance between body k and body j
   for ( int j = 0; j < p; j++) {
     ax[j] = 0.;
     ay[j] = 0.;
     for ( int k = 0; k < p; k++) {
       if ( k == j) continue;         // skip to the end of the loop if j=k.  There is no j=k contribution.
       drx    = rx[k] - rx[j];
       dry    = ry[k] - ry[j];
       d      = sqrt( drx*drx + dry*dry );
       ax[j] += m[k]*drx/(d*d*d);
       ay[j] += m[k]*dry/(d*d*d);
      }
    }

   for (int k = 0; k < p; k++) {   // Pack time derivatives into f
     f[ (4*k)    ] = vx[k];
     f[ (4*k) +1 ] = vy[k];
     f[ (4*k) +2 ] = ax[k];
     f[ (4*k) +3 ] = ay[k];
    }
   return;
  }
















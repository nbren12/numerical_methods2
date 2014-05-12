/*  Code for Assignment 5 of Numerical Methods II

 http://www.math.nyu.edu/faculty/goodman/teaching/NumericalMethodsII2014/index.html

The author gives permission for anyone to use this publically posted
code for any purpose.  The code was written for teaching, not research
or commercial use.  It has not been tested thoroughly and probably has
serious bugs.  Results may be inaccurate, incorrect, or just wrong. */


// Source file RK4.C

/*  Problem specific code for an n-body gravitational interaction simulation

There are two procedures,

init: initialized variables and sets initial configuration

f:   computes the time derivatives of the positions and velocities

*/

#include <iostream>
#include <math.h>
using namespace std;

#include "header.h"


// Use the classic RK4 method described here http://en.wikipedia.org/wiki/Runge–Kutta_methods:
//
// v_1 = f(x) ; v_2 = f(x+ v_1 h/2) ; v_3 = f(x+v_2 h/ 2) ; v_4 = f(x+ h v_3)
// x_+= x + v_1 / 6  + v_2 / 3 + v_3 / 3 + v_4 / 6
//
void RK4( double dx[], double x[],  double dt, int n,
        double v1[], double v2[], double v3[], double v4[]){

  // cout << "The time stepper says hello" << endl;

  double *xt;    // "x temporary", to hold x + alpha*v1 or x + beta*v1 + gamma*v2
  xt = dx;       // WARNING: uses the same storage as dx

  // dynamically allocate the arrays
  /* double* v1 = new double[n]; */
  /* double* v2 = new double[n]; */
  /* double* v3 = new double[n]; */
  /* double* v4 = new double[n]; */

  f( v1, x);                      // stage 1, v1 = dt* f(x)
  for ( int j = 0; j < n; j++){
     v1[j] = dt*v1[j];
     xt[j] = x[j] + (1.0 / 2.0 ) * v1[j];  // next point = x + alpha*v1
    }

  f( v2, xt);                     // stage 2, v2 = dt*f(x+1.0/2.0*v1)
  for ( int j = 0; j < n; j++){
     v2[j] = dt*v2[j];
     xt[j] = x[j] + (1.0 /2.0)* v2[j];
    }

  f( v3, xt);                     // stage 3, v3 = dt*f(x+1.0/2.0*v2)
  for ( int j = 0; j < n; j++){
     v3[j] = dt*v3[j];
     xt[j] = x[j] + v3[j];
    }

  f( v4, xt);                     // stage 4, v4 = dt*f(x+v3)
  for ( int j = 0; j < n; j++){
     v4[j] = dt*v4[j];
    }

  for ( int j = 0; j < n; j++){
     dx[j] = (1.0/6.0)*v1[j] + (1.0/3.0)*v2[j] + (1.0/3.0)*v3[j] + (1.0 / 6.0) * v4[j];
    }

}

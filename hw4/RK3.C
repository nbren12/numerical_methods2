/*  Code for Assignment 4 of Numerical Methods II

 http://www.math.nyu.edu/faculty/goodman/teaching/NumericalMethodsII2014/index.html

The author gives permission for anyone to use this publically posted
code for any purpose.  The code was written for teaching, not research
or commercial use.  It has not been tested thoroughly and probably has
serious bugs.  Results may be inaccurate, incorrect, or just wrong. */


// Source file RK3.C

/*  Problem specific code for an n-body gravitational interaction simulation

There are two procedures,

init: initialized variables and sets initial configuration

f:   computes the time derivatives of the positions and velocities

*/

#include <iostream>
#include <math.h>
using namespace std;

#include "header.h"

//   The Runge Kutta coefficients

#define alpha .5
#define beta  .4
#define gamma .3

#define a1    .2
#define a2    .7
#define a3    .1

void RK3( double dx[], double x[],  double dt, int n,
          double v1[], double v2[], double v3[]){

  // cout << "The time stepper says hello" << endl;

  double *xt;    // "x temporary", to hold x + alpha*v1 or x + beta*v1 + gamma*v2
  xt = dx;       // WARNING: uses the same storage as dx

  f( v1, x);                      // stage 1, v1 = dt* f(x)
  for ( int j = 0; j < n; j++){
     v1[j] = dt*v1[j];
     xt[j] = x[j] + alpha*v1[j];  // next point = x + alpha*v1
    }

  f( v2, xt);                     // stage 2, v2 = dt*f(x+alpha*v1)
  for ( int j = 0; j < n; j++){
     v2[j] = dt*v2[j];
     xt[j] = x[j] + beta*v1[j] + gamma*v2[j];
    }

  f( v3, xt);                     // stage 3, v3 = dt*f(x+beta*v1+gamma*v1)
  for ( int j = 0; j < n; j++){
     v3[j] = dt*v3[j];
    }

  for ( int j = 0; j < n; j++){
     dx[j] = a1*v1[j] + a2*v2[j] + a3*v3[j];
    }


}
















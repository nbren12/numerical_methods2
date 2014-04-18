/*  Code for Assignment 4 of Numerical Methods II

 http://www.math.nyu.edu/faculty/goodman/teaching/NumericalMethodsII2014/index.html

The author gives permission for anyone to use this publically posted 
code for any purpose.  The code was written for teaching, not research 
or commercial use.  It has not been tested thoroughly and probably has
serious bugs.  Results may be inaccurate, incorrect, or just wrong. */


// Source file PlanetMovie.cpp

#include <math.h>
#include <iostream>
using namespace std;

#include "header.h"


int main(){
  
  cout << "hello, n bodies.  Interact." << endl;
  
  int p = 3;
  int n = 4*p;
  double dt = .1;
  
  double *x;             //  The computed configuration at time t
  double *dx;            //  Delta x = computed change for dt
  double *v1, *v2, *v3;
  x  = new double(n);
  v1 = new double(n);
  v2 = new double(n);
  v3 = new double(n);
  dx = new double(n);
  
  init(x);               // Initialize the time step routine once
  
  int nt = 3;           // Compute the number of time steps from the final time and dt.
  for ( int i = 0; i < nt; i++){
     RK3( dx, x, dt, n, v1, v2, v3);
     for ( int j = 0; j < n; j++){
        x[j] += dx[j];
      }
   }
  
//       To do: a convergence study, or record a trajectory to make a movie, call pywrite to send it to python
  
  return 0;
 }
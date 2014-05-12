/*  Code for Assignment 4 of Numerical Methods II

 http://www.math.nyu.edu/faculty/goodman/teaching/NumericalMethodsII2014/index.html

The author gives permission for anyone to use this publically posted
code for any purpose.  The code was written for teaching, not research
or commercial use.  It has not been tested thoroughly and probably has
serious bugs.  Results may be inaccurate, incorrect, or just wrong. */


// Source file PlanetMovie.cpp

#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

#include "header.h"


int main(){

  cout << "hello, n bodies.  Interact." << endl;

  int n = 4*p;
  double T = 4.0;
  double dt = .005;

  double *x;             //  The computed configuration at time t
  double *dx;            //  Delta x = computed change for dt
  double *v1, *v2, *v3, *v4;
  x  = new double[n];
  v1 = new double[n];
  v2 = new double[n];
  v3 = new double[n];
  v4 = new double[n];
  dx = new double[n];

  init(x);               // Initialize the time step routine once

  // open an output file
  ofstream outfile;
  outfile.open("runOutput.py");

  // output header info
  outfile << "p = " << p << "; T=  " << T << "; dt = " << dt << endl;

  int nt = (int) T / dt;           // Compute the number of time steps from the final time and dt.

  outfile << "import numpy as np" << endl;
  outfile << "dat = np.array([";

  double const eps = 10^-7;

  // Do Time Stepping
  for ( int i = 0; i < nt; i++){
     // cout << "T = " << dt* i << endl;
     RK4( dx, x, dt, n, v1, v2, v3, v4);
     for ( int j = 0; j < n; j++){
        x[j] += dx[j];
        outfile << x[j] << "," ;
      }
   }
  outfile << "])" << endl;
  outfile << "particles = dat.reshape((-1, p, 4))"<< endl;
  outfile << "del dat" << endl;
  outfile.close();

  return 0;
 }

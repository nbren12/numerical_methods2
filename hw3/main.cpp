/*  Code for Assignment 3 of Numerical Methods II

 http://www.math.nyu.edu/faculty/goodman/teaching/NumericalMethodsII2014/index.html

The author gives permission for anyone to use this publically posted 
code for any purpose.  The code was written for teaching, not research 
or commercial use.  It has not been tested thoroughly and probably has
serious bugs.  Results may be inaccurate, incorrect, or just wrong. */


// Source file main.cpp

#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <vector>         // so you can use the vector class/template system
#include <ctime>          // so you can read the computer time clock

using namespace std;

#include "header.h"

#define l(j,k,nx) ((j) + ((nx)*(k)))    // Lots of harmless parens to avoid confusion

int main(){
  
  cout << "hello, movie world" << endl;
  
// Specified run parameters
  
  const double L   = 5.;         // Length of the computational interval
  const double T   = 5.;         // Integrate up to this time
  
  const int    nx  = 2000;         // number of space grid points
  const double dx  = L / (nx-1); // x_0 = 0 and x_{nx-1} = L are the first and last grid points
  const double lam = .8;         // the CFL ratio
        double sMax;             // fastest wave speed in the problem, to be computed
  
  const double tf  = .03;         // time interval between frames
  
//   run setup

  const int    nf = 1 + (int) ( T / tf ); // The number of frames, including initial condition
  const double tfa = T / nf;              // time per frame, adjusted, in case of roundoff in nf.
  
  vector<double> u;          // The solution at the current time step
  vector<double> v;          // The solution at the next time step, scratch storage
  vector<double> frames;     // Each row is the u value at the corresponding frame time
   
  u.resize(nx);              // Allocate the memory
  v.resize(nx);
  frames.resize(nx*(nf+1));  // With the initial data, there are nf+1 frames
  
  init( u, sMax, L, .7*L, .06*L, 30., nx);           // Set initial conditions
  
  double dt = lam*dx/sMax;           // time step, as determined by CFL
  int    nt = 1 + (int) ( tf / dt);  // number of time steps per frame, rounded up.
         dt = tf/nt;                 // lower dt so exactly nt time steps of size dt fit into tf
  
  for ( int j = 0; j < nx; j++ ){
    frames[ l(j,0,nx)] = u[j];       // frame zero is the initial data.
   }
  
  for ( int frame = 1; frame <= nf; frame++){  // to make a frame ...
  
    for ( int k = 0; k < nt; k++) {                  // ... advance the solution  ...
       timeStep( u, v, dx, dt, nx);
      }
     for ( int j = 0; j < nx; j++) {                 // ... and copy the frame.
       frames[ l( j, frame, nx)] = u[j];
      }
    }
  
  
//   Write the results into a Python file
  
  
  ofstream runOutput;                  // Internal name of the plot file
  runOutput.open ("runOutput.py");      // Open, and give an external name
  
  string pyIndent = "   ";             // One indententation in python
  runOutput <<             "import numpy as np"      << endl;
  runOutput <<             "def RunData():"          << endl;
  
  runOutput << pyIndent << "L = " << L               << endl;
  runOutput << pyIndent << "data = { 'L' : L } "     << endl;    // a dictionary for all run information
  
  runOutput << pyIndent << "tf = " << tf             << endl;
  runOutput << pyIndent << "data[ 'tf' ] = tf "      << endl;
  
  runOutput << pyIndent << "fMin = " << -1.          << endl;
  runOutput << pyIndent << "data[ 'fMin' ] = fMin "  << endl;
  
  runOutput << pyIndent << "fMax = " << 1.           << endl;
  runOutput << pyIndent << "data[ 'fMax' ] = fMax "  << endl;
  
  runOutput << pyIndent << "runString = 'wave packet moves left'" << endl;
  runOutput << pyIndent << "data[ 'runString' ] = runString "  << endl;
  
  pyWrite( frames, "frames", pyIndent, nf, nx, runOutput);
  
  runOutput << pyIndent << "return data"             << endl;
  
  runOutput.close();
  
  return 0;
 }
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

    const double epsilon = 1e-10;
    double Tfinal = 4.0;
    double t = 0.0;
    double dt = 1.0;

    double *x, *x1, *x2;             //  The computed configuration at time t
    double *dx, *dx2;            //  Delta x = computed change for dt
    double *v1, *v2, *v3, *v4;

    x  = new double[n];
    x1  = new double[n];
    x2  = new double[n];
    v1 = new double[n];
    v2 = new double[n];
    v3 = new double[n];
    v4 = new double[n];
    dx = new double[n];
    dx2 = new double[n];

    init(x);               // Initialize the time step routine once

    // open an output file
    ofstream outfile;
    ofstream tfile;

    outfile.open("runOutput.py");
    tfile.open("tOutput.py");

    // output header info
    outfile << "p = " << p << "; T=  " << Tfinal << "; dt = " << dt << endl;

    int nt = (int) Tfinal / dt;           // Compute the number of time steps from the final time and dt.

    outfile << "import numpy as np" << endl;
    outfile << "dat = np.array([";

    tfile << "import numpy as np" << endl;
    tfile << "dat = np.array([";


    for(int j =0 ; j < n ; j++)
        outfile << x[j] << ",";
    tfile << 0.0 << "," ;

    // Do Time Stepping
    while( t < Tfinal ){

        adaptiveStep( dx,  dx2,  x, x1, x2,  &dt, n,
                v1,  v2,  v3,  v4,
                epsilon,  0, 0);

        for (int j = 0 ; j < n; j++)
            x[j]+=dx2[j];

        t+=dt;

        // Output to file
        for(int j =0 ; j < n ; j++)
            outfile << x[j] << ",";
        tfile << dt << ",";

    }

    tfile << "])" << endl;
    outfile << "])" << endl;
    outfile << "particles = dat.reshape((-1, p, 4))"<< endl;
    outfile << "del dat" << endl;
    outfile.close();

    return 0;
 }


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
#define PI 3.14159265358979323846                       // from the Wikepedia page


int main(){

    cout << "Fixed Step Verify:" << endl;
    cout << "For order 3 RK method, we expect the ratio to be 2^3=8" << endl << endl;

    int n = 2;
    int i,j,k;

    double T  = 4.0 * PI;
    double dt = T / 1000;
    const double nIter = 15;

    double *x, *dx, *x_exact;
    double *v1, *v2, *v3;

    dx = new double(n);
    x = new double(n);
    x_exact = new double(n);
    v1 = new double(n);
    v2 = new double(n);
    v3 = new double(n);

    int nt = 10;
    int ntTmp = 10;
    double err1, err0;

    for (k = 0; k < nIter; k++)
    {
        ntTmp = nt * 2;  // double the number of time steps
        dt    = T / ntTmp;

        init(x);                     //Initialize the routine

        // Time step up until T
        for (i = 0; i < nt; i++){
            RK3( dx, x, dt, n, v1, v2, v3);
            for (j = 0; j < n; j++){
                x[j] += dx[j];
            }
        }

        exact_soln(x_exact, T);  // Load exact solution

        // Calculate L2 norm error compared to exact soln
        err1 = 0.0;
        for (j = 0; j < n; j++)
            err1 += pow(x[j] - x_exact[j], 2);

        err1 = sqrt(err1);


        // print convergence ratios
        if (k  > 0 )
            cout << "Step Size is "<<  dt << " Error is " << err1 << " Ratio is " << err0 / err1 << endl;


        err0 = err1;
        nt   = ntTmp;

    }
  return 0;
 }




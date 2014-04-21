
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

    int n = 2;

    double T  = 4.0 * PI;
    double dt = T / 1000;
    double nIter = 2;

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

    for (int i = 0; i < nIter; i++)
    {
        ntTmp = nt * 2;
        dt    = T / ntTmp;

        init(x);                     //Initialize the routine

        for ( int i = 0; i < nt; i++){
            RK3( dx, x, dt, n, v1, v2, v3);
            for ( int j = 0; j < n; j++){
                x[j] += dx[j];
            }
        }

        // TODO : Calculate error and ratio


    }
  return 0;
 }




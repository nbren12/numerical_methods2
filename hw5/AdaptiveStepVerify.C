/*  Code for Assignment 4 of Numerical Methods II

 http://www.math.nyu.edu/faculty/goodman/teaching/NumericalMethodsII2014/index.html

The author gives permission for anyone to use this publically posted
code for any purpose.  The code was written for teaching, not research
or commercial use.  It has not been tested thoroughly and probably has
serious bugs.  Results may be inaccurate, incorrect, or just wrong. */


// Source file OneStepVerify.C

#include <math.h>
#include <iostream>
using namespace std;

#include "header.h"

int main(int argc, char** argv){

    cout << "Adaptive Step Verify:" << endl;
    cout << "Printing adapative output ..." <<endl <<endl;

    double *x0, *dx, *dx2, *x_exact, *x, *x2, *x1;
    double *v1, *v2, *v3, *v4;
    double dt, hTmp;
    double err0, err1;
    int n = 2;
    int nIter;

    const double epsilon = 1e-10;

    dt  = 1e-10;
    nIter = 20;

    dx = new double[n];
    dx2 = new double[n];
    x = new double[n];
    x2 = new double[n];
    x1 = new double[n];
    x_exact = new double[n];

    v1 = new double[n];
    v2 = new double[n];
    v3 = new double[n];
    v4 = new double[n];

    init(x);


    adaptiveStep( dx,  dx2,  x, x1, x2,  &dt, n,
            v1,  v2,  v3,  v4,
            epsilon,  0, 1);



    cout << "Upper should be less than 1.2, but not too much less" << endl;
    cout << "Final dt = " << dt << endl;

    return 0;
}

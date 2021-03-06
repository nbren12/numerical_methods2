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

    cout << "One Step Verify:" << endl;
    cout << "For order 3 RK method, we expect the ratio to be 2^4=16" << endl << endl;

    double *x0, *dx, *x_exact;
    double *v1, *v2, *v3;
    double h, hTmp;
    double err0, err1;
    int n = 2;
    int nIter;

    h  = 4.0;
    nIter = 20;

    dx = new double[n];
    x0 = new double[n];
    x_exact = new double[n];

    v1 = new double[n];
    v2 = new double[n];
    v3 = new double[n];

    init(x0);

    hTmp = h;

    for ( int i = 0; i < nIter ; i++ )
    {
        hTmp = hTmp / 2.0;
        exact_soln(x_exact, hTmp);
        RK3(dx, x0, hTmp, 2, v1, v2, v3);

        err1 = 0.0;
        err1 =pow( x0[0] + dx[0] - x_exact[0],2 );
        err1 += pow( x0[1] + dx[1] - x_exact[1],2 );
        err1 = sqrt(err1); // Is this sqrt correct? Ratio is 4 without sqrt

        if (i == 0 ) {
            err0 = err1;
            continue;
        } else {
            cout << "Step Size is "<< hTmp << " Error is " << err1 << " Ratio is " << err0 / err1 << endl;
            err0 = err1;
        }

    }



    return 0;
}

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

    double *x;

    x = new double(2);

    init(x);
    cout << x[0] << " " << x[1] << endl;

    return 0;
}

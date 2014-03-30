/*  Code for Assignment 3 of Numerical Methods II
 
 http://www.math.nyu.edu/faculty/goodman/teaching/NumericalMethodsII2014/index.html
 
 The author gives permission for anyone to use this publically posted 
 code for any purpose.  The code was written for teaching, not research 
 or commercial use.  It has not been tested thoroughly and probably has
 serious bugs.  Results may be inaccurate, incorrect, or just wrong. */


// header file header.h

// Assume the generic headers have been given already
 
void init( vector<double>& u,     // initial data, to be set
          double&         sMax,   // fastest speed in the problem, to be computed
          double          L,      // length of the computational interval
          double          x0,     // center of the wave packet, see above
          double          r0,     // half width of the wave packet, see above
          double          k,      // wave number of the wave packet, see above
          int             nx) ;   // number of grid points
          
void timeStep( vector<double>& u,      // the solution at the current time, replaced by the solution at the next tiome
              vector<double>& v,      // a temp vector
              double          dx,     // the space step
              double          dt,     // the time step
              int             nx) ;   // number of grid points
 

//   Write an array for Python to read

void pyWrite( vector<double>& a,          // The array to be written out
             string          aName,      // The name of the array in the python file
             string          pyIndent,   // Some blanks, a python indent
             int             n,          // number of rows in a
             int             m,          // number of columns in a
             ofstream        &pyFile) ;  // the python file to write into,
                                         // pyFile must be open already.
                                         // this procedure leaves it open.
                                         // It's &pyFile, not pyFile, it can't be
                                         // copied so it's call by reference.
 



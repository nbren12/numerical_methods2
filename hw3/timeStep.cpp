/*  Code for Assignment 3 of Numerical Methods II

 http://www.math.nyu.edu/faculty/goodman/teaching/NumericalMethodsII2014/index.html

The author gives permission for anyone to use this publically posted
code for any purpose.  The code was written for teaching, not research
or commercial use.  It has not been tested thoroughly and probably has
serious bugs.  Results may be inaccurate, incorrect, or just wrong. */


// Source file timeStep.cpp

/*  take one time step

A wave Gaussian packet centered on x_0 with half-width r_0 and wave number k

u_0(x) = exp( - (x-x_0)^2/(2r_0^2) ) * sin(kx)

set u[j] = u_0(x_j)

*/

#include <iostream>
#include <math.h>
#include <vector>         // so you can use the vector class/template system
#define PI 3.14159265358979323846                       // from the Wikepedia page
#define l(j,k,nx) ((j) + ((nx)*(k)))    // Lots of harmless parens to avoid confusion
using namespace std;


void timeStepDemo( vector<double>& u,      // the solution at the current time, replaced by the solution at the next tiome
               vector<double>& v,      // a temp vector
               double          dx,     // the space step
               double          dt,     // the time step
               int             nx) {   // number of grid points

  for ( int j = 0; j < (nx-1); j++) {  // do a left shift ...
    v[j] = u[j+1];
   }
  v[nx-1] = 0.;                        // ... adding a zero on the end

  for ( int j = 0; j < nx; j++) {      // copy v back to u when the time step is done.
    u[j] = v[j];
   }

  return;
 }



double bottom(double x, double L, double bbar) {
    return bbar  * ( x > 9.0/20.0 * L) * (x < 11.0/20.0 * L) * sin( 4 * PI / L * ( x - 9.0/20.0 * L ) );
    // return 0.0;
}

void timeStep( vector<double>& u,      // the solution at the current time, replaced by the solution at the next tiome
               vector<double>& v,      // a temp vector
               double          L,
               double          g,
               double          hbar,
               double          bbar,   // max relative size of bottom topography
               double          dx,     // the space step
               double          dt,     // the time step
               int             nx) {   // number of grid points



    double mu  = dt/dx;
    double mu2  = mu * mu;
    double up, um,u0, hp, hm,h0;
    double bp, bm, b0, bp2, bm2;
    int i  = 0;

    // Use lax wendroff with the bottom topography

    // Handle periodic BC using ghost cells
    for (i = 0; i < nx ; i++)
    {
        v[l(i, 0, nx)] = u[l(i, 0, nx)];
        v[l(i, 1, nx)] = u[l(i, 1, nx)];
    }


    for (i = 0; i < nx; i++)
    {
        if (i < nx -1 ) {
            up = v[l(i+1,0,nx )];
            hp = v[l(i+1,1,nx )];
        } else {
            up = v[l(0,0,nx )];
            hp = v[l(0,1,nx )];
        }

        if (i > 0 ) {
            um = v[l(i-1,0,nx )];
            hm = v[l(i-1,1,nx )];
        } else {
            um = v[l(nx-1,0,nx )];
            hm = v[l(nx-1,1,nx )];
        }

        u0 = v[l(i,0,nx)];
        h0 = v[l(i,1,nx)];

        bm = bottom((i-2) * dx, L, hbar * bbar);
        bp = bottom((i) * dx, L, hbar * bbar);
        b0 = bottom((i-1) * dx, L, hbar * bbar);
        bm2 = bottom((i-1) * dx- dx/2.0, L, hbar * bbar);
        bp2 = bottom((i-1) * dx + dx/2.0, L, hbar * bbar);


        // First Order terms
        u[l(i  , 0, nx)] -=  (mu /2.0)*( g *( hp - hm ) );
        u[l(i  , 1, nx)] -=  (mu /2.0)* ( (hbar-bp)*up - (hbar-bm)*um );


        // Second order correction
        u[l(i  ,0, nx)] += (mu2 /2.0) * g * hbar *( up + um - 2.0*u0 );
        u[l(i  ,1, nx)] += (mu2 /2.0) * g * hbar *( hp + hm - 2.0*h0 );

        u[l(i  ,0,nx)]  -= (mu * mu /2.0) * g *( bp * up + bm*um - 2.0*b0*u0 );
        u[l(i  ,1,nx)]  -= (mu * mu/ 2.0) * g *( bp2 * (hp -h0) -bm2 * (h0-hm) );

    }
}



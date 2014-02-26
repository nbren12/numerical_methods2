//  C++ file for Numerical Methods II, Spring 2014
//  http://www.math.nyu.edu/faculty/goodman/teaching/NumericalMethodsII2014/index.html

//  File: PoissonSolver.C


#include <iostream>       // so you can use cout
#include <vector>         // so you can use the vector class/template system
#include <math.h>         // so you can use math functions such as sine and exp
#include <ctime>          // so you can read the computer time clock
#include <stdlib.h>     /* atoi */
using namespace std;

                                                        // Bullet 4

#define l(i,j,N)  ( (i) + (j)*(N) )                     // A macro that indexes into a square N X N array

#define PI 3.14159265358979323846                       // from the Wikepedia page

                                                        // Bullet 1

double u_e( double x, double y, double L);              // The exact mathematical solution, evaluated at the point (x,y)

double f_e( double x, double y, double L);              // Evaluate f(x,y), for solving Lap(u) = f

double g_e(           double y, double L);              // Evaluate g(y), for u(0,y) = g(y)

void   it ( vector<double>& v,
            vector<double>& u,
            vector<double>& h2f, int N);                //  The signature of the procedure that does one iteration, v <-- Iteration(u, h^2*f)

double rSSQ ( vector<double>& u,
              vector<double>& h2f, int N);              //  return the sum of the squares of the residuals || Lap(u) - h^2f ||

double amp( vector<double>& u, int n, int m, int N);    //  Evaluate the amplitude of the sin(pi*n*x/L)*sin(pi*m*y/L) mode in u on an N X N mesh vector u

int main(int argc, char *argv[]) {


   cout << "Hello, from the Poisson solver" << endl;

                              // Bullet 2

   const int    N = atoi(argv[1]);      // The number of points in each direction, which does not change
   const double L = 2.;       // The length of the sides of the box
   const double h = L/(N+1);  // h = Delta x = Delta y.  There are N+1 intervals between x=0 and x=L.
   const int    T = 10000;    // The number of Jacobi iterations to do, should be an even number
   const int    T_p = 100;   // The number of iterations between printouts

   int i, j, k;               // indices for grid functions and iteration count
   int x, y;                  // (x,y) coordinates of the corresponding grid point

   long int ClockStart = clock();  // look at the clock before you start computing
   long int ClockNow;              // the rest of the clock readings

                              // Bullet 3

   vector<double> u;          // An array to hold a grid vector
   vector<double> v;          // You need grid vectors to do a Jacobi iteration
   vector<double> h2f;        // A grid vector to hold the right hand side, which is h^2*f.

   u.resize(N*N);             // This makes the vector have N^2 elements
   v.resize(N*N);
   h2f.resize(N*N);

   for ( i = 0; i < N; i++ ) {              // Initialize the grid vectors
      for ( j = 0; j < N; j++ ) {
         x = h*(i+1);                       // This would be x_i = h*i except that i starts with 0 instead of 1 in C++ convention
         y = h*(j-1);
                                            // Bullet 5

         u[l(i,j,N)] = 0.;                  // The initial guess is u = 0.
         v[l(i,j,N)] = 0.;                  // You probably don't have to say v=0, but just to be safe.
         h2f[l(i,j,N)] = h*h*f_e( x, y, L); // The right hand side, which is part of the problem
        }
     }

    for (j = 0; j < N; j++){             // Put in possibly non-trivial boundary values on the left boundary.
       y = h*(j-1);
       h2f[l(0,j,N)] = .25*g_e( y, L);   // The right hand side, which is part of the problem
      }

    k = 0;
    double oldRnorm, newRnorm;           //  L^2 norm of the residual now, and last time.
    oldRnorm = 0.;
    while ( k < T ) {
       it( v, u, h2f, N);
       k++;
       it( u, v, h2f, N);
       k++;
       newRnorm = sqrt( rSSQ( u, h2f, N) );
       if ( k%T_p == 0 ){
          ClockNow = clock();
          cout << "Iteration " << k << " has residual norm " << newRnorm << ", and ratio = 1 + " << oldRnorm/newRnorm-1.
               << ", elapsed time: " << (ClockNow - ClockStart)/double(CLOCKS_PER_SEC) << endl;
         }
       oldRnorm = newRnorm;
      }

   return 0;
  }


void it ( vector<double>& v, vector<double>& u, vector<double>& h2f, int N){

//               Do one Jacobi iteration, assuming Dirichlet boundary conditions.

   int    i,  j;           // Indices into the u and v arrays
   double ul, ur, ut, ub;  // The u values at neighbor points.  ul (= "u left") = u(i-1,j)

   for ( i = 0; i < N; i++ ) {
      for ( j = 0; j < N; j++ ) {

                                                   // Bullet 6

         if ( i == 0 ) ul     = 0;                 // Are you on the left   boundary?
         else          ul     = u[l(i-1,j  ,N)];
         if ( i == (N-1) ) ur = 0;                 // Are you on the right  boundary?
         else              ur = u[l(i+1,j  ,N)];
         if ( j == 0 )     ub = 0;                 // Are you on the bottom boundary?
         else              ub = u[l(i  ,j-1,N)];
         if ( j == (N-1) ) ut = 0;                 // Are you on the top    boundary?
         else              ut = u[l(i  ,j+1,N)];

         v[l(i,j,N)] = .25*( ut + ur + ub + ul ) - h2f[l(i,j,N)];  // The only real "work" in this program.

        }
     }

    return;
  }


double rSSQ ( vector<double>& u , vector<double>& h2f, int N) {

   int    i,  j;           // code copied from it
   double ul, ur, ut, ub;
   double R, RSSQ;         // The residual at (i,j) and the sum of squares

   RSSQ = 0.;

   for ( i = 0; i < N; i++ ) {
      for ( j = 0; j < N; j++ ) {
         if ( i == 0 ) ul     = 0;                 // Are you on the left   boundary?
         else          ul     = u[l(i-1,j  ,N)];
         if ( i == (N-1) ) ur = 0;                 // Are you on the right  boundary?
         else              ur = u[l(i+1,j  ,N)];
         if ( j == 0 )     ub = 0;                 // Are you on the bottom boundary?
         else              ub = u[l(i  ,j-1,N)];
         if ( j == (N-1) ) ut = 0;                 // Are you on the top    boundary?
         else              ut = u[l(i  ,j+1,N)];

         R = u[l(i,j,N)] - ( .25*( ut + ur + ub + ul ) - h2f[l(i,j,N)] );  // The only real "work" in this program.
         RSSQ += R*R;
        }
     }
   return RSSQ;
  }



double f_e( double x, double y, double L){
   return 0.;                       // Assume f = 0.
  }


double g_e( double y, double L){
   return sin( PI*y/L);
  }


double u_e( double x, double y, double L){
   return sin(PI*y/L)*exp(-PI*x/L);
  }






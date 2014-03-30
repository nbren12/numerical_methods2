/*  Code for Assignment 3 of Numerical Methods II

 http://www.math.nyu.edu/faculty/goodman/teaching/NumericalMethodsII2014/index.html

The author gives permission for anyone to use this publically posted 
code for any purpose.  The code was written for teaching, not research 
or commercial use.  It has not been tested thoroughly and probably has
serious bugs.  Results may be inaccurate, incorrect, or just wrong. */


// Source file pyWrite

/*  Procedure to write an array to an ASCII file in a format that can
    be read by python.        

    Write the n by m array a as a python statements

   aName = np.array([ [ a_11, ....,a_1m], [a_21 ... ],...,[a_n1,...,a_nm] ])
   data['aName'] = aName
   
   Assume the elements of a are in row major order, which means the linear
   array is 
   
   a = (a_11, a_12, ..., a_1m, a_21, ..., a_2m, ..., a_n1, ..., a_nm)
   
   The C/C++ loops start with zero, ao a[0] is a_11, etc.

*/ 

#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


void pyWrite( vector<double>& a,          // The array to be written out
              string          aName,      // The name of the array in the python file
              string          pyIndent,   // Some blanks, a python indent
              int             n,          // number of rows in a
              int             m,          // number of columns in a
              ofstream        &pyFile) {  // the python file to write into,
                                          // pyFile must be open already.
                                          // this procedure leaves it open.
                                          // It's &pyFile, not pyFile, it can't be
                                          // copied so it's call by reference.
                                       
  
  int i;  // The row index, i = 0, ..., n-1
  int j;  // The column index, i = 0, ..., m-1 

  pyFile << pyIndent << aName <<  " = np.array([\\" << endl;
                                       // note: \\" here produces \" in the output.
  
  for ( i = 0; i < n; i++){            // Write row i
      
    pyFile << pyIndent << "[";         //  no << endl;.  Not done with this line.
    
    for ( j = 0; j < m; j++) {         // Write a_ij
    
      if ( j < (m-1)  ) {              //  not at the end of the row ...
        pyFile << a[ i*m + j] << " , ";//  ... not the end of the line
       }
        
      else {                           //  end of a row      
        if ( i < (n-1) ) {             //  not the bottom row
          pyFile <<  a[i*m+j] << " ],\\" << endl; // end of the row
         }
          
        else {                        //  end of the bottom row, all done.
          pyFile << a[i*m+j] <<  " ]])" << endl;
         }
       }    
     }     // end of for ( j = 0; j < m; j++), done writing row i
   }       // end of for ( i = 0; i < n; i++), done writing a.
    
  
  pyFile << pyIndent << "data[ '" << aName << "' ] = " << aName << endl;
  return;
  
 }
  



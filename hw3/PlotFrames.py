#  Python 2.7.x file for Assignment 3 of Numerical Methods II, Spring 2014
#  http://www.math.nyu.edu/faculty/goodman/teaching/NumericalMethodsII2014/index.html

# The author gives permission for anyone to use this publically posted
# code for any purpose.  The code was written for teaching, not research
# or commercial use.  It has not been tested thoroughly and probably has
# serious bugs.  Results may be inaccurate, incorrect, or just wrong.

#  File: PlotFrames.py

#  Make frames for a movie from  data from a Python formatted plot file


import runOutput         as ro
import numpy             as np
import matplotlib.pyplot as plt
import string as st

#   copy the data elements to interman python variables with the same names

data       = ro.RunData()
L          = data['L']            #  The length of the interval
tf         = data['tf']           #  The time between frames
fMin       = data['fMin']         #  The smallest u value, for plotting
fMax       = data['fMax']         #  The largest u value, for plotting
runString  = data['runString']    #  A string that describes the run
frames     = data['frames']       #  The curves to be plotted

[nf,nx] = frames.shape

print 'nx = ' + str(nx)+ ", nf = " + str(nf)

fm  = np.zeros( nx, np.float64)   # the curve data, in floating point
xm  = np.zeros( nx, np.float64)   # x values, for plotting

dx = ( float(L)/float(nx-1))      # L might be an integer
for j in range(0,nx):
    xm[j] = j*dx


for frame in range(0,nf):
    plt.figure( frame)
    for j in range(0,nx):
        fm[j] = frames[frame,j]
    curve1  = plt.plot(xm, fm)
    plt.setp( curve1, 'linewidth', 5., 'color', 'k', 'alpha', .5)
    plt.axis([0., L, fMin, fMax])
    plt.grid(axis='both')
    plt.title(runString)
    textString = 'frame ' + str(frame) + ', elapsed time: ' + str(frame*tf)
    plt.text(.1*L, .9*fMax, textString)
    FrameFileName = "WaveMovieFrames/frame" + str(frame) + ".png"
    plt.savefig(FrameFileName)
    plt.close(frame)
    print "saved file " + FrameFileName

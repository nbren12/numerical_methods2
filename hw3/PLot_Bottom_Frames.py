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
import matplotlib.animation as animation
import string as st

#   copy the data elements to interman python variables with the same names

data       = ro.RunData()
L          = data['L']            #  The length of the interval
tf         = data['tf']           #  The time between frames
fMin       = data['fMin']         #  The smallest u value, for plotting
fMax       = data['fMax']         #  The largest u value, for plotting
runString  = data['runString']    #  A string that describes the run
frames     = data['frames']       #  The curves to be plotted

nf, nx = frames.shape
print 'nx = %i, nf = %i'%(nx, nf)

PI = np.pi

xm = np.linspace(0, L, nx, endpoint=False)
bbar = .5
bottom  = -1.0+ bbar  * ( xm > 9.0/20.0 * L) * (xm < 11.0/20.0 * L) * np.sin( 4 * PI / L * ( xm - 9.0/20.0 * L ) );

# Create initial plot

fig, ax = plt.subplots(1)
curve2, = ax.plot(xm, bottom, linewidth=1.0, color= 'b', alpha=.5)
curve1, = ax.plot(xm, frames[0,:], linewidth=5.0, color= 'k', alpha=.5)
plt.axis([0., L, fMin, fMax])
plt.grid(axis='both')
frame = 0
textString = 'frame %i, elapsed time: %f'%(frame, frame*tf)
textbox=  plt.text(.1*L, .9*fMax, textString)
plt.title(runString)


def updatefig(frame):
    """
    Will pass this function to update plot to FuncAnimation
    """
    print frame
    curve1.set_ydata(frames[frame,:])
    FrameFileName = "WaveMovieFrames/frame%i.png"%frame
    textString = 'frame %i, elapsed time: %f'%(frame, frame*tf)
    textbox.set_text(textString)

    return curve1,

updatefig(50)
plt.savefig('bottom_frame50.png')

ani = animation.FuncAnimation(fig, updatefig, xrange(nf), interval=75, blit=True)
ani.save('WaveMovie_bottom.mp4')


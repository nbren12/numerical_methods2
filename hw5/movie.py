import runOutput         as ro
import tOutput           as to
import numpy             as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from scipy.interpolate import interp1d # used for interolating the data onto the frame times I specify

frame_times = np.linspace(0, 4.0, 400)
nt_line_y   = -1.05


############################################################
#                      Nitty Gritty                        #
############################################################

t = to.dat.cumsum()
dt = ro.dt
particles = ro.particles

frame_interpolator = interp1d(t, particles, axis=0, kind='linear')
particles = frame_interpolator(frame_times)

# Get average time step over a given time interval
timestep = [
        (( bTime < t  ) & ( t < eTime )).sum()
        for bTime, eTime
        in zip(frame_times[0:-1], frame_times[1:])
        ]

timestep.append(timestep[-1])
timestep = np.array(timestep)
dt_max = timestep.max()

# Begin plotting routine
nt, p,_ = particles.shape

xmin = particles[:,:,0].min()
xmax = particles[:,:,0].max()
ymin = particles[:,:,1].min()
ymax = particles[:,:,1].max()

m = min(xmin ,ymin)
M = max (xmax, ymax)


m = -1
M = 1
xLim = [m, M]
yLim = [min(m, nt_line_y -.05), M]

# xLim = [ -10.0, 10.0 ]
# yLim = [ -10.0, 10.0 ]

# Initial Plot
frame = 0

fig, ax = plt.subplots(1)
plt.axis(xLim + yLim)
plt.grid('on')
ax.set_aspect('equal')

points = []
for pp in xrange(p):
    x = particles[frame,pp,0 ]
    y = particles[frame,pp,1 ]
    point, = plt.plot(x, y, 'o')
    points.append((pp, point))

textStr = 'frame %i, elapsed time %0.2f'%(frame, frame_times[frame])

line_length =  np.log(timestep[frame]) / np.log(dt_max)
nt_line, = plt.plot([m, m + line_length * (M-m) ], [nt_line_y, nt_line_y], '-', linewidth=3)

textbox = plt.title(textStr)
#
def updatefig(frame):
    print frame
    for pp, point in points:
        x = particles[frame,pp,0 ]
        y = particles[frame,pp,1 ]
        point.set_data(x, y)

        line_length =  np.log(timestep[frame]) / np.log(dt_max)
        nt_line.set_data([m, m + line_length * (M-m) ], [nt_line_y, nt_line_y])

        textStr = 'frame %i, elapsed time %0.2f'%(frame, frame_times[frame])
        textbox.set_text(textStr)

ani = animation.FuncAnimation(fig, updatefig, xrange(nt), interval=75, blit=True)
ani.save('nbody.mp4', bitrate=1024)

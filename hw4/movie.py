import runOutput         as ro
import numpy             as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


dt = ro.dt
particles = ro.particles

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
yLim = [m, M]

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

textStr = 'frame %i, elapsed time %0.2f'%(frame, frame * dt )

textbox = plt.title(textStr)

def updatefig(frame):
    print frame
    for pp, point in points:
        x = particles[frame,pp,0 ]
        y = particles[frame,pp,1 ]
        point.set_data(x, y)
        textStr = 'frame %i, elapsed time %0.2f'%(frame, frame * dt )
        textbox.set_text(textStr)

ani = animation.FuncAnimation(fig, updatefig, xrange(nt), interval=75, blit=True)
ani.save('nbody.mp4', bitrate=1024)

#  Makefile file for Numerical Methods II, Spring 2014
#  http://www.math.nyu.edu/faculty/goodman/teaching/NumericalMethodsII2014/index.html

#  File: Makefile

#   The author gives permission for anyone to use this publicly posted 
#   code for any purpose.  The code was written for teaching, not research 
#   or commercial use.  It has not been tested thoroughly and probably has
#   serious bugs.  Results may be inaccurate, incorrect, or just wrong.

SUFFIXES :=
%.cpp:
%.o:
%.h:
%.py:

#        Compilers, linkers, compile options, link options, paths 

CC      = gcc             #  C
CPP     = g++             #  C++ 

CCFLAGS = -O2       

LINKER  =  g++       # linker, use C++ linker 

PYTHON  = python
FFMPEG  = ffmpeg           

#          Lists of files

CPP_SOURCES = main.cpp timeStep.cpp init.cpp pyWrite.cpp

P_SOURCES   = PlotFrames.py 

CPP_OBJECTS = $(patsubst %.cpp, %.o, $(CPP_SOURCES) )


#           Stuff that every single program depends on

FOR_ALL   = Makefile header.h

ALL_SOURCES = $(CPP_SOURCES) $(P_SOURCES) Makefile  header.h 



#        compiling and linking (building) instructions, all manual, no implicit rules

main.o:     main.cpp $(FOR_ALL)
	$(CPP) -c $(CCFLAGS) main.cpp

timeStep.o: timeStep.cpp $(FOR_ALL)
	$(CPP) -c $(CCFLAGS) timeStep.cpp

init.o :   init.cpp $(FOR_ALL)
	$(CPP) -c $(CCFLAGS) init.cpp

pyWrite.o: pyWrite.cpp $(FOR_ALL)
	$(CPP) -c $(CCFLAGS) pyWrite.cpp

CppExecutable: main.o timeStep.o init.o pyWrite.o
	$(CPP)  $(CCFLAGS) main.o timeStep.o init.o pyWrite.o -o CppExecutable


#               Running executables


runOutput.py: CppExecutable             #  If the code has changed, you have to re-run it.
	./CppExecutable

WaveMovie.mpg: runOutput.py PlotFrames.py
	rm -f WaveMovieFrames/*.png        #  delete any existing frames
	rm -f WaveMovie.mpg                #  delete the existing movie, if there is one
	mkdir WaveMovieFrames
	$(PYTHON) PlotFrames.py 
	$(FFMPEG) -i WaveMovieFrames/frame%d.png WaveMovie.mpg

tarball: $( All_SOURCES)  
	tar -cvf Assignment3.tar $(ALL_SOURCES) 




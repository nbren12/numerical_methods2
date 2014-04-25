#  Makefile file for Numerical Methods II, Assignment 4, Spring 2014
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

CCFLAGS = -O2  -std=gnu++0x    

LINKER  =  g++       # linker, use C++ linker 

PYTHON  = python

#          Lists of files

CPP_SOURCES = PlanetMovie.C fnb.C OneStepVerify.C f2D.C RK3.C FixedStepVerify.C

CPP_OBJECTS = $(patsubst %.C, %.o, $(CPP_SOURCES) )


#           Stuff that every single program depends on

FOR_ALL   = Makefile header.h

ALL_SOURCES = $(CPP_SOURCES)  Makefile  header.h movie.py



#        compiling and linking (building) instructions, all manual, no implicit rules

#   Planet movie 

PlanetMovie.o:     PlanetMovie.C $(FOR_ALL)
	$(CPP) -c $(CCFLAGS) PlanetMovie.C

fnb.o: fnb.C $(FOR_ALL)
	$(CPP) -c $(CCFLAGS) fnb.C  

#   One step tester

OneStepVerify.o: OneStepVerify.C  $(FOR_ALL)
	$(CPP) -c $(CCFLAGS) OneStepVerify.C  

f2D.o: f2D.C $(FOR_ALL)
	$(CPP) -c $(CCFLAGS) f2D.C

#   trajectory convergence study tester

#   Time step program

RK3.o: RK3.C $(FOR_ALL)
	$(CPP) -c $(CCFLAGS) RK3.C   


#   Assemble the executables


nBodyExecutable: PlanetMovie.o fnb.o RK3.o
	$(CPP)  $(CCFLAGS) PlanetMovie.o fnb.o RK3.o -o nBodyExecutable

OneStepVerifyExecutable: OneStepVerify.o f2D.o RK3.o
	$(CPP)  $(CCFLAGS) OneStepVerify.o f2D.o RK3.o -o OneStepVerifyExecutable

FixedStepVerifyExecutable: FixedStepVerify.o f2D.o RK3.o
	$(CPP)  $(CCFLAGS) FixedStepVerify.o f2D.o RK3.o -o FixedStepVerifyExecutable

# Movie

runOutput.py : nBodyExecutable
	./nBodyExecutable

nbody.mp4 : movie.py runOutput.py
	$(PYTHON) $<

#               Running executables

.PHONY: nBodyMovie OneStepVerify FixedStepVerify tarball UnitTest clean

nBodyMovie: nBodyExecutable     #  If the code has changed, you have to re-run it.
	./nBodyExecutable

OneStepVerify: OneStepVerifyExecutable    
	./OneStepVerifyExecutable

FixedStepVerify: FixedStepVerifyExecutable    
	./FixedStepVerifyExecutable

UnitTest: FixedStepVerify OneStepVerify


tarball: $( All_SOURCES)  
	tar -cvf Assignment4.tar $(ALL_SOURCES) 

clean:
	rm -f  nBodyExecutable OneStepVerifyExecutable FixedStepVerifyExecutable Assignment4.tar nbody.mp4 *.o runOutput.py runOutput.pyc

movie: nbody.mp4 
	mplayer $<


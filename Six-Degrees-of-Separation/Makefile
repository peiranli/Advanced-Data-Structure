# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)

ifeq ($(type),opt)
    CPPFLAGS += -O3
    LDFLAGS += -O3
else
    CPPFLAGS += -g
    LDFLAGS += -g
endif

all: pathfinder



# include what ever source code *.h files pathfinder relies on (these are merely the ones that were used in the solution)

pathfinder: ActorEdge.o ActorNode.o Movie.o ActorGraph.o

actorconnections: Timer.o ActorNode.o ActorEdge.o Movie.o DisjointSet.o ActorGraph.o
# include what ever source code *.h files ActorGraph relies on (these are merely the ones that were used in the solution)
extension: extension.o
# Note: you do not have to include a *.cpp file if it aleady has a paired *.h file that is already included with class/method headers

#ActorGraph.o: Movie.h ActorNode.h ActorEdge.h ActorGraph.h
Timer.o: Timer.h

extension.o: extension.cpp

DisjointSet.o: Movie.o ActorNode.o DisjointSet.h

ActorGraph.o: Movie.o ActorEdge.o ActorNode.o ActorGraph.h

ActorEdge.o: ActorEdge.h

ActorNode.o: ActorNode.h

Movie.o: Movie.h

clean:
	rm -f pathfinder *.o core*


#ifndef ACTOREDGE_H
#define ACTOREDGE_H
#include "Movie.h"
#include <utility>

/**
  * The ActorNode class is a class to represent every single actor.
  * It contains actor names, the movies he or she in, the actors and
  * actresses that have be in the same movie with him or her, and the
  * other useful parameters.
  */

class ActorNode;

/**
  * The ActorEdge class is a class to represent a connection of two actors or
  * actresses that were in the same movie. It contains Movie*, two ActorNode*
  * and other useful parameters.
  */

class ActorEdge{
public:
    Movie* movie;
    ActorNode* actor1;
    ActorNode* actor2;
    int weight;

    ActorEdge(){}

    /**
      * Construtor that takes a movie and two actors as input
      */
    ActorEdge(Movie* movie, ActorNode* actor1, ActorNode* actor2);
    /**
      * form a output to match the standard output
      */ 
    std::string to_string();
    /**
      * redefine the operator == to compare if two ActorEdges are the same
      */ 
    bool operator == (ActorEdge* edge)const;

    /**
      * Destructor
      */
    ~ActorEdge(){}

};

#endif //ACTOREDGE_H

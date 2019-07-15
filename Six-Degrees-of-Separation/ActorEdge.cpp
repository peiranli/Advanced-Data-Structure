#include "ActorEdge.h"
#include "ActorNode.h"
#define MOST_RECENT_YEAR 2015


/**
  * Construtor that takes a movie and two actors as input
  */
ActorEdge::ActorEdge(Movie* movie, ActorNode* actor1, ActorNode* actor2){
    this->movie = movie;
    this->actor1 = actor1;
    this->actor2 = actor2;
    this->weight = 1 + (MOST_RECENT_YEAR - movie->movie_year);
}

/**
  * form a output to match the standard output
  */ 
std::string ActorEdge::to_string(){
    return "[" + movie->movie_title + "#@" + std::to_string(movie->movie_year) 
        + "]-->";
}

/**
  * redefine the operator == to compare if two ActorEdges are the same
  */ 
bool ActorEdge::operator==(ActorEdge* edge)const{
    if (edge->movie == this->movie && (edge->actor1 == this->actor1 && 
        edge->actor2 == this->actor2|| edge->actor1 == this->actor2 && 
        edge->actor2 == this->actor1))
        return true;
    else
        return false;
}

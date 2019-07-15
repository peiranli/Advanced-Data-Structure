#ifndef ACTORNODE_H
#define ACTORNODE_H
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

/**
  * The ActorEdge class is a class to represent a connection of two actors or
  * actresses that were in the same movie. It contains Movie*, two ActorNode*
  * and other useful parameters.
  */
class ActorEdge;

/**
  * The movie class is a class that represents a movie. It has the movie title,
  * the movie year, and other useful parameters.
  */
class Movie;


/**
  * The ActorNode class is a class to represent every single actor.
  * It contains actor names, the movies he or she in, the actors and
  * actresses that have be in the same movie with him or her, and the
  * other useful parameters.
  */
class ActorNode{

public:
    std::string actor_name;
    int dist;
    bool done;
    std::unordered_map<std::string,ActorEdge*> edges;
    ActorEdge* prev_edge;
    ActorNode* prev_actor;
    std::unordered_map<std::string,Movie*> movies;
    std::unordered_map<std::string,ActorNode*> adj_actors;

    int rank;
    ActorNode* parent;
    int initial_year;

    /**
      * void Constructor
      */ 
    ActorNode(){}
    /**
     * constructor with actor_name as a input
     */
    ActorNode(std::string actor_name);

    /**
     * redefine the == to compare two actor nodes
     */
    bool operator==(ActorNode* actor) const;
    /**
     * Add a movie to the hashmap of the actor node that contains the movies
     * the actor is in
     */  
    void add_movie(Movie* movie);
    /**
     * check if there is a movie movie in the movie hashmap
     */ 
    bool find_movie(Movie* movie);
    /**
     * format the output to relate the standard output
     */
    std::string to_string();
    /**
     * check if can find the actor with actor_name in the adj_actor hashmap
     */
    bool find_actor(std::string actor_name);
    /**
     * get the edge that connect the actor and the curr_actor
     */
    ActorEdge* find_edge(ActorNode* actor);
    /**
     * redefine the < to check if the actorname is smaller
     */   
    bool operator<(const ActorNode& other);
    /**
     * Destructor
     */
    ~ActorNode(){}
};

#endif //ACTORNODE_H

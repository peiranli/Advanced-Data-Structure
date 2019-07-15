#ifndef DISJOINTSET_H
#define DISJOINTSET_H
#include "ActorNode.h"
#include "Movie.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

/**
 * This is the class that use the disjoint set to represent actor connections
 * There are actor_map and movie_map as the base of the set
 * There are merge, find, and reset methods as the eseential of the disjoint
 * Set's method
 */
class DisjointSet{
public:
    std::unordered_map<std::string, ActorNode*> actor_map;
    std::unordered_map<int, std::unordered_map<std::string, Movie*>> movie_map;

    /**
     * void constructor
     */
    DisjointSet(void){}

    /**
     * Destructor
     */ 
    ~DisjointSet();

    /**
     * the method to merge two actors in two sets if they have connections
     */ 
    void merge(ActorNode* actor1, ActorNode* actor2);

    /**
     * The method to find a actor nodd. While finding, make a path compression
     */ 
    ActorNode* find(ActorNode* actor);

    /**
     * reset the disjoint set after each connection is done
     */
    void reset();

    /**
     * load the input from file and setup the empty set
     */
    bool loadFromFile(const char* in_filename);

};

#endif //DISJOINTSET_H

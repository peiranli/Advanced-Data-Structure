/*
 * ActorGraph.h
 * Author: Peiran Li, Ziang Jing
 * Date:   3/14/2017
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H
#include <unordered_map>
#include <iostream>
#include "ActorNode.h"
#include "ActorEdge.h"
// Maybe include some data structures here

class ActorGraph {
protected:
  
    // Maybe add class data structure(s) here

public:
    std::unordered_map<std::string, ActorNode*> actor_map;
    std::unordered_map<std::string, Movie*> movie_map;
    std::unordered_set<ActorEdge*> edge_map;
    	std::unordered_map<int, std::unordered_map<std::string, Movie*>> movie_map_by_year;
    /**
     * void constructor
     */
    ActorGraph(void);

    /**
     * reset the graph when starting a new iteration
     */
    void setUp();
    // Maybe add some more methods here
  
    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2015 - 
     * movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges, 
        bool actorconnection); 

    /**
     * build the graph if the requirement is find the shortest path in the graph
     */
    void buildGraph(bool use_weighted_edges);

    /**
     * build graph if the requirement is to find the actorconnection by bfs
     */
    void buildGraphByYear(int year);

    /**
     * reset the adj list of each actor node before each iteration
     */
    void reset();

    /**
     * Destructor
     */
    ~ActorGraph();
  
};


#endif // ACTORGRAPH_H

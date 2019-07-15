/*
 * ActorGraph.cpp
 * Author: Peiran Li, Ziang Jing
 * Date:   3/14/17
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.h"

#define INFINITY 2147483647
#define MOST_RECENT_YEAR 2015
using namespace std;

/**
 * void constructor
 */
ActorGraph::ActorGraph(void) {}

/**
 * reset the graph when starting a new iteration
 */
void ActorGraph::setUp(){
	for (auto it = actor_map.begin(); it != actor_map.end(); it++){
		ActorNode* curr_actor = it->second;
		if(it->second == nullptr)
            continue;
		curr_actor->dist = INFINITY;
        curr_actor->prev_actor == nullptr;
        curr_actor->done = false;
	}
}

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
bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges, 
    bool actorconnection) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;
  
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            // get the next string before hitting a tab character and put it in
            // 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }
    
        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);
    
        // find (or create if doesn't exist) the actor of the input
        ActorNode* actor;
        if (actor_map.find(actor_name) == actor_map.end()){
            actor = new ActorNode(actor_name);
            actor_map.insert(std::make_pair(actor_name, actor));
        }
        else{
            actor = actor_map[actor_name];
        }

        if (actor->initial_year > movie_year)
            actor->initial_year = movie_year;

	//find (or create if doesn't exist) the movies
        Movie* movie;
        //the situdation that is not requiring actorconnection
        if (!actorconnection){
            if (movie_map.find(movie_title + std::to_string(movie_year)) == 
                movie_map.end()){
                movie = new Movie(movie_title, movie_year);
                movie_map.insert(std::make_pair(movie_title + 
                    std::to_string(movie_year), movie));
            }
            else{
                movie = movie_map[movie_title + std::to_string(movie_year)];
            }
        }
        //the situdation that requiring actorconnection
        else{
            if (movie_map_by_year[movie_year].find(movie_title + 
                std::to_string(movie_year)) == movie_map_by_year[movie_year].end()){
                movie = new Movie(movie_title, movie_year);
                movie_map_by_year[movie_year].insert(std::make_pair(movie_title 
                    + std::to_string(movie_year), movie));
            }
            else{
                movie = movie_map_by_year[movie_year][movie_title + 
                    std::to_string(movie_year)];
            }
        }
	//add movie and actor to each other's hashmap
        actor->add_movie(movie);
        movie->add_actor(actor);

    }
    //check if the file is correctly readed
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    
    //build the graph base on the input mode
    buildGraph(use_weighted_edges);

    infile.close();

    return true;
}

/**
 * build the graph if the requiement is find the shrortest path in the graph
 */
void ActorGraph::buildGraph(bool use_weighted_edges){
    //loop through the movie map
    for (auto it = movie_map.begin(); it != movie_map.end(); it++){
        Movie* movie = it->second;
        std::unordered_map<std::string, ActorNode*> actor_list = movie->actor_list;
	//loop through the actor list in each movie
        for (auto it2 = actor_list.begin(); it2 != actor_list.end(); it2++){
            ActorNode* actor = it2->second;
            //compare each other actor with the previous actor
	    for (auto it3 = ++(actor_list.begin()); it3 != actor_list.end(); it3++){
                // pair all actors
                ActorNode* curr_actor = it3->second;
                if (!actor->find_actor(curr_actor->actor_name)){
                    actor->adj_actors.insert(std::make_pair(curr_actor->
                        actor_name, curr_actor));
                    curr_actor->adj_actors.insert(std::make_pair(actor->
                        actor_name, actor));
                    ActorEdge* edge = new ActorEdge(movie, actor, curr_actor);
                    edge_map.insert(edge);
                    actor->edges.insert(std::make_pair(curr_actor->actor_name, 
                        edge));
                    curr_actor->edges.insert(std::make_pair(actor->actor_name, 
                        edge));
                }
                else{
                    ActorEdge* edge = actor->find_edge(curr_actor);
                    //renew the movie with the most recent year
                    if (edge->movie->movie_year < movie->movie_year){
                        edge->movie = movie;
                        if (use_weighted_edges)
                            edge->weight = 1 + (MOST_RECENT_YEAR - 
                                movie->movie_year);
                    }
                }
            }
        }
    }
}

/**
 * build the graph if the requirement is to find the actorconnection by bfs
 */
void ActorGraph::buildGraphByYear(int year){
    // loop through the movie map 
    for (auto it = movie_map_by_year[year].begin(); it !=movie_map_by_year[year]
        .end(); it++){
        Movie* curr_movie = it->second;
        std::unordered_map<std::string, ActorNode*> actor_list = curr_movie->
            actor_list;
	//loop through the actor list in each movie
        for (auto it = actor_list.begin(); it != actor_list.end(); it++){
            ActorNode* curr_actor = it->second;
	    //compare each other actor with the previous actor
            for (auto it = actor_list.begin(); it != actor_list.end(); it++){
                // add each other to each other's adj list
                ActorNode* adj_actor = it->second;
                if (adj_actor->actor_name.compare(curr_actor->actor_name) == 0)
                    continue;
                if (!curr_actor->find_actor(adj_actor->actor_name)){
                    curr_actor->adj_actors.insert(std::make_pair(adj_actor->
                        actor_name, adj_actor));
                    adj_actor->adj_actors.insert(std::make_pair(curr_actor->
                        actor_name, curr_actor));
                }
            }
        }
    }
}

/**
 * reset the adj list of each actor node before each iteration
 */
void ActorGraph::reset(){
    for (auto it = actor_map.begin(); it != actor_map.end(); it++){
        std::unordered_map<std::string, ActorNode*> new_adj_actors;
        it->second->adj_actors = new_adj_actors;
    }
}

/**
 * Destructor
 */
ActorGraph::~ActorGraph(){
    //delete all of the actor nodes
    for (auto it = actor_map.begin(); it != actor_map.end(); it++){
        if (it->second != nullptr){
            delete it->second;
            it->second = nullptr;
        }
    }
    //delete all of the movies
    for (auto it = movie_map.begin(); it != movie_map.end(); it++){
        if (it->second != nullptr){
            delete it->second;
            it->second = nullptr;
        }
    }
    //delete all of the edges
    for (auto it = edge_map.begin(); it != edge_map.end(); it++){
        delete *it;
    }
}

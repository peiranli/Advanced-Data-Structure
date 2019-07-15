#include "DisjointSet.h"
/**
 * the method to merge two actors in two sets if they have connections
 */ 
void DisjointSet::merge(ActorNode* actor1, ActorNode* actor2){
    ActorNode* root1 = find(actor1);
    ActorNode* root2 = find(actor2);
    if (root1 == root2)
        return;
    //the root with low rank is merged into the set with highly ranked root 
    if (root1->rank < root2->rank){
        root2->rank += root1->rank;
        root1->parent = root2;
    }
    else{
        root1->rank += root2->rank;
        root2->parent = root1;
    }
}
/**
 * The method to find a actor nodd. While finding, make a path compression
 */ 
ActorNode* DisjointSet::find(ActorNode* actor){
    if (actor != actor->parent){
        //path compression
        actor->parent = find(actor->parent);
    }
    return actor->parent;
}
/**
 * load the input from file and setup the empty set
 */
bool DisjointSet::loadFromFile(const char* in_filename){
    // Initialize the file stream
    std::ifstream infile(in_filename);

    bool have_header = false;

    // keep reading lines until the end of file is reached
    // keep reading lines until the end of file is reached
    while (infile) {
    std::string s;

        // get the next line
        if (!getline(infile, s)) break;
        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        std::istringstream ss(s);
        std::vector <std::string> record;

        while (ss) {
            std::string next;

            // get next string before hitting a tab character and put it in
            // 'next'
            if (!getline(ss, next, '\t')) break;

            record.push_back(next);
        }
        

        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }
        std::string actor_name(record[0]);
        std::string movie_title(record[1]);
        int movie_year = stoi(record[2]);

        //find or create if doesn't exist the actor of input
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

        // find or create if doesn't exist the actor of input
        Movie* movie;
        if (movie_map[movie_year].find(movie_title + std::to_string
            (movie_year))== movie_map[movie_year].end()){
        movie = new Movie(movie_title, movie_year);
        movie_map[movie_year].insert(std::make_pair(movie_title + 
                std::to_string(movie_year), movie));
        }
        else{
            movie = movie_map[movie_year][movie_title + std::to_string
                (movie_year)];
        }
        
        //add movie and actor to each other's hashmap
        actor->add_movie(movie);
        movie->add_actor(actor);
    }

    //check if the file is read correctly
    if (!infile.eof()) {
        std::cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}

/**
 * reset the disjoint set after each connection is done
 */
void DisjointSet::reset(){
    for (auto it = actor_map.begin(); it != actor_map.end(); it++){
        if (it->second != nullptr){
            it->second->parent = it->second;
        }
    }
}

/**
 * destructor
 */
DisjointSet::~DisjointSet(){
    //delete all of the actor nodes
    for (auto it = actor_map.begin(); it != actor_map.end(); it++){
        if (it->second != nullptr){
            delete it->second;
            it->second = nullptr;
        }
    }
    //delete all of the movies
    for (auto it = movie_map.begin(); it != movie_map.end(); it++){
        int key = it->first;
        for (auto it = movie_map[key].begin(); it != movie_map[key].end();
            it++){
            if (it->second != nullptr){
                delete it->second;
                it->second = nullptr;
            }
        }
    }

}

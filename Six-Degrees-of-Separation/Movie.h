#ifndef MOVIE_H
#define MOVIE_H
#include <unordered_map>
#include <string>

/**
  * The ActorNode class is a class to represent every single actor.
  * It contains actor names, the movies he or she in, the actors and
  * actresses that have be in the same movie with him or her, and the
  * other useful parameters.
  */
class ActorNode;

/**
  * The movie class is a class that represents a movie. It has the movie title,
  * the movie year, and other useful parameters.
  */
class Movie{
public:
    std::string movie_title;
    int movie_year;
    std::unordered_map<std::string, ActorNode*> actor_list;

    /**
     * void constructor
     */  
    Movie(){}

    /**
     * constructor thattakes movie title and movie year as input
     */ 
    Movie(std::string movie_title, int movie_year);

    /**
     * return the string format of movie to match the standard output
     */
    std::string to_string();
    
    /** 
     * redifine the == to compare two movies
     */
    bool operator==(Movie* movie)const;

    /**
     * add an actor to the hashmap of the movie
     */
    void add_actor(ActorNode* actor);

    /**
     * destructor
     */
    ~Movie(){}

};


#endif //MOVIE_H

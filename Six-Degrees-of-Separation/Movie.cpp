#include "Movie.h"
#include "ActorNode.h"

 /**
  * constructor thattakes movie title and movie year as input
  */ 
Movie::Movie(std::string movie_title, int movie_year){
    this->movie_title = movie_title;
    this->movie_year = movie_year;
}

 /**
  * return the string format of movie to match the standard output
  */
std::string Movie::to_string(){
    return this->movie_title + std::to_string(this->movie_year);
}

 /** 
  * redifine the == to compare two movies
  */
bool Movie::operator==(Movie* movie)const{
    if (movie->movie_title.compare(this->movie_title) == 0
        && movie->movie_year == this->movie_year)
        return true;
    else
        return false;
}

/**
 * add an actor to the hashmap of the movie
 */
void Movie::add_actor(ActorNode* actor){
    this->actor_list.insert(std::make_pair(actor->actor_name, actor));
}


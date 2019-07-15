#include "ActorNode.h"
#include "ActorEdge.h"
#include "Movie.h"
#define INFINITY 2147483647

/**
 * constructor with actor_name as a input
 */
ActorNode::ActorNode(std::string actor_name){
	this->actor_name = actor_name;
	this->dist = INFINITY;
	this->done = false;
	this->prev_edge = nullptr;
	this->prev_actor = nullptr;
	this->parent = this;
	this->initial_year = 0;
	this->rank = 0;
}
/**
 * redefine the == to compare two actor nodes
 */
bool ActorNode::operator==(ActorNode* actor) const{
	if (actor->actor_name.compare(this->actor_name) == 0)
		return true;
	return false;
}
/**
  * format the output to relate the standard output
  */
std::string ActorNode::to_string(){
	return "(" + this->actor_name + ")--";
}
/**
 * Add a movie to the hashmap of the actor node that contains the movies
 * the actor is in
 */ 
void ActorNode::add_movie(Movie* movie){
	movies.insert(std::make_pair(movie->to_string(),movie));
}
/**
 * check if there is a movie movie in the movie hashmap
 */ 
bool ActorNode::find_movie(Movie* movie){
	if (movies.find(movie->to_string()) != movies.end())
		return true;
	else
		return false;
}
/**
 * check if can find the actor with actor_name in the adj_actor hashmap
 */
bool ActorNode::find_actor(std::string actor_name){
	if (adj_actors.find(actor_name) != adj_actors.end())
		return true;
	else
		return false;
}
/**
 * get the edge that connect the actor and the curr_actor
 */
ActorEdge* ActorNode::find_edge(ActorNode* actor){
	if (edges.find(actor->actor_name) == edges.end())
		return nullptr;
	else
		return edges[actor->actor_name];
}
/**
 * redefine the < to check if the actorname is smaller
 */  
bool ActorNode::operator<(const ActorNode& other){
	return actor_name <= other.actor_name;
}


#include "ActorGraph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#define INFINITY 2147483647


typedef std::pair<int, ActorNode*> actor_pair;

/**
 * class that contains a method to redefine the pair comparison operator
 */
class PairComp{
public:
    //redefine the operator () to get make the priority queue rank the 
    //actor pair with lowest weight in the front
    bool operator()(const actor_pair& lhs,const actor_pair& rhs) const{
        if (lhs.first != rhs.first)
            return lhs.first > rhs.first;
        return *(lhs.second) < *(rhs.second);
    }
};

int main(int argc, char** argv){
    ActorGraph graph;

    //distinguish weighted and unweighted
    bool weighted;
    if (*argv[2] == 'u')
        weighted = false;
    else if (*argv[2] == 'w')
        weighted = true;
    else{
        std::cout << "wrong input" << std::endl;
        return -1;
    }
    
    //check if loading from file succeeds
    bool load_success = graph.loadFromFile(argv[1], weighted, false);

    if (load_success == false){
        std::cout << "fail to setup the graph" << std::endl;
        return -1;
    }

    // Initialize the file stream
    std::ifstream infile(argv[3]);

    bool have_header = false;

    std::ofstream outfile(argv[4]);
    //write header
    outfile << "(actor)--[movie#@year]-->(actor)--..." << std::endl;

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

        // get the next string before hitting a tab character and put it in 
        // 'next'
            if (!getline(ss, next, '\t')) break;

            record.push_back(next);
        }

        if (record.size() != 2) {
            // we should have exactly 2 columns
            continue;
        }

        //get begin and end actors
        std::string actor_name_begin(record[0]);
        std::string actor_name_end(record[1]);

        ActorNode* begin = graph.actor_map[actor_name_begin];
        ActorNode* end = graph.actor_map[actor_name_end];
        if(begin == nullptr || end == nullptr){
            outfile<<"NO PATH"<<std::endl;
            continue;      
        }
        //setup the graph before started
        graph.setUp();
        //check if there is a path of the input in the graph 
        bool finish = false;

        //when the input require unweighted solution
        if (!weighted){
            //BFS
            std::queue<ActorNode*> queue;
            queue.push(begin);
            begin->dist = 0;
            while (!queue.empty()){
                ActorNode* curr_actor = queue.front();
                queue.pop();
                curr_actor->done = true;
              	//check if get the end point of bfs
                if (curr_actor->actor_name.compare(actor_name_end) == 0){
                    finish = true;
                    break;
                }
                for (auto it = curr_actor->adj_actors.begin(); it != 
                    curr_actor->adj_actors.end(); it++){
                    ActorNode* next_actor = it->second;
                    ActorEdge* edge = curr_actor->find_edge(next_actor);
                    if (next_actor->done)
                        continue;
                    //check if the node is visited
                    if (next_actor->dist == INFINITY){
                        next_actor->dist = curr_actor->dist + 1;
                        next_actor->prev_edge = edge;
                        next_actor->prev_actor = curr_actor;
                        queue.push(next_actor);
                    }
                    
                }
                
            }
        }
        // when the input requires weighted output
        else{
            //Dijkstra using redifined min-priority queue 
            std::priority_queue<actor_pair,std::deque<actor_pair>,PairComp>queue;
            begin->dist = 0;
            queue.push(std::make_pair(begin->dist, begin));
            while (!queue.empty()){
                std::pair<int, ActorNode*> curr_actor = queue.top();
                queue.pop();
              	//check if is the end point of traverse
                if (curr_actor.second->actor_name.compare
                     (actor_name_end) == 0){
                      finish = true;
                      break;
                }
                if (!curr_actor.second->done){
                    curr_actor.second->done = true;
                    for (auto it = curr_actor.second->adj_actors.begin(); 
                        it != curr_actor.second->adj_actors.end(); it++){
                        ActorNode* next_actor = it->second;
                        ActorEdge* edge = curr_actor.second->
                            find_edge(next_actor);
                        int movie_year = edge->movie->movie_year;
                        int distance = curr_actor.second->dist + edge->weight;
                        //check if the node is visited
                        if (distance < next_actor->dist){
                            next_actor->prev_edge = edge;
                            next_actor->prev_actor = curr_actor.second;
                            next_actor->dist = distance;
                            queue.push(std::make_pair(distance, next_actor));
                        }
                        
                    }
                   
                }
            }
        }

        //print results

        // if there is a path in the graph according to the input
        if(!finish){
            outfile<<"NO PATH"<<std::endl;
        }
        if(finish){
            std::stack<std::string> output;
            ActorNode* curr = end;
            while (curr != begin){
                //use the prev_edge preset
                ActorEdge* prev_edge = curr->prev_edge;
                output.push(prev_edge->to_string());
                ActorNode* prev_actor = curr->prev_actor;
                output.push(prev_actor->to_string());
                curr = curr->prev_actor;
            }
            while (!output.empty()){
                outfile << output.top();
                output.pop();
            }
            outfile << "(" + end->actor_name + ")" << std::endl;
        }
    }
    infile.close();
    outfile.close();

    return 0;
}

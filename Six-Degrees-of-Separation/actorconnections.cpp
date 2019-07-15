#include "DisjointSet.h"
#include "ActorGraph.h"
#include "Timer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#define INFINITY 2147483647
#define MOST_RECENT_YEAR 2016



int main(int argc, char** argv){
    DisjointSet set;
    ActorGraph graph;

    std::string mode(argv[4]);
    if (mode.compare("ufind") == 0){
        bool load_success = set.loadFromFile(argv[1]);

        if (load_success == false){
            std::cout << "fail to setup the disjoint set" << std::endl;
            return -1;
        }
    }
    if (mode.compare("bfs") == 0){
        bool load_success = graph.loadFromFile(argv[1], false, true);

        if (load_success == false){
            std::cout << "fail to setup the graph" << std::endl;
            return -1;
        }
    }
    //int num_iterations = 10;
    //Timer timer;

    //for(int i=0; i < num_iterations; i++){
    // Initialize the file stream
    std::ifstream infile(argv[2]);

    bool have_header = false;

    std::ofstream outfile(argv[3]);

    //write header
    outfile << "Actor1" << "\t" << "Actor2" << "\t" <<"Year" << std::endl;
	
    //timer.begin_timer();	
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

        std::string actor_name_1(record[0]);
        std::string actor_name_2(record[1]);

        //if the input mode is union find
        if (mode.compare("ufind") == 0){
            ActorNode* actor1 = set.actor_map[actor_name_1];
            ActorNode* actor2 = set.actor_map[actor_name_2];
            if(actor1 == nullptr || actor2 == nullptr)
                continue;
            set.reset();
            bool found = false;
            //get the earliest start year
            int start_year_1 = actor1->initial_year;
            int start_year_2 = actor2->initial_year;
            int start_year = (start_year_1 >= start_year_2) ? start_year_2 : 
                start_year_1;
            //use disjoint list
            int output_year = 0;
            for (int year = start_year; year < MOST_RECENT_YEAR; year++){
                output_year = year;
                for (auto it = set.movie_map[year].begin(); it != set.
                    movie_map[year].end(); it++){
                    Movie* curr_movie = it->second;
                    ActorNode* actor_list_begin = curr_movie->actor_list.begin()
                        ->second;
                    for (auto it = curr_movie->actor_list.begin(); it != 
                        curr_movie->actor_list.end(); it++){
                        set.merge(actor_list_begin, it->second);
                    }
                }
                //if find the end of the path
                if (set.find(actor1) == set.find(actor2)){
                    found = true;
                    break;
                }
            }
            if(found){
                outfile << actor1->actor_name << "\t" << actor2->actor_name << "\t"
                    << output_year << std::endl;
            }else{
                outfile << "NO PATH" << std::endl;
            }
        }

        // if the input mode is bfs
        if (mode.compare("bfs") == 0){
            bool finish = false;
            graph.reset();
            //get the earlist start year
            ActorNode* actor1 = graph.actor_map[actor_name_1];
            ActorNode* actor2 = graph.actor_map[actor_name_2];
            int start_year_1 = actor1->initial_year;
            int start_year_2 = actor2->initial_year;
            int start_year = (start_year_1 >= start_year_2) ? start_year_2 : start_year_1;
            //set up the previous year of graph
            for (int i = 0; i < start_year; i++)
                graph.buildGraphByYear(i);
	    //use bfs to find the actor connection
            int output_year = 0;
            if(actor1 == nullptr || actor2 == nullptr){
                continue;
            }
            for (int year = start_year; year < MOST_RECENT_YEAR; year++){
                output_year = year;
                graph.setUp();
                if (graph.actor_map.find(actor1->actor_name) == graph.actor_map.
                    end()|| graph.actor_map.find(actor2->actor_name) == 
                    graph.actor_map.end())
                    continue;
		// build year by year until the actor is found
                graph.buildGraphByYear(year);
                std::queue<ActorNode*> queue;
                queue.push(actor1);
                actor1->dist = 0;
              	
                while (!queue.empty()){
                    ActorNode* curr_actor = queue.front();
                    queue.pop();
                    curr_actor->done = true;
                  	//find the actor with specific year
                	if (curr_actor->actor_name.compare(actor_name_2) == 0){
                      finish = true;
                      break;
                	}
                    for (auto it = curr_actor->adj_actors.begin(); it != 
                        curr_actor->adj_actors.end(); it++){
                        ActorNode* next_actor = it->second;
                        //check if the actor is visited
                        if (next_actor->done)
                            continue;
                        if (next_actor->dist == INFINITY){
                            next_actor->dist = curr_actor->dist + 1;
                            queue.push(next_actor);
                        }
                        
                    }
                }
                if (!finish){
                    continue;
                }
                else{
                    outfile << actor1->actor_name << "\t" << actor2->actor_name 
                        << "\t" << output_year << std::endl;
                    break;
                }
            }		
        }

    }
    //long long time = timer.end_timer();
    //std::cout << i << "th\t" << time << std::endl;   
    infile.close();
    outfile.close();
    //}
    return 0;
}


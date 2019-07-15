#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <stack>

/**
 * class that reoresents Facebook user that has friends
 * use the information of each useris uid and their friends, we can 
 * show how many common friends two users have
 * this is realized based on hashmap and stack
 */
class User;

std::unordered_map<int, User*> user_list;

/**
 * class that reoresents Facebook user that has friends
 * use the information of each useris uid and their friends, we can 
 * show how many common friends two users have
 */
class User{
public:
    int uid;
    std::unordered_set<int> friend_lists;

    /**
     * constructor with a uid as the input
     */ 
    User(int uid){
        this->uid = uid;
    }

};

/**
 * load the input from file and form the hashmap with users as a social network
 */
bool loadFromFile(const char* in_filename);

/**
 * check if we can find user with specific uid
 */
bool findUser(int uid);

/**
 * destructor to delete the user nodes
 */
void clear_userlist(){
    for (auto it = user_list.begin(); it != user_list.end(); it++){
        if (it->second != nullptr){
            delete it->second;
            it->second = nullptr;
        }
    }
}

int main(int agrc, char** argv){

    bool load_success = loadFromFile(argv[1]);

    if (load_success == false){
        std::cout << "fail to setup the graph" << std::endl;
        return -1;
    }

    // Initialize the file stream
    std::ifstream infile(argv[2]);

    bool have_header = false;

    std::ofstream outfile(argv[3]);

    //write header
    outfile << "userId_1" << "\t" << "userId_2" << "\t" << 
        "Number of mutual friends" << std::endl;

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

        int uid_1 = std::stoi(record[0], nullptr);
        int uid_2 = std::stoi(record[1], nullptr);

        // get the two users
        User* user_1 = user_list[uid_1];
        User* user_2 = user_list[uid_2];

        //no valid input case
        if(user_1==nullptr || user_2 == nullptr){
            outfile<< "NO SUCH USER!"<<std::endl;
            continue;
        }

        int count = 0;
        //check how many common friends they have
        for (auto it = user_1->friend_lists.begin(); it != 
            user_1->friend_lists.end(); it++){
            if (user_2->friend_lists.find(*it) != user_2->friend_lists.end())
                count++;
            }
        //print the result
        outfile << user_1->uid << "\t" << user_2->uid << "\t" 
            << count << std::endl;
    }
    //destructor
    clear_userlist();

    return 0;
}

/**
 * load the input from file and form the hashmap with users as a social network
 */
bool loadFromFile(const char* in_filename){
    // Initialize the file stream
    std::ifstream infile(in_filename);

    bool have_header = false;

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

        int uid_1 = std::stoi(record[0],nullptr);
        int uid_2 = std::stoi(record[1],nullptr);

        // get or create if not exist user1 node
        User* user_1;
        if (!findUser(uid_1)){
            user_1 = new User(uid_1);
            user_list.insert(std::make_pair(uid_1, user_1));
        }
        else
            user_1 = user_list[uid_1];

        //get or create if not exist user2 node
        User* user_2;
        if (!findUser(uid_2)){
            user_2 = new User(uid_2);
            user_list.insert(std::make_pair(uid_2, user_2));
        }
        else
            user_2 = user_list[uid_2];

        //insert user2 to user1's friend list
        user_1->friend_lists.insert(uid_2);

    }

    infile.close();

    return true;
}

/**
 * check if we can find user with specific uid
 */
bool findUser(int uid){
    if (user_list.find(uid) != user_list.end())
        return true;
    else
        return false;
}

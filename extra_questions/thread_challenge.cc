// Totally not an Nvidia interview question - 

/*A.1. Implement a program where there are three threads that are exchanging messages.
- Message body is std::string.- Messages are p2p and have a destination index.
- Each thread reads the messages sent to its index and prints message bodies and then adds a random number of messages,
 each of which is directed to a random destination index (but not to itself).

A.2. Change the implementation so that a thread can send a message in broadcast mode to all other threads.*/


#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
using namespace std;

int counter; // Message num for debuggning

class peer{ // message thread. Got a better name? Send suggestions at shaioren100@gmail.com
    public:
        static vector<peer>peers; // Do not resize during runtime, papa GPT says it's not safe with running threads.

        int ID;
        vector<string>inbox;
        mutex myMutex;
        condition_variable cv;

        void send_message(int target);
        void read_messages();
};



int main(){


    peer p1;
    p1.ID = 0;

    peer::peers.push_back();
    peer::peers.push_back();
    // PSEUDO
    // send message to queue[i]
    // in thread i : 
        // read message in queue - block incoming traffic while reading
        // print each message from queue
        // release block
    
    return 0;
}


void peer::send_message(int target){
    unique_lock<mutex>lock(this->peers[target].myMutex); // Get access to target inbox. Block for others once inside.
    
    // insert message in inbox
    cout << this->ID << " sent to "<< target << "\n";
    this->peers[target].inbox.push_back("message from " + to_string(this->ID) + " , message: " + to_string(counter++));
    
    // notify target
    this->peers[target].cv.notify_one();

    // enter wait state for messages
    this->read_messages();
};

void peer::read_messages(){
    unique_lock<mutex>lock(this->myMutex); // Wait for other treads to release access. Block once reading.

    cout << this->ID << " is reading messages in queue " << "\n";
    
    for (string message: this->inbox){
        cout << this->ID << " is reading: " << message;
    }

    // CONTINUE SENDING MESSAGES
};
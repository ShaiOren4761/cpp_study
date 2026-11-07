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
#include <atomic>
using namespace std;

atomic<int> counter{0}; // Message num for debugging

class peer{
    public:
        static vector<peer>peers; // Do not resize during runtime, papa GPT says it's not safe with running threads.

        // attributes
        int ID = -1;
        vector<string>inbox;
        
        // thread safety tools
        mutex myMutex;
        condition_variable cv;
        
        // methods
        void send_message(int target);
        void read_messages();
};

// Declare in class, define in namespace, use in Main -> ???????????
vector<peer> peer::peers(2); // 2 peers


int main(){

    // Testing for 2 peers

    peer::peers[0].ID = 0;
    peer::peers[1].ID = 1;

    // Launch threads
    vector<thread> threads;

    threads.emplace_back(&peer::send_message, &peer::peers[0], 1);
    threads.emplace_back(&peer::read_messages, &peer::peers[1]);

    /*
    for (peer& p : peer::peers) {
        threads.emplace_back(&peer::read_messages, &p);
    }
    */
    for (thread& t : threads) {
        t.join();
    }

    // PSEUDO
    // send message to queue[i]
    // in thread i : 
        // read message in queue - block incoming traffic while reading
        // print each message from queue
        // release block
    
    return 0;
}


void peer::send_message(int target){
    { // lock scope start
    lock_guard<mutex>lock(this->peers[target].myMutex); // Get access to target inbox. Block for others once inside.

    // insert message in inbox
    cout << this->ID << " sent to "<< target << "\n";
    this->peers[target].inbox.push_back("message from " + to_string(this->ID) + " , message: " + to_string(counter.fetch_add(1)));
    
    // notify target
    this->peers[target].cv.notify_one();
    
    } // lock scope end

    // enter wait state for messages
    this->read_messages();
};

void peer::read_messages(){
    { // lock scope start
    unique_lock<mutex>lock(this->myMutex); // Wait for other treads to release access. Block once reading.
    this->cv.wait(lock, [this] {return !inbox.empty();});

    cout << this->ID << " is reading messages in queue " << "\n";
    
    for (string message: this->inbox){
        cout << this->ID << " is reading: " << message << "\n";
    }
    
    this->inbox.clear();
    } // lock scope end

    if (counter < 5) this->send_message((this->ID-1)*-1); // temp for 2 peers. 0 - 1 * -1 = 1. 1 - 1 * -1 = 0.
};
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
#include <cstdlib>
#include <syncstream>
#include <queue>
using namespace std;


class peer{
    public:
        static vector<peer>peers; // Do not resize during runtime, papa GPT says it's not safe with running threads.

        // attributes
        int ID = -1;
        queue<string>inbox;
        
        // thread safety tools
        mutex myMutex;
        condition_variable cv;
        
        // methods
        void message_loop();
        void send_message(int target, int amount);
        void read_messages();
};

// Declare in class, define in namespace, use in Main -> Profit
vector<peer> peer::peers(3);

atomic<int> counter{0}; // Message num for debugging


int main(){

    // Set peer ID
    int ID{};
    for (peer& p : peer::peers) {
        p.ID = ID++;
    }

    // Launch threads
    vector<thread> threads;
    for (peer& p : peer::peers) {
        threads.emplace_back(&peer::message_loop, &p);
    }

    for (thread& t : threads) {
        t.join();
    }

    // PSEUDO
    // all i peers send message to queue[j] j!=i
    // all peers : 
        // read message in queue
        // print each message from queue
    // roll targets for more message sending
    
    return 0;
}


void peer::message_loop(){

    int target;
    int amount_msg_total;
    int amount_msg_t1;
    int amount_msg_t2;
    int limit = 5;

    while(limit){
        target = rand() % peer::peers.size(); // force new roll every iteration. Otherwise it stays stuck on 1 valid target.

        // Roll message batches (Custom case for 3 peers! Does not scale!)
            // Phase 1: Roll message amount
            amount_msg_total = (rand() % 6) + 1; // I have to limit this otherwise it goes up to MAX INT. Kinda hard to debug that.
            // Phase 2: Roll amount of messages to be sent to first target and calc msgs to 2nd target
            amount_msg_t1 = amount_msg_total - (rand() % (amount_msg_total + 1));
            amount_msg_t2 = amount_msg_total - amount_msg_t1;
            // Phase 3: Roll first target
            while (target == this->ID) target = rand() % peer::peers.size();
            // Phase 4: send messages
            if (amount_msg_t1) this->send_message(target, amount_msg_t1);
            if (amount_msg_t2) this->send_message(3 - this->ID - target, amount_msg_t2);
        
        
        this->read_messages();

        limit--;
    }
}

void peer::send_message(int target, int amount){
    { // lock scope start

        lock_guard<mutex>lock(this->peers[target].myMutex); // Get access to target inbox. Block for others once inside.

        // insert message in inbox
        osyncstream(cout) << this->ID << " is sending " << amount << " messages to "<< target << "\n";
        for (int i=0; i<amount; i++){
            this->peers[target].inbox.push("message from peer " + to_string(this->ID) + " , total message number: " + to_string(counter.fetch_add(1)));
        }

    } // lock scope end

    // notify target
    this->peers[target].cv.notify_one();
};

void peer::read_messages(){
    { // lock scope start

        unique_lock<mutex>lock(this->myMutex); // Wait for other treads to release access. Block once reading.
        this->cv.wait(lock, [this] {return !inbox.empty();});

        osyncstream(cout) << this->ID << " is reading messages in queue " << "\n";
        
        while (!this->inbox.empty()){
            string message = this->inbox.front();
            osyncstream(cout) << this->ID << " is reading: " << message << "\n";
            this->inbox.pop();
        }

    } // lock scope end

};
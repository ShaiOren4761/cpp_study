// Totally not an Nvidia interview question - 

/*A.1. Implement a program where there are three threads that are exchanging messages.
- Message body is std::string.- Messages are p2p and have a destination index.
- Each thread reads the messages sent to its index and prints message bodies and then adds a random number of messages,
 each of which is directed to a random destination index (but not to itself).

A.2. Change the implementation so that a thread can send a message in broadcast mode to all other threads.*/


// PSEUDO
// all i peers send message to queue[j] j!=i
// all peers : 
    // read message in queue
    // print each message from queue
// roll targets for more message sending


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


class Peer{
    public:
        static vector<Peer>peers; // Do not resize during runtime, papa GPT says it's not safe with running threads.

        // Construct Destruct
        explicit Peer(int id) : id_(id) {}
        ~Peer() = default;
        // methods
        void MessageLoop();
        void SendMessages(int target, int amount);
        void ReadMessages();
        // getter setter
        int GetID() {return this->id_;}
        void SetID(int id) {this->id_ = id;}
    private:
        // attributes
        int id_ = -1;
        queue<string>inbox_;
        
        // thread safety tools
        mutex my_mutex_;
        condition_variable cv_;
                    
};

// Declare in class, define in namespace, use in Main -> Profit
vector<Peer> Peer::peers(3);

atomic<int> counter{0}; // Message num for debugging


int main(){

    // Set peer ID
    int ID{};
    for (Peer& p : Peer::peers) {
        p.SetID(ID++);
    }

    // Launch and join threads
    vector<thread> threads;
    for (Peer& p : Peer::peers) {
        threads.emplace_back(&Peer::MessageLoop, &p);
    }

    for (thread& t : threads) {
        t.join();
    }

    return 0;
}


void Peer::MessageLoop(){

    int target;
    int amount_msg_total;
    int amount_msg_t1;
    int amount_msg_t2;
    int limit = 5;

    while(limit){
        target = rand() % Peer::peers.size(); // force new roll every iteration. Otherwise it stays stuck on 1 valid target.

        // Roll message batches (Custom case for 3 peers! Does not scale!)
        // Phase 1: Roll message amount
        amount_msg_total = (rand() % 6) + 1; // I have to limit this otherwise it goes up to MAX INT. Kinda hard to debug that.
        // Phase 2: Roll amount of messages to be sent to first target and calc msgs to 2nd target
        amount_msg_t1 = amount_msg_total - (rand() % (amount_msg_total + 1));
        amount_msg_t2 = amount_msg_total - amount_msg_t1;
        // Phase 3: Roll first target
        while (target == this->id_) target = rand() % Peer::peers.size();
        // Phase 4: send messages
        if (amount_msg_t1) this->SendMessages(target, amount_msg_t1);
        if (amount_msg_t2) this->SendMessages(3 - this->id_ - target, amount_msg_t2);
        
        
        this->ReadMessages();

        limit--;
    }
}

void Peer::SendMessages(int target, int amount){
    { // lock scope start

        lock_guard<mutex>lock(this->peers[target].my_mutex_); // Get access to target inbox. Block for others once inside.

        // insert message in inbox
        osyncstream(cout) << this->id_ << " is sending " << amount << " messages to "<< target << "\n";
        for (int i=0; i<amount; i++){
            this->peers[target].inbox_.push("message from peer " + to_string(this->id_) + " , total message number: " + to_string(counter.fetch_add(1)));
        }

    } // lock scope end

    // notify target
    this->peers[target].cv_.notify_one();
};

void Peer::ReadMessages(){
    { // lock scope start

        unique_lock<mutex>lock(this->my_mutex_); // Wait for other treads to release access. Block once reading.
        this->cv_.wait(lock, [this] {return !inbox_.empty();});

        osyncstream(cout) << this->id_ << " is reading messages in queue " << "\n";
        
        while (!this->inbox_.empty()){
            string message = this->inbox_.front();
            osyncstream(cout) << this->id_ << " is reading: " << message << "\n";
            this->inbox_.pop();
        }

    } // lock scope end

};
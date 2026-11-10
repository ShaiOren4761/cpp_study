/*A.1. Implement a program where there are three threads that are exchanging messages.
- Message body is std::string.- Messages are p2p and have a destination index.
- Each thread reads the messages sent to its index and prints message bodies and then adds a random number of messages,
 each of which is directed to a random destination index (but not to itself).

A.2. Change the implementation so that a thread can send a message in broadcast mode to all other threads.*/


// PSEUDO
// peer sends messages to other peers
    // sender asks target to place messages in their queue
// peer reads their own messages, prints, back to start
// roll targets for more message sending


#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <cstdlib>
#include <queue>
using namespace std;


class Peer{
    public:
        static vector<Peer>peers; // Do not resize during runtime, papa GPT says it's not safe with running threads.

        // Constructors Destructor
        Peer() = default;
        explicit Peer(int id) : id_(id) {}
        ~Peer() = default;

        // methods
        void MessageLoop();
        void SendMessages();
        void InsertMessages(int sender, int amount);
        void ReadMessages();
        void Broadcast();

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

    int limit = 5;

    while(limit){

        this->SendMessages();
        this->ReadMessages();

        limit--;
    }
}

void Peer::SendMessages(){ // sender asks target to place X messages in their queue
    int target = rand() % Peer::peers.size();
    int amount_msg_total;
    int amount_msg_t1;
    int amount_msg_t2;        

    // Roll message batches (Custom case for 3 peers! Does not scale!)
    
    // Phase 1: Roll message amount
    amount_msg_total = (rand() % 6) + 1; // 1 - 6 messages total. Arbitrary limit for debugging ease.

    // Phase 2: Roll amount of messages to be sent to first target and calc msgs to 2nd target
    amount_msg_t1 = amount_msg_total - (rand() % (amount_msg_total + 1));
    amount_msg_t2 = amount_msg_total - amount_msg_t1;
    
    // Phase 3: Roll first target
    while (target == this->id_) target = rand() % Peer::peers.size();
    
    // Phase 4: send messages
    if (amount_msg_t1) peers[target].InsertMessages(this->id_, amount_msg_t1);
    if (amount_msg_t2) peers[3 - this->id_ - target].InsertMessages(this->id_, amount_msg_t2); // index calc is just 0 + 1 + 2 = 3 parameterized.
        
};

void Peer::InsertMessages(int sender, int amount){
    { // lock scope start

        lock_guard<mutex>lock(this->my_mutex_);

        cout << sender << " is sending " << amount << " messages to "<< this->id_ << "\n";
        for (int i=0; i<amount; i++){
            this->inbox_.push("message from peer " + to_string(sender) + " , total message number: " + to_string(counter.fetch_add(1)));
        }

    } // lock scope end

    // notify target
    this->cv_.notify_one();
}

void Peer::ReadMessages(){
    { // lock scope start

        unique_lock<mutex>lock(this->my_mutex_); // Wait for other treads to release access. Block once reading.
        this->cv_.wait(lock, [this] {return !inbox_.empty();});

        cout << this->id_ << " is reading messages in queue " << "\n";
        
        while (!this->inbox_.empty()){
            string message = this->inbox_.front();
            cout << this->id_ << " is reading: " << message << "\n";
            this->inbox_.pop();
        }

    } // lock scope end

};


void Peer::Broadcast(){
    // Broadcast 1 message to all other peers
    int target = rand() % Peer::peers.size();
    while (target == this->id_) target = rand() % Peer::peers.size();

    peers[target].InsertMessages(this->id_, 1);
    peers[3 - this->id_ - target].InsertMessages(this->id_, 1); 
}

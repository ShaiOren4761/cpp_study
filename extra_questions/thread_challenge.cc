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
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <cstdlib>
#include <queue>
#include <csignal>
#include <chrono>
using namespace std;


class Peer{
    public:
        static Peer peers[3];

        // Constructors Destructor
        Peer() : id_(id_gen++) {}
        ~Peer() { t.~thread(); }

        // methods
        void MessageLoop();
        void SendMessages();
        void InsertMessages(int sender, int amount);
        void ReadMessages();
        void Broadcast();
        void InitThread();
        void JoinThread();

        // getter setter
        int GetID() {return this->id_;}
        void SetID(int id) {this->id_ = id;}

    private:
        static int id_gen;
        // attributes
        int id_ = -1;
        queue<string>inbox_;
        thread t;
        
        // thread safety tools
        mutex my_mutex_;
        condition_variable cv_;
                    
};

// Peer statis members init
int Peer::id_gen = 0;
Peer Peer::peers[3];

atomic<int> counter{0}; // Message num for debugging
atomic<bool> interrupt_flag = false;

void HandleSignal(int signal);

int main(){

    // Launch and join threads
    for (Peer& p : Peer::peers) {
        p.InitThread();
    }
    
    // Wait for user interrupt (No other way to stop the program)
    signal(SIGINT, HandleSignal);
    while(!interrupt_flag.load()){
        this_thread::sleep_for(chrono::milliseconds(50));
    }

    // Join threads to allow graceful exit
    for (Peer& p : Peer::peers) {
        p.JoinThread();
    }

    return 0;
}


void Peer::MessageLoop(){

    while(true){
        if (rand()%2 == 0) this->SendMessages(); else this->Broadcast();
        this->ReadMessages();
    }
}

void Peer::SendMessages(){ // sender asks target to place X messages in their queue
    int target = rand() % 3;
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
    while (target == this->id_) target = rand() % 3;
    
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
    int target = rand() % 3;
    while (target == this->id_) target = rand() % 3;

     cout << this->id_ << " is broadcasting to all peers" << "\n";
    peers[target].InsertMessages(this->id_, 1);
    peers[3 - this->id_ - target].InsertMessages(this->id_, 1); 
}

void Peer::InitThread(){
    if (!this->t.joinable()) t = thread(&Peer::MessageLoop, this);
}

void Peer::JoinThread(){
    if (this->t.joinable()) this->t.join();
}

void HandleSignal(int signal){
    cout << "Interrupt!";
    Peer::peers[0].~Peer();
    Peer::peers[1].~Peer();
    Peer::peers[2].~Peer();
}



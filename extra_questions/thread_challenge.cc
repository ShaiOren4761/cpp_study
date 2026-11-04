/*A.1. Implement a program where there are three threads that are exchanging messages.
- Message body is std::string.- Messages are p2p and have a destination index.
- Each thread reads the messages sent to its index and prints message bodies and then adds a random number of messages,
 each of which is directed to a random destination index (but not to itself).

A.2. Change the implementation so that a thread can send a message in broadcast mode to all other threads.*/


#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;


mutex mtx1; // TODO - convert to class - queue of messages + relevant lock_guard mtx
mutex mtx2;

int count = 0;

void send_message(int i, vector<vector<string>>&inboxes);
void read_messages(int i, vector<vector<string>>&inboxes);

int main(){

    // Init inboxes
    vector<vector<string>> inboxes; // TODO vector<queue<string>>
    
    vector<string>t1_in;
    vector<string>t2_in;
    inboxes.push_back(t1_in);
    inboxes.push_back(t2_in);
  
    // Launch threads
    thread t1(send_message, 1, ref(inboxes));
    thread t2(send_message, 2, ref(inboxes));
 
    t1.join();
    t2.join();

    
    // PSEUDO
    // send message to queue[i]
    // in thread i : 
        // read message in queue - block incoming traffic while reading
        // print each message from queue
        // release block
    
    return 0;
}


void send_message(int i, vector<vector<string>>&inboxes){
    lock_guard<mutex>lock(mtx);

    // determine destination (2 threads..)
    int j = 1;
    if (i == 1) j = 2;


    // insert message in inbox
    cout << i << " sent to "<< j << "\n";
    inboxes[j-1].push_back("message from " + to_string(i) + " , message: " + to_string(count++));
    
    // launch message read - HOW DOES ONE NOTIFY ANOTHER THREAD TO DO A THING?
    if (count < 2) read_messages(j-1, inboxes);
}

void read_messages(int i, vector<vector<string>>&inboxes){
    mtx.lock();

    cout << i << " read message in queue " << "\n";
    cout << inboxes[i][0];

    mtx.unlock(); 
}
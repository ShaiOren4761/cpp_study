#include <iostream>
#include <queue>

using namespace std;


void addNum(int num) {
    
}

double findMedian() {
   return 0; 
}

void printPQ(priority_queue<int> pq) {
    cout << "[ ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << "]\n";
}

int main(){
    priority_queue<int> heap(less<int>{}, {10,20,30,40});
    printPQ(heap);
}


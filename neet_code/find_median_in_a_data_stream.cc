#include <iostream>
#include <queue>

using namespace std;

class MedianFinder {
    public:
        priority_queue<int> left_datas; // max heap
        priority_queue<int, vector<int>, greater<int>> right_datas; // min heap

        MedianFinder(){};
            
        void addNum(int num) {
            // add by case:
            // empty heaps - initialize
            if (left_datas.empty() && right_datas.empty()) this->left_datas.push(num);
            // otherwise, maintain heaps at the center of the data stream
            else{
                if (num < left_datas.top()){
                    left_datas.push(num);
                }
                else right_datas.push(num);

                // check imbalance - heap sizes can't differ in more than 1 element
                if (left_datas.size()+2 == right_datas.size()){ // left too small, pop one from right
                    left_datas.push(right_datas.top());
                    right_datas.pop();
                }
                else if (left_datas.size() == right_datas.size()+2){ // right too small, pop one from left
                    right_datas.push(left_datas.top());
                    left_datas.pop();
                }
            }
        }

        double findMedian() {
            if (left_datas.size() == right_datas.size()) return (left_datas.top() + right_datas.top()) / 2.0;
            else{
                if (left_datas.size()+1 == right_datas.size()) return right_datas.top();
                else return left_datas.top();
            } 
        }

        
};


template<typename T, typename Container, typename Compare>
void printPQ(priority_queue<T, Container, Compare> pq) {
    cout << "[ ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << "]\n";
}

int main(){
    MedianFinder md;
    
    md.addNum(1);

    printPQ(md.left_datas);
    printPQ(md.right_datas);
    cout << md.findMedian() << "\n";

    md.addNum(3);

    printPQ(md.left_datas);
    printPQ(md.right_datas);
    cout << md.findMedian() << "\n";
    
    md.addNum(2);

    printPQ(md.left_datas);
    printPQ(md.right_datas);
    cout << md.findMedian() << "\n";
}


#include <iostream>
#include <set>

int main(){
    std::set<[int]>s;
    s.emplace(3);

    for (int num : s){
        std::cout << num << "\n";
    }
}
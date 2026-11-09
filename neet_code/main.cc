#include <iostream>
#include <vector>
using namespace std;



int main(){
    
    
    vector<int>letters(26); // 97 ascii value of 'a'
    string word = "abcdef";

    for (char c: word){
        letters[int(c)-97]++;
    }

    for (int x: letters){
        cout << x << " ";
    }
    cout << "\n";
    return 0;
}
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

bool isAnagram(string s, string t) {
    vector<int>s_letters(26);
    vector<int>t_letters(26);

    for (char c: s){
        s_letters[int(c)-97]++;
    }

    for (char c: t){
        t_letters[int(c)-97]++;
    }

    return s_letters == t_letters;
}
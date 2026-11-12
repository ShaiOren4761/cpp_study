#include <iostream>
#include <string>
#include <algorithm>

bool isPalindrome(std::string s) {
    if (s.length() < 2) return true;
    
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });

    int lptr = 0;
    int rptr = s.length()-1;

    while (lptr < rptr){
        while(!isalnum(s[lptr]) && (lptr < rptr)) lptr++;
        while(!isalnum(s[rptr]) && (lptr < rptr)) rptr--;
        
        if (s[lptr] != s[rptr]) return false;
        lptr++;
        rptr--;
    }

    return true;
}


int main(){
    std::cout << std::boolalpha;
    std::cout << isPalindrome("Was it a car or a cat I saw?") << "\n";
}
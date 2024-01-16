#include <bits/stdc++.h>

using namespace std;

void login(int noOfDigitsForThePalindrome, string userId, string password) {
    for(int i = 0; i < userId.size(); i++) {    
        if(!isalnum(userId[i])) {
            cout<<"Invalid input\n";
            return;
        }
    }
    for(int i = 0; i < password.size(); i++) {    
        if(!isalnum(password[i])) {
            cout<<"Invalid input\n";
            return;
        }
    }
    if(noOfDigitsForThePalindrome <= 0) {
        cout<<"Invalid input\n";
        return;
    }

    string palindromeans = "1";
    for(int i = 0; i < noOfDigitsForThePalindrome - 2; i++) palindromeans += "0";
    if(noOfDigitsForThePalindrome != 1) palindromeans += "1";
    for(int i = 1; i <= 5; i++) {
        string tempUser = "user" + to_string(i);

        string tempPass = "pass" + to_string(i);
        // cout<<tempUser<<" "<<tempPass<<endl;
        if(userId == tempUser && password == tempPass) {
            cout<<"Welcome " << userId <<" and the generated token is: token-" << palindromeans << endl;
            return;
        }
    }
    cout<<"UserId or password is not valid, pls try again." << endl;
}

int main() {
    login(3, "user1", "pass1");
    return 0;
}
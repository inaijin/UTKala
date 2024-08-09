#include "signup.hpp"
#include <iostream>
#include <stdexcept>
#include "account.hpp"
#include "utilities.hpp"

using namespace std;

Account* signup(vector<Account>& accounts) {
    string username, password, role, address;
    char init; cin >> init;
    if(init != '?')
        throw runtime_error("? error");
    string choice; int count = 0;
    while(true) {
        if(count == 4)
            break; 
        cin >> choice;
        if(choice == "username") {
            cin >> username;
            if(isDupAccountUser(accounts, username))
                throw runtime_error("Username Already In Use !");
            count++;
        } else if(choice == "password") {
            cin >> password;
            count++;
        } else if(choice == "role") {
            cin >> role;
            count++;
        } else if(choice == "address") {
            cin >> address;
            count++;
        } else {
            throw runtime_error("Invalid Choice For Signin !");
        }
    }
    accounts.push_back(Account(username, password, address, role));
    cout << "OK" << endl;
    return getUsrPasAccount(accounts, username);
}
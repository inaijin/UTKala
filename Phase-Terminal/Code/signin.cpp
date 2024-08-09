
#include "signin.hpp"
#include "account.hpp"
#include "utilities.hpp"
#include <iostream>
#include <stdexcept>

Account* signin(vector<Account>& accounts) {
    string username, password;
    initQ();
    string choice; int count = 0; bool usr = false; bool pass = false;
    while(true) {
        cin >> choice;
        if(choice == "username") {
            cin >> username;
            if(!isDupAccountUser(accounts, username))
                throw 0;
            usr = true;
        }else if(choice == "password") {
            cin >> password;
            pass = true;
        } else {
            throw runtime_error("Invalid Command");
        }
        if(pass && usr)
            break;
    }
    if(!isUsrPassCorrect(accounts, username, password))
        throw 1.5; 
    cout << "OK" << endl;
    return getUsrPasAccount(accounts, username);
}
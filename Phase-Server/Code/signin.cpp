
#include "signin.hpp"
#include "account.hpp"
#include "utilities.hpp"
#include <iostream>
#include <stdexcept>

Account* signin(vector<Account>& accounts, string username, string password) {
    if(!isDupAccountUser(accounts, username))
        throw 0;
    if(!isUsrPassCorrect(accounts, username, password))
        throw 1.5; 
    cout << "OK" << endl;
    return getUsrPasAccount(accounts, username);
}
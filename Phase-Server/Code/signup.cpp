#include "signup.hpp"
#include <iostream>
#include <stdexcept>
#include "account.hpp"
#include "utilities.hpp"

using namespace std;

Account* signup(vector<Account>& accounts, string username, string password, string role, string address) {
    if(isDupAccountUser(accounts, username))
        throw 2;
    accounts.push_back(Account(username, password, address, role));
    cout << "OK" << endl;
    return getUsrPasAccount(accounts, username);
}
#include "account.hpp"
#include "signup.hpp"
#include "signin.hpp"
#include "post.hpp"
#include "getdel.hpp"
#include "utilities.hpp"
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <system_error>
#include <vector>

// AP-UTKala-Phase-Terminal

using namespace std;

void initUTKala(vector<Account>& accounts) {
    string command; bool loggFlag = false;
    string errorBreakCommand = "NF";
    Account* loggAcc;
        while(errorBreakCommand != "NF" || cin >> command) {
            if(errorBreakCommand != "NF") {
                command = errorBreakCommand;
                errorBreakCommand = "NF";
            }
            try {
                if(!loggFlag && command == "POST") {
                    loggAcc = post(accounts);
                    if(loggAcc != NULL)
                        loggFlag = true;
                } else if(loggFlag && command == "POST") {
                    Account* temp;
                    temp = post(accounts, *loggAcc, loggFlag);
                    if(temp == NULL) { loggFlag = false; }
                } else if(loggFlag && command == "GET") {
                    get(*loggAcc, accounts);
                } else if(loggFlag && command == "DELETE") {
                    del(*loggAcc, accounts);
                } else if(loggFlag && command == "PUT") {
                    put(*loggAcc, accounts);       
                } else {
                    cout << "Bad Request" << endl;
                    errorBreakCommand = errorClearCin();
                    break;
                }
            } catch(...) {
                errorBreakCommand = errorClearCin();
            }
        }
        if(accounts.size() != 0)
            freeMemory(accounts);
}

int main() {
    vector<Account> accounts;
    initUTKala(accounts);
    return 0;
}
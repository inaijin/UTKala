#include "post.hpp"
#include "account.hpp"
#include "signup.hpp"
#include "signin.hpp"
#include "utilities.hpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

template<typename P>
void tryFunc(P func) {
    try{
        func();
    } catch(runtime_error& ex) {
        cout << "Bad Request" << endl;
        throw;
    } catch(double) {
        cout << "Permission Denied" << endl;
        throw;
    } catch(int) {
        cout << "Not Found" << endl;
        throw;
    }
}

Account* post(vector<Account>& accounts, Account& acc, bool loggedFlag) {
    string commnad; 
    while(!loggedFlag && cin >> commnad) {
        if(commnad == "signup") {
            try {
                Account* acc = signup(accounts);
                return acc;
            } catch (runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
            }
            return NULL;
        } else if(commnad == "login") {
            try {
                Account* acc = signin(accounts);
                return acc;
            } catch (runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
            } catch (double) {
                cout << "Permission Denied" << endl;
                throw;
            } catch (int) {
                cout << "Not Found" << endl;
                throw;
            }
        } else {
            cout << "Bad Request" << endl;
            throw runtime_error("Unknown Command");
        }
    }
    string command;
    while(loggedFlag && cin >> command) {
        if(command == "logout") {
            cout << "OK" << endl;
            if(acc.isSeller())
                deleteCart(acc);
            else
                deleteFilters();
            return NULL;
        } else if(command == "increase_credit" && !acc.isSeller()) {
            initQ();
            cin >> command;
            if(command == "amount") {
                int ammount; cin >> ammount;
                if(ammount <= 0) {
                    cout << "Bad Request" << endl;
                    return &acc; 
                }
                acc.increase_credit(ammount);
                cout << "OK" << endl;
                return &acc;
            } else {
                throw runtime_error("Unknown Command 1");
            }
        } else if(command == "add_item" && acc.isSeller()) {
            try {
                initQ();
                addItem(acc, accounts);
                return &acc;
            } catch(runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
                return &acc;
            }
        } else if(command == "add_to_cart" && !acc.isSeller()) {
            try {
                initQ();
                buyItem(acc, listItems(accounts, false), accounts);
                return &acc;
            } catch(runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
            } catch(int) {
                cout << "Not Found" << endl;
                throw;
            }
            return &acc;
        } else if(command == "refund" && !acc.isSeller()) {
            try {
                initQ();
                refund(acc, accounts);
                cout << "OK" << endl;
                return &acc;
            } catch(runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
            } catch(int) {
                cout << "Permission Denied" << endl;
                throw;
            } catch(double) {
                cout << "Not Found" << endl;
                throw;
            }
            return &acc;
        } else if(command == "comment" && !acc.isSeller()) {
            try {
                initQ();
                addComment(accounts, acc);
                cout << "OK" << endl;
            } catch(runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
            } catch(double) {
                cout << "Not Found" << endl;
                throw;
            }
            return &acc;
        } else if(command == "rate" && !acc.isSeller()) {
            try {
                initQ();
                rateItem(accounts, acc);
                cout << "OK" << endl;
            } catch(runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
            } catch(double) {
                cout << "Not Found" << endl;
                throw;
            } catch(int) {
                cout << "Permission Denied" << endl;
                throw;
            }
            return &acc;
        } else if(command == "rate_filter" && !acc.isSeller()) {
            try {
                initQ();
                filterByRate(accounts);
                cout << "OK" << endl;
            } catch(runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
            }
            return &acc;
        } else if(command == "price_filter" && !acc.isSeller()) {
            try {
                initQ();
                filterByPrice(accounts);
                cout << "OK" << endl;
            } catch(runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
            }
            return &acc;
        } else if(command == "category_filter" && !acc.isSeller()) {
            try {
                initQ();
                filterByCategory(accounts);
                cout << "OK" << endl;
            } catch(runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
            } catch(double) {
                cout << "Not Found" << endl;
                throw;
            }
            return &acc;
        } else if(command == "package_offer" && acc.isSeller()){
            try {
                initQ();
                addPackageOffer(acc);
                cout << "OK" << endl;
            } catch(runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
            } catch(double) {
                cout << "Not Found" << endl;
                throw;
            }
            return &acc;
        } else if(command == "category_offer" && acc.isSeller()){
            try {
                initQ();
                addCategoryOffer(acc);
                cout << "OK" << endl;
            } catch(runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
            } catch(double) {
                cout << "Not Found" << endl;
                throw;
            }
            return &acc;
        } else if(command == "total_cost_offer" && acc.isSeller()){
            try {
                initQ();
                addTotalCostOffer(acc);
                cout << "OK" << endl;
            } catch(runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
            }
            return &acc;
        } else if(command == "purchase_cart" && !acc.isSeller()) {
            try {
                initQ();
                purchaseCart(acc, accounts);
                deleteCart(acc);
            } catch(runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
            }
            return &acc;
        } else {
            cout << "Bad Request" << endl;
            throw runtime_error("Logged In Cannot Sign In");
        }
    }
    return NULL;
}
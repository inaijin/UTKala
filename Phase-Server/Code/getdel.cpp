#include "getdel.hpp"
#include "account.hpp"
#include "utilities.hpp"
#include <stdexcept>
#include <vector>

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

void get(Account loggedin, vector<Account>& accounts) {
    string command;
    while(cin >> command) {
        if(command == "wallet_balance" && !loggedin.isSeller()) {
            cout << "wallet balance : " << loggedin.getBalance() << endl;
            return;
        } else if(command == "list_items" && !loggedin.isSeller()) {
            try {
                initQ();
                listItems(accounts, true);
                return;
            } catch (runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
            } catch (double) {
                cout << "Empty" << endl;
                throw;
            } catch (int) {
                cout << "Not Found" << endl;
                throw;
            }
            return;
        } else if(command == "list_purchased" && !loggedin.isSeller()) {
            try {
                listPurcheses(loggedin);
            } catch(int) {
                cout << "Empty" << endl;
                throw;
            }
            return;
        } else if(command == "list_items" && loggedin.isSeller()) {
            try {
            initQ();
            listItemsSeller(loggedin);
            } catch(int) {
                cout << "Empty" << endl;
                throw;
            }
            return;
        } else if(command == "list_transactions" && loggedin.isSeller()) {
            try {
            listTransactions(accounts, loggedin);
            } catch(int) {
                cout << "Empty" << endl;
                throw;
            }
            return;
        } else if(command == "revenue" && loggedin.isSeller()) {
            getSellerRevenue(loggedin);
            return;
        } else if(command == "list_offers" && !loggedin.isSeller()) {
            try {
                initQ();
                listOffersSeller(accounts);
            } catch(runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
            } catch(int) {
                cout << "Not Found" << endl;
                throw;
            } catch(double) {
                cout << "Empty" << endl;
                throw;
            }
            return;
        } else {
            cout << "Bad Request" << endl;
            throw runtime_error("Unkown Command");
        }
    }
}

void del(Account& loggedin, vector<Account>& accounts) {
    string command;
    while(cin >> command) {
        if(command == "item" && loggedin.isSeller()) {
            try {
            initQ();
            deleteItem(loggedin, accounts);
            } catch(int) {
                cout << "Not Found" << endl;
                throw;
            } catch(double) {
                cout << "Permission Denied" << endl;
                throw;
            }
            return;
        } else if(command == "filters") {
            deleteFilters();
            cout << "OK" << endl;
            return;
        } else if(command == "cart") {
            deleteCart(loggedin);
            cout << "OK" << endl;
            return;
        } else if(command == "offers") {
            try {
                initQ();
                deleteOffer(loggedin, accounts);
                cout << "OK" << endl;
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
            return;
        } else {
            cout << "Bad Request" << endl;
            throw runtime_error("Unkown Command");
        }
    }
}

void put(Account& acc, vector<Account>& accounts) {
    string command;
    while(cin >> command) {
        if(command == "item_price" && acc.isSeller()) {
            try {
                initQ();
                changePrice(acc, accounts);
            } catch(runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
            } catch(int) {
                cout << "Not found" << endl;
                throw;
            } catch(double) {
                cout << "Permission Denied" << endl;
                throw;
            }
            return;
        } else if(command == "item_quantity" && acc.isSeller()) {
            try {
                initQ();
                changeQuantity(acc, accounts);
            } catch(runtime_error& ex) {
                cout << "Bad Request" << endl;
                throw;
            } catch(int) {
                cout << "Not found" << endl;
                throw;
            } catch(double) {
                cout << "Permission Denied" << endl;
                throw;
            }
            return;
        } else {
            cout << "Bad Request" << endl;
            throw runtime_error("Unkown Command");
        }
    }
}
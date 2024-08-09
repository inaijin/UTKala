#ifndef _UTKALAHANDELER_HPP_
#define _UTKALAHANDELER_HPP_

#include "Server/APHTTP/server/route.hpp"
#include "Server/APHTTP/server/server.hpp"
#include "Server/APHTTP/utils/request.hpp"
#include "Server/APHTTP/utils/response.hpp"
#include "account.hpp"
#include "utilities.hpp"
#include <iostream>
#include <vector>

class UTkala {
public:
    static vector<Account> accounts;
    static Account* loggAcc;
private:

};

class Error : public RequestHandler {
public:
    Error(string errorMassage__) : errorMassage(errorMassage__) {};
    Response* callback(Request*);
private:
    string errorMassage;
};

class Home : public RequestHandler {
public:
    Response* callback(Request*);
private:

};

class ErrorWithURL : public RequestHandler {
public:
    ErrorWithURL(string failMessage__, string url__) {
        errorMessage = failMessage__;
        url = url__;
    }
    Response* callback(Request*);
private:
    string errorMessage;
    string url;
};

class Success : public RequestHandler {
public:
    Success(string successMassage__, string url__) {
        successMassage = successMassage__;
        url = url__;
    }
    Response* callback(Request*);
private:
    string successMassage;
    string url;
};

class SignUpHandeler : public RequestHandler {
public:
    SignUpHandeler(vector<Account>& accounts__) : accounts(&accounts__) {};
    Response* callback(Request*);
private:
    vector<Account>* accounts;
};

class SignUp : public RequestHandler {
public:
    SignUp(vector<Account>& accounts__) : accounts(&accounts__) {};
    Response* callback(Request*);
private:
    vector<Account>* accounts;
};

class SignInHandeler : public RequestHandler {
public:
    SignInHandeler(vector<Account>& accounts__) : accounts(&accounts__) {};
    Response* callback(Request*);
private:
    vector<Account>* accounts;
};

class SignIn : public RequestHandler {
public:
    SignIn(vector<Account>& accounts__) : accounts(&accounts__) {};
    Response* callback(Request*);
private:
    vector<Account>* accounts;
};

class SellerHub : public RequestHandler {
public:
    Response* callback(Request*);
private:

};

class BuyerHub : public RequestHandler {
public:
    Response* callback(Request*);
private:

};

class AddItemHandeler : public RequestHandler {
public:
    Response* callback(Request*);
private:

};

class AddItem : public RequestHandler {
public:
    AddItem(vector<Account> accounts__) {
        accounts = &accounts__;
    }
    Response* callback(Request*);
private:
    vector<Account>* accounts;
};

class WalletHandeler : public RequestHandler {
public:
    Response* callback(Request*);
private:

};

class Wallet : public RequestHandler {
public:
    Response* callback(Request*);
private:

};

class ShowItemsHandeler : public RequestHandler {
public:
    Response* callback(Request*);
private:

};

class BuyItemHandeler : public RequestHandler {
public:
    Response* callback(Request*);
private:

};

class AddItemToCart : public RequestHandler {
public:
    Response* callback(Request*);
private:

};

class BuyItem : public RequestHandler {
public:
    Response* callback(Request*);
private:

};

class DeleteCart : public RequestHandler {
public:
    Response* callback(Request*);
private:

};

class ListPurchases : public RequestHandler {
public:
    Response* callback(Request*);
private:

};

#endif
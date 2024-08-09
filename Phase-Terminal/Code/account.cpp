#include "account.hpp"
#include "person.hpp"
#include <stdexcept>
#include <vector>

using namespace std;

Account::Account(string username__, string password__, string address__, string role__){
    password = password__;
    if(role__ == "seller") {
        Seller *seller = new Seller(username__, address__);
        person = seller;
    } else if(role__ == "buyer") {
        Buyer *buyer = new Buyer(username__, address__);
        person = buyer;
    } else {
        throw runtime_error("Invalid Role !");
    }
}

bool Account::filterR = false;
bool Account::filterP = false;
bool Account::filterC = false;
vector<Item*> Account::filteredItems = {};

void Account::freeMemoryAcc() {
    person->freeMemorySeller();
    delete person;
}

bool Account::isDupUser(string __username) {
    if(__username == person->getUser())
        return true;
    return false;
}

bool Account::isDupPass(string __password) {
    if(__password == password)
        return true;
    return false;
}

bool Account::isSeller() {
    if(person->isSeller())
        return true;
    return false;
}

void Account::increase_credit(int ammount) { person->increase_credit(ammount); }

int Account::getBalance() { return person->getBalance(); }

void Account::addItem(int id, string name, int price, string category, int quantity, int refund, string sellerUsr, Date date) {
    if(isSeller())
        person->addItem(id, name, price, category, quantity, refund, sellerUsr, date);
    else
        throw runtime_error("Buyer Can't Have Item");
}

vector<Item*> Account::getItmes() {
    return person->getItmes();
}

string Account::getUsername() {
    return person->getUser();    
}

void Account::purchaseItem(Purchest* purchase) {
    if(!isSeller())
        purcheses.push_back(purchase);
    else
        throw runtime_error("Seller Can't Purchase");
}

void Account::finalPurchase(Purchest* purchase) {
    if(!isSeller())
        finalBought.push_back(purchase);
    else
        throw runtime_error("Seller Can't Purchase");
}

void Account::nItemsBought(int n, Item *item) {
    person->nItemsBought(n, item);
}

int Account::finalPurchaseCount = 0;

void Account::listPurchase() {
    if(finalPurchases.size() == 0)
        throw 0;
    for(auto purchass : finalPurchases) {
        cout << "id : " << purchass->getId() << endl;
        cout << "date : ";
        purchass->getRealse().print_date();
        cout << "items : " << endl;
        int count = 1;
        for(auto finalPurchase : purchass->getFinalPurchases()) {
            cout << count << ')' << endl;
            finalPurchase->printPurchase();
            count++;
        }
    }
}

void Account::refund(int purchaseId) {
    double refundPerc; int price; int count; bool isDen = true;
    for(auto purchase : purcheses) {
        if(purchase->isId(purchaseId)) {
            refundPerc = purchase->getRefund();
            price = purchase->getPrice();
            count = purchase->getCount();
            isDen = false;
            break;
        }
    }
    if(isDen) {
        throw 0;
    }
    price = count * (price * (refundPerc/100));
    if(refundPerc == 0)
        throw runtime_error("Refund Not Available");
    else {
        increase_credit(price);
    }
}

int Account::getRefundPrice(int purchaseId) {
    double refundPerc; int price; int count;
    for(auto purchase : purcheses) {
        if(purchase->isId(purchaseId)) {
            refundPerc = purchase->getRefund();
            price = purchase->getPrice();
            count = purchase->getCount();
            break;
        }
    }
    price = count * (price * (refundPerc/100));
    return price;
}

string Account::getRefundSellerUsr(int purchaseId) {
    string userSeller;
    for(auto purchase : purcheses) {
        if(purchase->isId(purchaseId)) {
            userSeller = purchase->getSellerUser();
            break;
        }
    }
    return userSeller;
}

RateFilter* Account::rateFilter = NULL;
CategoryFilter* Account::categoryFilter = NULL;
PriceFilter* Account::priceFiler = NULL;

void Account::showOffersSeller() {
    if(person->getPO() != NULL) {
        cout << person->getPO()->getId() << " package_offer ";
        for(int i = 0; i < person->getPO()->getids().size(); i++) {
            if(i == person->getPO()->getids().size() - 1)
                cout << person->getPO()->getids()[i] << ' ';
            else
                cout << person->getPO()->getids()[i] << ',';           
        }
        cout << person->getPO()->getDiscount() << endl;
    }
    if(person->getCO() != NULL) {
        cout << person->getCO()->getId() << " category_offer " << person->getCO()->getCategoryO();
        cout << ' ' << person->getCO()->getDiscount() << endl;
    }
    if(person->getTC() != NULL) {
        cout << person->getTC()->getId() << " total_cost_offer " << person->getTC()->getCost();
        cout << ' ' << person->getTC()->getDiscount() << endl;
    }
}

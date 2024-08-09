#ifndef _ACCOUNT_HPP_
#define _ACCOUNT_HPP_

#include <string>
#include "person.hpp"
#include <memory>
#include <vector>
using namespace std;

class Account {
public:
    Account(string, string, string, string);
    void increase_credit(int);
    void addItem(int, string, int, string, int, int, string, Date);
    void purchaseItem(Purchest* purchase);
    void finalPurchase(Purchest* purchase);
    void nItemsBought(int n, Item* item);
    void buyItemBuyer(int price) { person->buyItemBuyer(price); }
    void boughtItemSeller(int price) {person->increaseRevenue(price); }
    string getCity() { return person->getCity(); }
    void listPurchase();
    void refund(int purchaseId);
    void setItems(vector<Item*> items) { person->setItems(items); }
    void addRevenue(int price) {person->increaseRevenue(price); }
    void freeMemoryAcc();
    void addPackageOffer(vector<int> ids, int discount) { person->addPackageOffer(ids, discount); }
    void addCategoryOffer(string category, int discount) { person->addCategoryOffer(category, discount); }
    void addTotalCostOffer(int cost, int discount) { person->addCostOffer(cost, discount); }
    void clearCart() {
        purcheses.clear();
        finalBought.clear(); 
    }
    void addToFinalPurchases(FinalPurchase* purchase) { finalPurchases.push_back(purchase); }
    void showOffersSeller();
    void deleteOfferById(int id) { person->deleteOfferById(id); }
    void deleteAllOffers() { person->deleteAllOffers(); }
    bool isDupUser(string);
    bool isDupPass(string);
    bool isSeller();
    bool isEmptyOffers() { return person->isOffersEmpty(); }
    bool isEmptyPurchase() {
        if(purcheses.size() == 0)
            return true;
        return false;
    }
    bool isIdOffer(int id) { return person->isOfferId(id); }
    int getRevenue() {return person->getRevenue(); }
    int getRefundPrice(int);
    int getBalance();
    int howManyPurchases() {
        int count = 0;
        for(auto purchase : purcheses)
            count++;
        return count;
    }
    string getUsername();
    string getRefundSellerUsr(int);
    vector<Item*> getItmes();
    vector<Purchest*> getPurchases() {return purcheses; }
    vector<Purchest*> getFinalPurchases() {return finalBought; }
    vector<FinalPurchase*> getFinalFinalPurchases() { return finalPurchases; }
    Person* getPerson() { return person; }
    static bool filterR;
    static bool filterP;
    static bool filterC;
    static RateFilter* rateFilter;
    static CategoryFilter* categoryFilter;
    static PriceFilter* priceFiler;
    static vector<Item*> filteredItems;
    static int finalPurchaseCount;
    PackageOffer* getPOSeller() { return person->getPO(); }
    CategoryOffer* getCOSeller() { return person->getCO(); }
    TotalCostOffer* getTCSeller() { return person->getTC(); }
private:
    string password;
    Person* person;
    vector<Purchest*> purcheses;
    vector<Purchest*> finalBought;
    vector<FinalPurchase*> finalPurchases;
};

#endif
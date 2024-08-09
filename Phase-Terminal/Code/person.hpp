#ifndef _PERSON_HPP_
#define _PERSON_HPP_

#include <cstddef>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Date {
public:
    Date(string date__ = "") { date = date__; }
    void print_date();
private:
    string date;
};

class Comment;
class Rating;
class Person;
class ItemIndex;


class PackageOffer {
public:
    PackageOffer(vector<int> ids__, int discount__) {
        ids = ids__;
        discount = discount__;
        offerId = offerIds;
        offerIds++;
    };
    vector<int> getids() { return ids; }
    int getDiscount() { return discount; }
    int getId() { return offerId; }
    static int offerIds;
private:
    vector<int> ids;
    int discount;
    int offerId;
};

class CategoryOffer {
public:
    CategoryOffer(string category__, int discount__) {
        category = category__;
        discount = discount__;
        offerId = PackageOffer::offerIds;
        PackageOffer::offerIds++;
    }
    string getCategoryO() { return category; }
    int getDiscount() { return discount; }
    int getId() { return offerId; }
private:
    string category;
    int discount;
    int offerId;
};

class TotalCostOffer {
public:
    TotalCostOffer(int cost__, int discount__) {
        cost = cost__;
        discount = discount__;
        offerId = PackageOffer::offerIds;
        PackageOffer::offerIds++;
    }
    int getCost() { return cost; }
    int getDiscount() { return discount; }
    int getId() { return offerId; }
private:
    int cost;
    int discount;
    int offerId;
};

class Item {
public:
    Item(int, string, int, string, int, int, string, Date);
    void printItem();
    void printItemSeller();
    void printItemForList();
    void printItemForSeller(string usernameBuyer);
    void nItemsBought(int n) {
        bought += n;
        quantity -= n;
        if(quantity < 0) {
            bought -= n;
            quantity += n;
            throw runtime_error("No More Item");
        }
    }
    bool operator>(const Item&);
    bool operator<(const Item&);
    bool isUsr(string username) { return username == sellerUsr; }
    int getId() { return id; }
    int getPrice() { return price; }
    string getUsrSeller() { return sellerUsr; }
    int getRefund() { return refund; }
    void changePrice(int newPrice) {price = newPrice; }
    void changeQuantity(int newQuant) {quantity = newQuant; }
    bool isItemName(string name__) { return name == name__; }
    void addComment(string comment__, Person*, Item*);
    void rateItem(int rating__, Person*, Item*);
    static int idCountItem;
    float averageRating();
    void printComments();
    string getCategory() { return category; }
    int getQuantity() {return quantity; }
    int getBoughtItem() { return bought; }
private:
    int id;
    string name;
    string sellerUsr;
    string category;
    int price;
    Date release;
    int quantity;
    int bought;
    int refund;
    int packageOffer;
    int totalCostOffer;
    int categoryOffer;
    vector<Comment*> comments;
    vector<Rating*> ratings;
};

class Person {
public:
    Person(string, string);
    string getUser();
    virtual bool isSeller() { return false; }
    virtual void increase_credit(int ammount) { cout << "E" << endl;}
    virtual int getBalance() { return 0; }
    virtual void addItem(int, string, int, string, int, int, string, Date) { cout << "E" << endl; }
    virtual vector<Item*> getItmes() { return {};}
    virtual void nItemsBought(int, Item*) { cout << "E";}
    virtual void buyItemBuyer(int price) { cout << "B"; }
    virtual string getCity() { return "";}
    virtual void setItems(vector<Item*> items__) { cout << "D"; } 
    virtual void increaseRevenue(int ammount) { cout << "D"; }
    virtual int getRevenue() { return 0; }
    virtual void freeMemorySeller() { return; }
    virtual void addPackageOffer(vector<int> ids, int discount) { return; }
    virtual void addCategoryOffer(string category, int discount) { return; }
    virtual void addCostOffer(int cost, int discount) { return; }
    virtual PackageOffer* getPO() { return NULL; }
    virtual CategoryOffer* getCO() { return NULL; }
    virtual TotalCostOffer* getTC() { return NULL; }
    virtual bool isOffersEmpty() { return true; }
    virtual void deleteAllOffers() { return; }
    virtual void deleteOfferById(int id) { return; }
    virtual bool isOfferId(int id) { return false; }
protected:
    string username;
    string address;
};

class Seller : public Person {
public:
    Seller(string, string);
    bool isSeller();
    void addItem(int, string, int, string, int, int, string, Date);
    vector<Item*> getItmes();
    void nItemsBought(int, Item*);
    string getCity() { return address;}
    void setItems(vector<Item*> items__) { items = items__; }
    void increaseRevenue(int ammount) {revenue += ammount; }
    int getRevenue() { return revenue; }
    void freeMemorySeller();
    void addPackageOffer(vector<int> ids, int discount) {
        PackageOffer* newPO = new PackageOffer(ids, discount);
        POdis = newPO;
    }
    void addCategoryOffer(string category, int discount) {
        CategoryOffer* newCO = new CategoryOffer(category, discount);
        COdis = newCO;
    }
    void addCostOffer(int cost, int discount) {
        TotalCostOffer* newTCO = new TotalCostOffer(cost, discount);
        TCdis = newTCO;
    }
    PackageOffer* getPO() { return POdis; }
    CategoryOffer* getCO() { return COdis; }
    TotalCostOffer* getTC() { return TCdis; }
    bool isOffersEmpty() {
        if(POdis == NULL && COdis == NULL && TCdis == NULL)
            return true;
        return false;
    }
    void deleteAllOffers() {
        POdis = NULL;
        COdis = NULL;
        TCdis = NULL;
    }
    void deleteOfferById(int id);
    bool isOfferId(int id) {
        bool result = false;
        if(POdis != NULL)
            if(POdis->getId() == id)
                result = true;
        if(COdis != NULL)
            if(COdis->getId() == id)
                result = true;
        if(TCdis != NULL)
            if(TCdis->getId() == id)
                result = true;
        return result;
    }
private:
    string role;
    vector<Item*> items;
    int revenue;
    PackageOffer* POdis;
    CategoryOffer* COdis;
    TotalCostOffer* TCdis;
};

class Buyer : public Person {
public:
    Buyer(string, string);
    bool isSeller();
    void increase_credit(int ammount);
    int getBalance();
    void buyItemBuyer(int price);
    string getCity() { return address; }
private:
    string role;
    int credit;
};

class ItemIndex {
public:
    ItemIndex(int, Item*, string);
    int getIndex() { return index; }
    Item* getBoughtItem() { return item; }
    string getUserName() { return username; }
private:
    int index;
    Item* item;
    string username;
};

class Comment {
public:
    Comment(string comment__, Item* item__, Person* person__) { 
        comment = comment__;
        item = item__;
        person = person__;     
    }
    Item* getItemComment() {return item; }
    Person* getPersonCommented() {return person; }
    string getCommnet() { return comment; }
private:
    string comment;
    Item* item;
    Person* person;
};

class Rating {
public:
    Rating(int rating__, Item* item__, Person* person__) { 
        rating = rating__;
        item = item__;
        person = person__;     
    }
    Item* getItemComment() {return item; }
    Person* getPersonCommented() {return person; }
    int getRating() { return rating; }
private:
    int rating;
    Item* item;
    Person* person;
};

class RateFilter {
public:
    RateFilter(int minRate__, int maxRate__) {
        minRate = minRate__;
        maxRate = maxRate__;
    }
    int getMin() { return minRate; }
    int getMax() { return maxRate; }
private:
    int minRate;
    int maxRate;
};

class PriceFilter {
public:
    PriceFilter(int minPrice__, int maxPrice__) {
        minPrice = minPrice__;
        maxPrice = maxPrice__;
    }
    int getMin() { return minPrice; }
    int getMax() { return maxPrice; }
private:
    int minPrice;
    int maxPrice;
};

class CategoryFilter {
public:
    CategoryFilter(string cateogry__) { category = cateogry__; }
    string getCategory() { return category; }
private:
    string category;
};

class Purchest {
public:
    Purchest(int, Person*, Item*, int, int, int, int = 0);
    Purchest(const Purchest&);
    void printPurchase();
    void printPurchaseSeller(string usernameBuyer);
    bool isId(int id__) { return id == id__; }
    int getRefund() { return boughtItem->getRefund(); }
    string getUser() { return buyerItem->getUser(); }
    int getPrice() { return boughtItem->getPrice(); }
    int getCount() { return count; }
    bool isUsr(string username) {return boughtItem->isUsr(username); } 
    string getBuyerUser() {return buyerItem->getUser(); }
    string getSellerUser() {return boughtItem->getUsrSeller();}
    bool operator>(const Purchest&);
    bool operator<(const Purchest&);
    Purchest& operator=(const Purchest*);
    void rateItem(int rating) { boughtItem->rateItem(rating, buyerItem, boughtItem); }
    Item* getItem() { return boughtItem; }
    Person* getPerson() { return buyerItem; }
    int getId() { return boughtItem->getId(); }
    int getFullPriceOnly() { return fullPriceOnly; }
    static int countId;
private:
    Person* buyerItem;
    Item* boughtItem;
    int id;
    int count;
    int deliveryCost;
    int totalCost;
    int fullPriceOnly;
};

class DiscountItem {
public:
    DiscountItem(Purchest* item__, int discount__) {
        item = item__;
        discount = discount__;
    }
    Purchest* getItem() { return item; }
    int getDiscount() { return discount; }
private:
    Purchest* item;
    int discount;
};

class FinalPurchase {
public:
    FinalPurchase(vector<Purchest*> finalPurchases__, Date release__) { 
        finalPurchases = finalPurchases__; 
        id = idCount;
        release = release__;
        idCount++;
    }
    int getId() { return id; }
    vector<Purchest*> getFinalPurchases() { return finalPurchases; }
    Date getRealse() { return release; }
    static int idCount;
private:
    vector<Purchest*> finalPurchases;
    int id;
    Date release;
};

#endif
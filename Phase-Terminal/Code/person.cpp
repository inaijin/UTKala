#include "person.hpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

void Date::print_date() {
    cout << date;
}

void Item::addComment(string comment__, Person* person, Item* item) {
    Comment* newComment = new Comment(comment__, item, person);
    comments.push_back(newComment);
}

void Item::rateItem(int rating__, Person* person, Item* item) {
    Rating* newRate = new Rating(rating__, item, person);
    ratings.push_back(newRate);
}

float Item::averageRating() {
    float sum = 0; int count = 0;
    for(auto rating : ratings) {
        sum += rating->getRating();
        count++;
    }
    if(count == 0)
        return 0;
    float average = (sum / count);
    return average;
}

void Item::printComments() {
    for(auto comment : comments) {
        cout << "“" << comment->getCommnet() << "“" << " by " << comment->getPersonCommented()->getUser() << endl;
    }
}

Item::Item(int id__, string name__, int price__, string category__, int quantity__, int refund__, string sellerUsr__, Date date__) {
    id = id__;
    name = name__;
    price = price__;
    category = category__;
    quantity = quantity__;
    refund = refund__;
    sellerUsr = sellerUsr__;
    release = date__;
    bought = 0;
}

int Item::idCountItem = 1;

void Item::printItem() {
    cout << "id : " << id << endl;
    cout << "name : " << name << endl << "seller : " << sellerUsr << endl << "category : " << category << endl << "date : ";
    release.print_date();
    cout << "price : " << price << endl << "quantity : " << quantity << endl <<"purchased_count : " << bought << endl;
    cout << "average_rate : " << averageRating() << endl << "comments : " << endl; printComments();
}

void Item::printItemSeller() {
    cout << "id : " << id << endl;
    cout << "name : " << name << endl << "category : " << category << endl << "date : ";
    release.print_date();
    cout << "price : " << price << endl << "quantity : " << quantity << endl <<"purchased_count : " << bought << endl << "refund_percentage : " << refund << endl;
}

void Item::printItemForList() {
    cout << "seller : " << sellerUsr << endl << "item_id : " << id << endl << "item_name : " << name << endl << "item_price : " << price
    << endl << "purchased_count : " << bought << endl;
}

void Item::printItemForSeller(string usernameBuyer) {
    cout << "item_id : " << id << endl << "item_name : " << name << endl << "item_price : " << price
    << endl << "purchased_count : " << bought << endl;
}

int PackageOffer::offerIds = 1;

bool Item::operator>(const Item& item) {
    return this->price > item.price;
}

bool Item::operator<(const Item& item) {
    return this->price < item.price;
}

Person::Person(string username__, string address__) {
    username = username__;
    address = address__;
}

string Person::getUser() { return username; }

Seller::Seller(string username__, string address__) : Person(username__, address__) {
    role = "seller";
}

Buyer::Buyer(string username__, string address__) : Person(username__, address__) {
    role = "buyer";
    credit = 0;
}

bool Seller::isSeller() { return true; }
bool Buyer::isSeller() { return false; }

void Buyer::increase_credit(int ammount) {
    credit += ammount;
}

int Buyer::getBalance() {
    return credit;
}

void Seller::addItem(int id__, string name__, int price__, string category__, int quantity__, int refund__, string su, Date d) {
    Item* newItem = new Item(id__, name__, price__, category__, quantity__, refund__, su, d);
    items.push_back(newItem);
}

void Seller::freeMemorySeller() {
    if(items.size() != 0) {
        for(auto item : items) {
            delete item;
        }
    }
}

vector<Item*> Seller::getItmes() {
    return items;
}

Purchest::Purchest(int id__, Person* buyer, Item* item, int quantity, int deliveryCost__, int totalCost__, int fullPriceOnly__) {
    id = id__;
    buyerItem = buyer;
    boughtItem = item;
    count = quantity;
    deliveryCost = deliveryCost__;
    totalCost = totalCost__;
    fullPriceOnly = fullPriceOnly__;
}

Purchest::Purchest(const Purchest& p) {
    buyerItem = p.buyerItem;
    boughtItem = p.boughtItem;
    id = p.id;
    count = p.count;
    deliveryCost = p.deliveryCost;
    totalCost = p.totalCost;
}

Purchest& Purchest::operator=(const Purchest * purchase) {
    if(this == purchase)
        return *this;
    buyerItem = purchase->buyerItem;
    boughtItem = purchase->boughtItem;
    id = purchase->id;
    count = purchase->count;
    deliveryCost = purchase->deliveryCost;
    totalCost = purchase->totalCost;
    return *this;
}

ItemIndex::ItemIndex(int index__, Item* item__, string username__) {
    index = index__;
    item = item__;
    username = username__;
}

void Seller::nItemsBought(int n, Item* item__) {
    for(auto item : items) {
        if(item__ == item) 
            item->nItemsBought(n);
    }
}

void Buyer::buyItemBuyer(int price) {
    if(price > credit)
        throw runtime_error("Balance Not Enough");
    else
        credit -= price;
}

int Purchest::countId = 1;

int FinalPurchase::idCount = 1;

void Purchest::printPurchase() {
    boughtItem->printItemForList();
    cout << "delivery_cost : " << deliveryCost << endl << "total_cost : " << fullPriceOnly << endl << "paid : " << totalCost << endl;
}

void Purchest::printPurchaseSeller(string usernameBuyer) {
    boughtItem->printItemForSeller(usernameBuyer);
    cout << "delivery_cost : " << deliveryCost << endl << "total_cost : " << fullPriceOnly << endl << "paid : " << totalCost << endl;
}

bool Purchest::operator>(const Purchest& purchase) {
    return this->boughtItem->getPrice() > purchase.boughtItem->getPrice();
}

bool Purchest::operator<(const Purchest& purchase) {
    return this->boughtItem->getPrice() < purchase.boughtItem->getPrice();
}

void Seller::deleteOfferById(int id) {
    if(POdis->getId() == id)
        POdis = NULL;
    else if(COdis->getId() == id)
        COdis = NULL;
    else if(TCdis->getId() == id)
        TCdis = NULL;
    else
        throw 1.5;
}

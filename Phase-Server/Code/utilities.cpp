#include "utilities.hpp"
#include "account.hpp"
#include "person.hpp"
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <algorithm>

void initQ() {
    char init;
    cin >> init;
    if(init != '?')
        throw runtime_error("? error");
}

template<typename T>
void sortVecHigh(vector<T>& vector) {
    for(int i = 0; i < vector.size() - 1; i++)
        for(int j = 0; j < vector.size() - i - 1; j++)
            if(vector[j]->getPrice() < vector[j+1]->getPrice())
                swap(vector[j], vector[j+1]);
}

template<typename T>
void sortVecLow(vector<T>& vector) {
    for(int i = 0; i < vector.size() - 1; i++)
        for(int j = 0; j < vector.size() - i - 1; j++)
            if(vector[j]->getPrice() > vector[j+1]->getPrice())
                swap(vector[j], vector[j+1]);
}

bool isDupAccountUser(vector<Account> accounts, string username) {
    for(auto account : accounts) {
        if(account.isDupUser(username))
            return true;
    }
    return false;
}

bool isFilter() {
    if(Account::filterC || Account::filterP || Account::filterR)
        return true;
    return false;
}

bool isDupAccountPass(vector<Account> accounts, string password) {
    for(auto account : accounts) {
        if(account.isDupPass(password))
            return true;
    }
    return false;
}

bool isUsrPassCorrect(vector<Account> accounts, string username, string password) {
    int place;
    for(int i = 0; i < accounts.size(); i++) {
        if(accounts[i].isDupUser(username)) {
            place = i;
            break;
        }
    }
    if(accounts[place].isDupPass(password))
        return true;
    return false;
}

Account* getUsrPasAccount(vector<Account>& accounts, string username) {
    for(int i = 0; i < accounts.size(); i++)
        if(accounts[i].isDupUser(username))
            return &accounts[i];
    return NULL;
}

void increase_credit(Account account, int ammount) {
    if(account.isSeller())
        throw runtime_error("Seller");
    account.increase_credit(ammount);
}

Date getCurrentDate() {
    auto start = std::chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(start);
    string time = ctime(&currentTime);
    return Date(time);
}

void addItem(Account& acc, vector<Account> accounts, string name, string category, int price, int quantity) {
    for(auto account : accounts) {
        if(account.getItmes().size() == 0)
            continue;
        for(auto item : account.getItmes()) {
            if(item->isItemName(name))
                throw runtime_error("Cannot Have Two Items With The Same Name");
        }
    }
    if(quantity < 0 || price < 0)
        throw 1;
    acc.addItem(Item::idCountItem, name, price, category, quantity, 0, acc.getUsername(), getCurrentDate());
    cout << "id : " << Item::idCountItem << endl;
    Item::idCountItem++;
}

vector<ItemIndex*> listItems(vector<Account> accounts, bool print) {
    vector<ItemIndex*> result; vector<Item*> items; bool isEmpty = true;
    string command; int id = 0;
    bool more = true;
    for(int i = 0; i < accounts.size(); i++) {
        if(accounts[i].getItmes().size() != 0) {
            isEmpty = false;
            for(int j = 0; j < accounts[i].getItmes().size(); j++) {
                if(print && !more) {
                    if(accounts[i].getItmes()[j]->getId() == id) {
                        accounts[i].getItmes()[j]->printItem();
                    }
                }
                items.push_back(accounts[i].getItmes()[j]);
                ItemIndex* newItemIndex = new ItemIndex(accounts[i].getItmes()[j]->getId(), accounts[i].getItmes()[j], accounts[i].getUsername());
                result.push_back(newItemIndex);
            }
            if(items.size() == 0)
                throw 1.5;
            if(print && more) {
                string command;
                cin >> command;
                while(true) {
                    string choice;
                    cin >> choice;
                    bool moremore = true;
                    if(cin.get() == '\n') { moremore = false; }
                    if(moremore) {
                        int countMore = 0;
                        vector<Item*> temp;
                        while(countMore != 2) {
                            if(countMore == 1)
                                cin >> command;
                            if(command == "sort_by") {
                                if(countMore == 1)
                                    cin >> choice;
                                if(choice == "highest_price") {
                                    if(temp.size() == 0) {
                                        sortVecHigh(items);
                                    } else {
                                        sortVecHigh(temp);
                                    }
                                    countMore++;
                                } else if(choice == "lowest_price") {
                                    if(temp.size() == 0) {
                                        sortVecLow(items);
                                    } else {
                                        sortVecLow(temp);
                                    }
                                    countMore++;
                                } else {
                                    throw runtime_error("Invalid Command");
                                }
                            } else if(command == "seller_username") {
                                if(countMore == 1)
                                    cin >> choice;
                                for(auto item : items) {
                                    if(item->isUsr(choice))
                                        temp.push_back(item);
                                }
                                if(temp.size() == 0)
                                        throw 0;
                                countMore++;
                            } else {
                                throw runtime_error("Invalid Command");
                            }
                            if(countMore == 2) {
                                for(auto x : temp) {
                                    x->printItem();
                                }
                            }         
                        }               
                        return result;
                    }
                    if(command == "sort_by") {
                        if(choice == "highest_price") {
                            sortVecHigh(items);
                            for(auto item : items) {
                                item->printItem();
                            }
                            return result;
                        } else if(choice == "lowest_price") {
                            sortVecLow(items);
                            for(auto item : items) {
                                item->printItem();
                            }
                            return result;
                        } else {
                            throw runtime_error("Invalid Command");
                        }
                    } else if(command == "seller_username") {
                        bool isEmpty = true;
                        for(auto item : items) {
                            if(item->isUsr(choice)) {
                                item->printItem();
                                isEmpty = false;
                            }
                        }
                        if(isEmpty)
                            throw 0;
                        return result;
                    } else {
                        throw runtime_error("Invalid Command");
                    }
                }
            }
        }
    }
    if(isEmpty)
        throw 2.5;
    return result;
}

void buyItem(Account& acc, vector<ItemIndex*> itemIndexs, vector<Account>& accounts, int id, int count) {
    Item* item; string username;
    bool isEmpty = true;
    for(int i = 0; i < itemIndexs.size(); i++) {
        if(itemIndexs[i]->getIndex() == id) {
            item = itemIndexs[i]->getBoughtItem();
            username = itemIndexs[i]->getUserName();
            isEmpty = false;
        }
    }
    if(isEmpty)
        throw 0;
    int postPrice; string cityBuyer, citySeller;
    for(auto account : accounts) {
        if(account.isDupUser(item->getUsrSeller())) {
            citySeller = account.getCity();
        }
    }
    if(count > item->getQuantity())
        throw runtime_error("Cannot Buy More Than Stock");
    int purchaseId = 1;
    for(auto account : accounts) {
        if(!account.isEmptyPurchase())
            purchaseId += account.howManyPurchases();
    }
    Purchest* newPurchess = new Purchest(purchaseId, acc.getPerson(), item, count, 0, item->getPrice());
    acc.purchaseItem(newPurchess);
    cout << "OK" << endl;
}

vector<DiscountItem*> getPackageOfferDis(vector<Account> accounts, vector<Purchest*> cart) {
    vector<DiscountItem*> result;
    for(auto account : accounts) {
        vector<Purchest*> itemss; vector<int> discounts;
        vector<int> ids;
        if(account.getPOSeller() != NULL)
            ids = account.getPOSeller()->getids();
        else
            continue;
        if(ids.size() == 0)
            continue;
        for(auto item : cart) {
            for(auto id : ids) {
                if(item->getId() == id) {
                    vector<int>::iterator position = find(ids.begin(), ids.end(), id);
                    if(position != ids.end())
                        ids.erase(position);
                    itemss.push_back(item);
                    discounts.push_back(account.getPOSeller()->getDiscount());
                }
            }
        }
        if(ids.size() == 0) {
            for(int i = 0; i < discounts.size(); i++) {
                DiscountItem* newDI = new DiscountItem(itemss[i], discounts[i]);
                result.push_back(newDI);
            }
        }
    }
    return result;
}

vector<DiscountItem*> getCategoryOfferDis(vector<Account> accounts, vector<Purchest*> cart) {
    vector<DiscountItem*> result;
    for(auto account : accounts) {
        string category, sellerId;
        if(account.getCOSeller() != NULL) {
            category = account.getCOSeller()->getCategoryO();
            sellerId = account.getUsername();
        } else
            continue;
        for(auto item : cart) {
            if(item->getItem()->getCategory() == category && item->getSellerUser() == sellerId) {
                DiscountItem* newDI = new DiscountItem(item, account.getCOSeller()->getDiscount());
                result.push_back(newDI);
            }
        }
    }
    return result;
}

vector<DiscountItem*> getTotalCostOfferDis(vector<Account> accounts, vector<Purchest*> cart) {
    vector<DiscountItem*> result;
    for(auto account : accounts) {
        int cost;  int currentCost = 0;
        if(account.getTCSeller() != NULL)
            cost = account.getTCSeller()->getCost();
        else
            continue;
        vector<Purchest*> temp;
        for(auto item : cart) {
            for(auto itemSeller : account.getItmes()) {
                if(item->getId() == itemSeller->getId()) {
                    currentCost += (itemSeller->getPrice()) * item->getCount();
                    temp.push_back(item);
                }
            }
        }
        if(currentCost > cost) {
            for(auto purchase : temp) {
                DiscountItem* newDI = new DiscountItem(purchase, account.getTCSeller()->getDiscount());
                result.push_back(newDI);
            }
        }
    }
    return result;
}

void purchaseCart(Account& loggedAccount, vector<Account>& accounts, string city) {
    if(loggedAccount.getPurchases().size() == 0)
        throw 1;
    int totalPrice = 0; int paid = 0; int maxDiscounts = 0;
    int totalPriceReal = 0;
    for(auto purchase : loggedAccount.getPurchases()) {
        float totalDiscount = 0;
        int price = 0;
        Item* item = purchase->getItem();
        int postPrice; string cityBuyer, citySeller;
        for(auto account : accounts) {
            if(account.isDupUser(item->getUsrSeller())) {
                citySeller = account.getCity();
            }
        }
        if(city == "") {
            cityBuyer = loggedAccount.getCity();
        } else {
            cityBuyer = city;
        }
        if(cityBuyer == citySeller)
            postPrice = 1000;
        else
            postPrice = 2000;
        vector<DiscountItem*> discounts;
        vector<DiscountItem*> temp1 = getPackageOfferDis(accounts, loggedAccount.getPurchases());
        vector<DiscountItem*> temp2 = getCategoryOfferDis(accounts, loggedAccount.getPurchases());
        vector<DiscountItem*> temp3 = getTotalCostOfferDis(accounts, loggedAccount.getPurchases());
        discounts.reserve( temp1.size() + temp2.size() + temp3.size() );
        discounts.insert( discounts.end(), temp1.begin(), temp1.end() );
        discounts.insert( discounts.end(), temp2.begin(), temp2.end() );
        discounts.insert( discounts.end(), temp3.begin(), temp3.end() );
        for(auto discount : discounts) {
            if(purchase->getId() == discount->getItem()->getId()) {
                totalDiscount += discount->getDiscount();
            }
        }
        if(totalDiscount > maxDiscounts) { maxDiscounts = totalDiscount; }
        price = ( purchase->getPrice() * (1 - float(totalDiscount / 100)) ) * purchase->getCount() + postPrice;
        totalPriceReal += (purchase->getPrice() * purchase->getCount()) + postPrice;
        totalPrice += price;
        loggedAccount.buyItemBuyer(price);
        for(auto account : accounts) {
            if(account.isDupUser(item->getUsrSeller())) {
                account.addRevenue(price);
            }
        }
        for(int i = 0; i < accounts.size(); i++) {
            if(accounts[i].isDupUser(purchase->getSellerUser())) {
                accounts[i].nItemsBought(purchase->getCount(), item);
            }
        }
        Purchest* newPurchess = new Purchest(Purchest::countId, loggedAccount.getPerson(), item, purchase->getCount(), postPrice, price, ((purchase->getPrice() * purchase->getCount()) + postPrice));
        Purchest::countId++;
        loggedAccount.finalPurchase(newPurchess);
    }
    FinalPurchase* newFP = new FinalPurchase(loggedAccount.getFinalPurchases(), getCurrentDate());
    loggedAccount.addToFinalPurchases(newFP);
    cout << "total_cost : " << totalPriceReal << endl << "total_discount : " << totalPriceReal - totalPrice << endl << "paid : " << totalPrice << endl;
}

void listPurcheses(Account acc) {
    acc.listPurchase();
}

void deleteCart(Account& loggedAccount) {
    for(auto puchase : loggedAccount.getPurchases()) {
        delete puchase;
    }
    loggedAccount.clearCart();
}

void refund(Account& acc, vector<Account>& accounts) {
    int purchaseId;
    string command;
    cin >> command;
    if(command == "purchased_id") {
        cin >> purchaseId;
    } else {
        throw runtime_error("Unkown Command");
    }
    try {
        acc.refund(purchaseId);
    } catch(int) {
        bool isEmpty = true;
        for(auto account : accounts) {
            for(auto purchase : account.getPurchases()) {
                if(purchase->isId(purchaseId))
                    isEmpty = false;
            }
        }
        if(isEmpty) {
            throw 1.5;
        } else {
            throw 1;
        }
    }
    int price = acc.getRefundPrice(purchaseId);
    string usernameSeller = acc.getRefundSellerUsr(purchaseId);
    for(auto account : accounts) {
        if(account.isDupUser(usernameSeller))
            account.addRevenue(-price);
    }
}

void deleteItem(Account& acc, vector<Account> accounts) {
    int id; string command; cin >> command;
    int index; bool found = false;
    if(command == "id")
        cin >> id;
    else
        throw runtime_error("Unkown Command");
    vector<Item*> items = acc.getItmes();
    for(int i = 0; i < items.size(); i++) {
        if(items[i]->getId() == id) {
            index = i;
            found = true;
            break;
        }
    }
    bool exist = false;
    for(auto account : accounts) {
        for(auto item : account.getItmes()) {
            if(item->getId() == id) {
                exist = true;
            }
        }
    }
    if(!found && !exist)
        throw 0;
    if(exist && !found)
        throw 1.5;
    items.erase(items.begin() + index);
    acc.setItems(items);
}

void changePrice(Account& acc, vector<Account> accounts) {
    string command; int priceChange;
    int count = 0; int id;
    while(count != 2) {
        cin >> command;
        if(command == "price") {
           cin >> priceChange;
           count++;
        } else if(command == "id") {
            cin >> id;
            count++;
        }
    }
    if(priceChange <= 0)
        throw runtime_error("Cant 0");
    bool found = false;
    for(auto item : acc.getItmes()) {
        if(item->getId() == id) {
            item->changePrice(priceChange);
            found = true;
        }
    }
    bool exist = false;
    for(auto account : accounts) {
        for(auto item : account.getItmes()) {
            if(item->getId() == id) {
                exist = true;
            }
        }
    }
    if(!found && !exist)
        throw 0;
    if(exist && !found)
        throw 1.5;
}

void changeQuantity(Account& acc, vector<Account> accounts) {
    string command; int quantityChange;
    int count = 0; int id;
    while(count != 2) {
        cin >> command;
        if(command == "quantity") {
           cin >> quantityChange;
           count++;
        } else if(command == "id") {
            cin >> id;
            count++;
        }
    }
    if(quantityChange <= 0)
        throw runtime_error("Can't 0");
    bool found = false;
    for(auto item : acc.getItmes()) {
        if(item->getId() == id) {
            item->changeQuantity(quantityChange);
            found = true;
        }
    }
    bool exist = false;
    for(auto account : accounts) {
        for(auto item : account.getItmes()) {
            if(item->getId() == id) {
                exist = true;
            }
        }
    }
    if(!found && !exist)
        throw 0;
    if(exist && !found)
        throw 1.5;
}

void listItemsSeller(Account& acc) {
    if(acc.getItmes().size() == 0) {
        throw 0;
    }
    if(cin.get() != '\n') {
        string command; cin >> command;
        if(command == "sort_by") {
            string choice; cin >> choice;
            if(choice == "highest_price") {
                for(int i = 0; i < acc.getItmes().size() - 1; i++) {
                    for(int j = 0; j < acc.getItmes().size() - i - 1; j++) {
                        if(acc.getItmes()[j] < acc.getItmes()[j + 1])
                            swap(acc.getItmes()[j], acc.getItmes()[j + 1]);
                    }
                }
            } else if(choice == "lowest_price") {
                for(int i = 0; i < acc.getItmes().size() - 1; i++) {
                    for(int j = 0; j < acc.getItmes().size() - i - 1; j++) {
                        if(acc.getItmes()[j] > acc.getItmes()[j + 1])
                            swap(acc.getItmes()[j], acc.getItmes()[j + 1]);
                    }
                }
            }
        }
    }
    for(auto item : acc.getItmes()) {
        if(item->getUsrSeller() == acc.getUsername()) {
            item->printItemSeller();
        }
    }
}

void swapTransaction(Purchest*& a, Purchest*& b) {
    Purchest* temp = new Purchest(0, NULL, NULL, 0, 0, 0);
    *temp = *b;
    *b = *a;
    *a = *temp;
}

void listTransactions(vector<Account> accounts, Account acc) {
    string username; username = acc.getUsername(); bool isEmpty = true;
    if(cin.get() != '\n') {
        string command; cin >> command;
        if(command == "sort_by") {
            string choice; cin >> choice;
            if(choice == "highest_price") {
                for(auto acc : accounts) {
                    if(acc.getPurchases().size() == 0)
                        continue;
                    for(int i = 0; i < acc.getPurchases().size() - 1; i++) {
                        for(int j = 0; j < acc.getPurchases().size() - i - 1; j++) {
                            if(acc.getPurchases()[j]->getPrice() < acc.getPurchases()[j + 1]->getPrice()) {
                                swapTransaction(acc.getPurchases()[j], acc.getPurchases()[j + 1]);
                            }
                        }
                    }
                }
            } else if(choice == "lowest_price") {
                for(auto acc : accounts) {
                    if(acc.getPurchases().size() == 0)
                        continue;
                    for(int i = 0; i < acc.getPurchases().size() - 1; i++) {
                        for(int j = 0; j < acc.getPurchases().size() - i - 1; j++) {
                            if(acc.getPurchases()[j]->getPrice() > acc.getPurchases()[j + 1]->getPrice())
                                swapTransaction(acc.getPurchases()[j], acc.getPurchases()[j + 1]);
                        }
                    }
                }
            }
        }
    }
    for(auto account : accounts) {
        for(auto purchase : account.getFinalFinalPurchases()) {
            string buyerUsername;
            for(auto finalPurchase : purchase->getFinalPurchases()) {
                if(finalPurchase->isUsr(username)) {
                    buyerUsername = finalPurchase->getBuyerUser();
                    isEmpty = false;
                }
            }
            cout << "id : " << purchase->getId() << endl;
            cout << "date : "; purchase->getRealse().print_date();
            cout << "buyer : " << buyerUsername << endl;
            cout << "items : " << endl;
            int count = 1;
            for(auto finalPurchase : purchase->getFinalPurchases()) {
                cout << count << ')' << endl;
                if(finalPurchase->isUsr(username)) {
                    finalPurchase->printPurchaseSeller(buyerUsername);
                }
                count++;
            }
        }
    }
    if(isEmpty) {
        throw 0;
    }
}

void getSellerRevenue(Account acc) {
    cout << "total revenue : " << acc.getRevenue() << endl; 
}

string errorClearCin() {
    string buffer = "NF";
    while(cin >> buffer) {
        if(buffer == "POST" || buffer == "GET" || buffer == "DELETE" || buffer == "PUT") {
            break;
        }
        buffer = "NF";
    }
    return buffer;
}

void freeMemory(vector<Account>& accounts) {
    for(auto account : accounts) {
        account.freeMemoryAcc();
    }
}

void addComment(vector<Account>& accounts, Account loggAcc) {
    string choice; bool foundItemById = false;
    string comment; int id; int count = 0;
    while(count != 2) {
        cin >> choice;
        if(choice == "id") {
            cin >> id;
        } else if(choice == "message") {
            cin >> comment;
        } else {
            throw runtime_error("Invalid Command");
        }
        count++;
    }
    for(auto account : accounts)
        for(auto item : account.getItmes())
            if(item->getId() == id) {
                item->addComment(comment, loggAcc.getPerson(), item);
                foundItemById = true;
            }
    if(!foundItemById) {
        throw 1.5;
    }
}

void rateItem(vector<Account>& accounts, Account& user) {
    string choice; bool foundItemById = false, foundItem = false;
    int rating, id, count = 0;
    while(count != 2) {
        cin >> choice;
        if(choice == "id") {
            cin >> id;
        } else if(choice == "rate") {
            cin >> rating;
        } else {
            throw runtime_error("Invalid Command");
        }
        count++;
    }
    if(rating > 10 || rating < 0)
        throw runtime_error("Rating Out Of Range");
    for(auto purchase : user.getFinalFinalPurchases()) {
        for(auto item : purchase->getFinalPurchases())
            if(item->getId() == id) {
                item->rateItem(rating);
            foundItemById = true;
        }
    }
    for(auto account : accounts) {
        for(auto item : account.getItmes()) {
            if(item->getId() == id)
                foundItem = true;
        }
    }
    if(!foundItemById && foundItem)
        throw 1;
    if(!foundItemById && !foundItem)
        throw 1.5;
}

void filterByRateLite(vector<Item*>& items, int min, int max) {
    vector<Item*> result;
    for(auto item : items) {
        if(item->averageRating() <= max && item->averageRating() >= min)
            result.push_back(item);
    }
    items = result;
}

void filterByPriceLite(vector<Item*>& items, int min, int max) {
    vector<Item*> result;
    for(auto item : items) {
        if(item->getPrice() <= max && item->getPrice() >= min)
            result.push_back(item);
    }
    items = result;
}

bool filterByCategoryLite(vector<Item*>& items, string category) {
    vector<Item*> result; bool foundCategory = false;
    for(auto item : items) {
        if(item->getCategory() == category) {
            result.push_back(item);
            foundCategory = true;
        }
    }
    items = result;
    return foundCategory;
}

void filterByRate(vector<Account> accounts) {
    vector<Item*> items;
    for(auto account : accounts) {
        for(auto item : account.getItmes()) {
            items.push_back(item);
        }
    }
    string choice; int count = 0;
    int minRating, maxRating;
    while(count != 2) {
        cin >> choice;
        if(choice == "min_rating") {
            cin >> minRating;
        } else if(choice == "max_rating") {
            cin >> maxRating;
        } else {
            throw runtime_error("Invalid Choice");
        }
        count++;
    }
    if(minRating > 10 || minRating < 0 || maxRating > 10 || maxRating < 0)
        throw runtime_error("Invalid Rating Range");
    if(!isFilter() && Account::rateFilter == NULL) {
        vector<Item*> result;
        for(auto item : items) {
            if(item->averageRating() <= maxRating && item->averageRating() >= minRating) {
                result.push_back(item);
            }
        }
        Account::filteredItems = result;
    } else if(isFilter() && Account::rateFilter == NULL) {
        vector<Item*> result;
        for(auto item : Account::filteredItems) {
            if(item->averageRating() <= maxRating && item->averageRating() >= minRating)
                result.push_back(item);
        }
        Account::filteredItems = result;        
    }
    if(Account::rateFilter == NULL) {
        RateFilter* newRateFilter = new RateFilter(minRating, maxRating);
        Account::rateFilter = newRateFilter;
    }
    if(Account::categoryFilter != NULL) {
        if(Account::categoryFilter != NULL) {
            filterByCategoryLite(items, Account::categoryFilter->getCategory());
        }
        if(Account::priceFiler != NULL) {
            filterByPriceLite(items, Account::priceFiler->getMin(), Account::priceFiler->getMax());
        }
        filterByRateLite(items, minRating, maxRating);
        Account::filteredItems = items;
    }
    Account::filterR = true;
}

void filterByPrice(vector<Account> accounts) {
    vector<Item*> items;
    for(auto account : accounts) {
        for(auto item : account.getItmes()) {
            items.push_back(item);
        }
    }
    string choice; int count = 0;
    int minPrice, maxPrice;
    while(count != 2) {
        cin >> choice;
        if(choice == "min_price") {
            cin >> minPrice;
        } else if(choice == "max_price") {
            cin >> maxPrice;
        } else {
            throw runtime_error("Invalid Choice");
        }
        count++;
    }
    if(minPrice < 0 || maxPrice < 0)
        throw runtime_error("Invalid Rating Range");
    if(!isFilter()) {
        vector<Item*> result;
        for(auto item : items) {
            if(item->getPrice() <= maxPrice && item->getPrice() >= minPrice)
                result.push_back(item);
        }
        Account::filteredItems = result;
    } else if(isFilter() && Account::priceFiler == NULL) {
        vector<Item*> result;
        for(auto item : Account::filteredItems) {
            if(item->getPrice() <= maxPrice && item->getPrice() >= minPrice)
                result.push_back(item);
        }
        Account::filteredItems = result;        
    }
    if(Account::priceFiler == NULL) {
        PriceFilter* newPriceFilter = new PriceFilter(minPrice, maxPrice);
        Account::priceFiler = newPriceFilter;
    }
    if(Account::categoryFilter != NULL) {
        if(Account::rateFilter != NULL) {
            filterByRateLite(items, Account::rateFilter->getMin(), Account::rateFilter->getMax());
        }
        if(Account::categoryFilter != NULL) {
            filterByCategoryLite(items, Account::categoryFilter->getCategory());
        }
        filterByPriceLite(items, minPrice, maxPrice);
        Account::filteredItems = items;
    }
    Account::filterP = true;
}

void filterByCategory(vector<Account> accounts) {
    vector<Item*> items;
    for(auto account : accounts) {
        for(auto item : account.getItmes()) {
            items.push_back(item);
        }
    }
    string choice; int count = 0;
    string category;
    while(count != 1) {
        cin >> choice;
        if(choice == "category") {
            cin >> category;
        } else {
            throw runtime_error("Invalid Choice");
        }
        count++;
    }
    if(!isFilter()) {
        vector<Item*> result; bool foundCategory = false;
        for(auto item : items) {
            if(item->getCategory() == category) {
                result.push_back(item);
                foundCategory = true;
            }
        }
        if(!foundCategory)
            throw 1.5;
        Account::filteredItems = result;
    } else if(isFilter() && Account::categoryFilter == NULL) {
        vector<Item*> result; bool foundCategory = false;
        for(auto item : Account::filteredItems) {
            if(item->getCategory() == category) {
                result.push_back(item);
                foundCategory = true;
            }
        }
        if(!foundCategory)
            throw 1.5;
        Account::filteredItems = result;
    }
    if(Account::categoryFilter == NULL) {
        CategoryFilter* newCategoryFilter = new CategoryFilter(category);
        Account::categoryFilter = newCategoryFilter;
    }
    if(Account::categoryFilter != NULL) {
        if(Account::rateFilter != NULL) {
            filterByRateLite(items, Account::rateFilter->getMin(), Account::rateFilter->getMax());
        }
        if(Account::priceFiler != NULL) {
            filterByPriceLite(items, Account::priceFiler->getMin(), Account::priceFiler->getMax());
        }
        filterByCategoryLite(items, category);
        Account::filteredItems = items;
    }
    Account::filterC = true;
}

void deleteFilters() {
    Account::filterC = false;
    Account::priceFiler = NULL;
    Account::filterR = false;
    Account::rateFilter = NULL;
    Account::filterP = false;
    Account::categoryFilter = NULL;
}

void addPackageOffer(Account& loggedInAcc) {
    int count = 0; string choice; int tempId;
    vector<int> ids; int discount;
    while(count != 2) {
        cin >> choice;
        if(choice == "id") {
            while(true) {
                cin >> tempId; bool exists = false;
                for(auto item : loggedInAcc.getItmes())
                    if(tempId == item->getId())
                        exists = true;
                if(!exists)
                    throw 1.5;
                ids.push_back(tempId);
                if(cin.get() != ',')
                    break;
            }
        } else if(choice == "discount") {
            cin >> discount;
        } else {
            throw runtime_error("Invalid Command");
        }
        count++;
    }
    if(discount < 1 || discount > 100)
        throw runtime_error("Discount Out Off Range");
    loggedInAcc.addPackageOffer(ids, discount);
}

void addCategoryOffer(Account& loggedInAcc) {
    int count = 0; string choice;
    string category; int discount;
    while(count != 2) {
        cin >> choice;
        if(choice == "category") {
            cin >> category;
        } else if(choice == "discount") {
            cin >> discount;
        } else {
            throw runtime_error("Invalid Command");
        }
        count++;
    }
    bool exists = false;
    for(auto item : loggedInAcc.getItmes())
        if(item->getCategory() == category)
            exists = true;
    if(!exists)
        throw 1.5;
    if(discount < 1 || discount > 100)
        throw runtime_error("Discount Out Off Range");
    loggedInAcc.addCategoryOffer(category, discount);
}

void addTotalCostOffer(Account& loggedAccount) {
    int count = 0; string choice;
    int cost, discount;
    while(count != 2) {
        cin >> choice;
        if(choice == "cost") {
            cin >> cost;
        } else if(choice == "discount") {
            cin >> discount;
        } else {
            throw runtime_error("Invalid Command");
        }
        count++;
    }
    if(loggedAccount.getTCSeller() != NULL)
        throw runtime_error("Already Have");
    if(discount < 1 || discount > 100)
        throw runtime_error("Discount Out Off Range");
    loggedAccount.addTotalCostOffer(cost, discount);    
}

void listOffersSeller(vector<Account> accounts) {
    string choice, username;
    bool isEmpty = true, found = false;
    cin >> choice;
    if(choice == "username")
        cin >> username;
    else
        throw runtime_error("Invalid Command");
    for(auto account : accounts) {
        if(account.getUsername() == username) {
            if(!account.isSeller())
                continue;
            found = true;
            if(!account.isEmptyOffers())
                isEmpty = false;
            else
                continue;
            account.showOffersSeller();
        }
    }
    if(!found)
        throw 1;
    if(found && isEmpty)
        throw 1.5;
}

void deleteOffer(Account& loggedAccount, vector<Account> accounts) {
    if(cin.get() != '\n') {
        bool foundId = false; bool exists = false;
        string choice; int id;
        cin >> choice;
        if(choice == "id")
            cin >> id;
        else
            throw runtime_error("Invalid Command");
        try {
            loggedAccount.deleteOfferById(id);
        } catch(double) {
            throw;
        }
        for(auto account : accounts) {
            if(account.isIdOffer(id))
                exists = true;
        }
        if(exists)
            throw 1;
    } else {
        loggedAccount.deleteAllOffers();
    }
}

#ifndef _UTILITIES_HPP_
#define _UTILITIES_HPP_

#include <vector>
#include "account.hpp"
#include "person.hpp"
using namespace std;

void initQ();
bool isDupAccountUser(vector<Account>, string);
bool isDupAccountPass(vector<Account>, string);
bool isUsrPassCorrect(vector<Account>, string, string);
Account* getUsrPasAccount(vector<Account>&, string);
void increase_credit(int);
Date getCurrentDate();
void addItem(Account&, vector<Account>, string name, string category, int price, int quantity);
vector<ItemIndex*> listItems(vector<Account>, bool);
void buyItem(Account&, vector<ItemIndex*>, vector<Account>&, int id, int count);
void listPurcheses(Account);
void refund(Account&, vector<Account>&);
void deleteItem(Account&, vector<Account>);
void changePrice(Account&, vector<Account>);
void changeQuantity(Account&, vector<Account>);
void listItemsSeller(Account&);
void listTransactions(vector<Account>, Account);
void getSellerRevenue(Account acc);
string errorClearCin();
void freeMemory(vector<Account>&);
void addComment(vector<Account>& accounts, Account);
void rateItem(vector<Account>& accounts, Account&);
void filterByRate(vector<Account> accounts);
void filterByPrice(vector<Account> accounts);
void filterByCategory(vector<Account> accounts);
void filterByRateLite(vector<Item*>&, int, int);
void filterByPriceLite(vector<Item*>&, int, int);
bool filterByCategoryLite(vector<Item*>&, string);
void deleteFilters();
void purchaseCart(Account&, vector<Account>&, string city);
void addPackageOffer(Account&);
void addCategoryOffer(Account&);
void addTotalCostOffer(Account&);
vector<DiscountItem*> getPackageOfferDis(vector<Account> accounts, vector<Purchest*> cart);
vector<DiscountItem*> getCategoryOfferDis(vector<Account> accounts, vector<Purchest*> cart);
vector<DiscountItem*> getTotalCostOfferDis(vector<Account> accounts, vector<Purchest*> cart);
void deleteCart(Account&);
void listOffersSeller(vector<Account>);
void deleteOffer(Account&, vector<Account>);

#endif
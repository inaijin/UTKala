#ifndef _GETDEL_HPP_
#define _GETDEL_HPP_

#include <string>
#include <vector>
#include "account.hpp"
using namespace std;

void get(Account, vector<Account>&);
void del(Account&, vector<Account>&);
void put(Account&, vector<Account>&);

#endif
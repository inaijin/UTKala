#ifndef _POST_HPP_
#define _POST_HPP_

#include <vector>
#include "account.hpp"
using namespace std;

static Account DEFAULT("","","","seller");

Account* post(vector<Account>&, Account& acc = DEFAULT, bool loggedFlag = false);

#endif
#ifndef _SIGNUP_HPP_
#define _SIGNUP_HPP_

#include <string>
#include <vector>
#include "account.hpp"
using namespace std;

Account* signup(vector<Account>&, string username, string password, string role, string address);

#endif
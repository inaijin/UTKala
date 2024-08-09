#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "Server/APHTTP/utils/response.hpp"
#include "account.hpp"
#include "handelers.hpp"
#include "signup.hpp"
#include "signin.hpp"
#include "utilities.hpp"

vector<Account> UTkala::accounts = {};
Account* UTkala::loggAcc = NULL;

Response* Error::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;

    body << "<!DOCTYPE html>" << endl
         << "<html lang=\"en\">" << endl
         << "<head>" << endl
         << "    <meta charset=\"UTF-8\">" << endl
         << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">" << endl
         << "    <title>Error - AP-UTKala</title>" << endl
         << "    <link rel=\"stylesheet\" href=\"/css/style.css\">" << endl
         << "</head>" << endl
         << "<body>" << endl
         << "    <header>" << endl
         << "        <h1>UTkala</h1>" << endl
         << "    </header>" << endl
         << "    <main>" << endl
         << "        <div class=\"message error-message\">" << endl
         << "            <h2>Error</h2>" << endl
         << "            <p>" << errorMassage << "</p>" << endl
         << "            <a href=\"/\" class=\"button-link\">Home</a>" << endl
         << "        </div>" << endl
         << "    </main>" << endl
         << "    <footer>" << endl
         << "        <a href=\"/\">AP-UTKala</a>" << endl
         << "    </footer>" << endl
         << "    <script src=\"/js/script.js\"></script>" << endl
         << "</body>" << endl
         << "</html>" << endl;

    res->setBody(body.str());
    return res;
}

Response* ErrorWithURL::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;

    body << "<!DOCTYPE html>" << endl
         << "<html lang=\"en\">" << endl
         << "<head>" << endl
         << "    <meta charset=\"UTF-8\">" << endl
         << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">" << endl
         << "    <title>Error - AP-UTKala</title>" << endl
         << "    <link rel=\"stylesheet\" href=\"/css/style.css\">" << endl
         << "</head>" << endl
         << "<body>" << endl
         << "    <header>" << endl
         << "        <h1>UTkala</h1>" << endl
         << "    </header>" << endl
         << "    <main>" << endl
         << "        <div class=\"message error-message\">" << endl
         << "            <h2>Error</h2>" << endl
         << "            <p>" << errorMessage << "</p>" << endl
         << "            <a href=\"" << url << "\" class=\"button-link\">Back</a>" << endl
         << "        </div>" << endl
         << "    </main>" << endl
         << "    <footer>" << endl
         << "        <a href=\"/\">AP-UTKala</a>" << endl
         << "    </footer>" << endl
         << "    <script src=\"/js/script.js\"></script>" << endl
         << "</body>" << endl
         << "</html>" << endl;

    res->setBody(body.str());
    return res;
}

Response* Success::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;

    body << "<!DOCTYPE html>" << endl
         << "<html lang=\"en\">" << endl
         << "<head>" << endl
         << "    <meta charset=\"UTF-8\">" << endl
         << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">" << endl
         << "    <title>Success - AP-UTKala</title>" << endl
         << "    <link rel=\"stylesheet\" href=\"/css/style.css\">" << endl
         << "</head>" << endl
         << "<body>" << endl
         << "    <header>" << endl
         << "        <h1>UTkala</h1>" << endl
         << "    </header>" << endl
         << "    <main>" << endl
         << "        <div class=\"message success-message\">" << endl
         << "            <h2>Success</h2>" << endl
         << "            <p>" << successMassage << "</p>" << endl
         << "            <a href=\"" << url << "\" class=\"button-link\">Back</a>" << endl
         << "        </div>" << endl
         << "    </main>" << endl
         << "    <footer>" << endl
         << "        <a href=\"/\">AP-UTKala</a>" << endl
         << "    </footer>" << endl
         << "    <script src=\"/js/script.js\"></script>" << endl
         << "</body>" << endl
         << "</html>" << endl;

    res->setBody(body.str());
    return res;
}

Response* Home::callback(Request * req) {
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;
    body
        << "<html>" << endl
        << "    <head><title>Home</title>" << endl
        << "    </head>" << endl
        << "    <body style=\'text-align: center;\'>" << endl
        << "    <h1>UTkala</h1>" << endl
        << "        <p>" << endl
        << "            <a href='signIn'>Sign In</a>" << endl
        << "        </p>" << endl
        << "        <p>" << endl
        << "            <a href='signUp'>Sign Up</a>" << endl
        << "        </p>" << endl
        << "    </body" << endl
        << "</html>" << endl;
    res->setBody(body.str());
    return res;
}

Response* SignUpHandeler::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;
    body
        << "<html>" << endl
        << "    <head><title>SignUp</title>" << endl
        << "    </head>" << endl
        << "    <body style=\'text-align: center;\'>" << endl
        << "    <h1>Sign Up</h1>" << endl
        << "        <form action='signUp' method='POST'>" << endl
        << "             Username: <input type='text' name='Username' /><br/>" << endl
        << "             Password: <input type='text' name='Password' /><br/>" << endl
        << "             Role: <input type='text' name='Role' /><br/>" << endl
        << "             Address: <input type='text' name='Address' /><br/>" << endl
        << "             <input type = 'submit' value='Sign Up'/>" << endl
        << "        </form>" << endl
        << "    </body>" << endl
        << "</html>" << endl;
    res->setBody(body.str());
    return res;
}

Response* SignUp::callback(Request* req) {
    try {
        signup(UTkala::accounts, req->getBodyParam("Username"), req->getBodyParam("Password"), 
        req->getBodyParam("Role"), req->getBodyParam("Address"));
    } catch(runtime_error& ex) {
        return Response::redirect("RoleErr");
    } catch(int) {
        return Response::redirect("SameUserErr");
    }
    for(int i = 0; i < UTkala::accounts.size(); i++)
        if(UTkala::accounts[i].isDupUser(req->getBodyParam("Username")))
            UTkala::loggAcc = &UTkala::accounts[i];
    if(req->getBodyParam("Role") == "buyer") {
        return Response::redirect("buyerHome");
    } else {
        return Response::redirect("sellerHome");
    }
}

Response* SignInHandeler::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;
    body
        << "<html>" << endl
        << "    <head><title>SignIn</title>" << endl
        << "    </head>" << endl
        << "    <body style=\'text-align: center;\'>" << endl
        << "    <h1>Sign In</h1>" << endl
        << "        <form action='signIn' method='POST'>" << endl
        << "             Username: <input type='text' name='Username' /><br/>" << endl
        << "             Password: <input type='text' name='Password' /><br/>" << endl
        << "             <input type = 'submit' value='Sign In'/>" << endl
        << "        </form>" << endl
        << "    </body>" << endl
        << "</html>" << endl;
    res->setBody(body.str());
    return res;
}

Response* SignIn::callback(Request* req) {
    try {
        signin(UTkala::accounts, req->getBodyParam("Username"), req->getBodyParam("Password"));
    } catch(int) {
        return Response::redirect("UserNotFoundErr");
    } catch(double) {
        return Response::redirect("WrongPasswordErr");
    }
    string role;
    for(int i = 0; i < UTkala::accounts.size(); i++)
        if(UTkala::accounts[i].isDupUser(req->getBodyParam("Username"))) {
            role = UTkala::accounts[i].getPerson()->getRole();
            UTkala::loggAcc = &UTkala::accounts[i];
        }
    if(role == "buyer") {
        return Response::redirect("buyerHome");
    } else {
        return Response::redirect("sellerHome");
    }
}

Response* SellerHub::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;
    body
        << "<html>" << endl
        << "    <head><title>SignIn</title>" << endl
        << "    </head>" << endl
        << "    <body style=\'text-align: center;\'>" << endl
        << "    <h1>Welcome Seller</h1>" << endl
        << "        <p>" << endl
        << "            <a href='AddItem'>Add Item</a>" << endl
        << "        </p>" << endl
        << "        <p>" << endl
        << "            <a href='/'>Log Out</a>" << endl
        << "        </p>" << endl
        << "    </body" << endl
        << "</html>" << endl;    
    res->setBody(body.str());
    return res;
}

Response* BuyerHub::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;
    body
        << "<html>" << endl
        << "    <head><title>SignIn</title>" << endl
        << "    </head>" << endl
        << "    <body style=\'text-align: center;\'>" << endl
        << "    <h1>Welcome Buyer</h1>" << endl
        << "        <p>" << endl
        << "            <a href='Wallet'>Wallet</a>" << endl
        << "        </p>" << endl
        << "        <p>" << endl
        << "            <a href='ShowItems'>Show Items</a>" << endl
        << "        </p>" << endl
        << "        <p>" << endl
        << "            <a href='Cart'>Cart</a>" << endl
        << "        </p>" << endl
        << "        <p>" << endl
        << "            <a href='listPurchases'>Previous Purcheses</a>" << endl
        << "        </p>" << endl
        << "        <p>" << endl
        << "            <a href='/'>Log Out</a>" << endl
        << "        </p>" << endl
        << "    </body" << endl
        << "</html>" << endl;
    res->setBody(body.str());
    return res;
}

Response* AddItemHandeler::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;
    body
        << "<html>" << endl
        << "    <head><title>AddItem</title>" << endl
        << "    </head>" << endl
        << "    <body style=\'text-align: center;\'>" << endl
        << "    <h1>Add Item</h1>" << endl
        << "        <form action='addItem' method='POST'>" << endl
        << "             Name: <input type='text' name='Name' /><br/>" << endl
        << "             Category: <input type='text' name='Category' /><br/>" << endl
        << "             Price: <input type='text' name='Price' /><br/>" << endl
        << "             Quantity: <input type='text' name='Quantity' /><br/>" << endl
        << "             <input type = 'submit' value='Add Item'/>" << endl
        << "        </form>" << endl
        << "    </body>" << endl
        << "</html>" << endl;
    res->setBody(body.str());
    return res;
}

Response* AddItem::callback(Request* req) {
    try {
        addItem(*UTkala::loggAcc, UTkala::accounts, req->getBodyParam("Name"), req->getBodyParam("Category"),
        stoi(req->getBodyParam("Price")), stoi(req->getBodyParam("Quantity")));
    } catch(runtime_error& ex) {
        return Response::redirect("SameItemNameErr");
    } catch(int) {
        return Response::redirect("InvalidRangePriceQuantityErr");
    }
    return Response::redirect("ItemAddedSUC");
}

Response* WalletHandeler::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");

    double balance = UTkala::loggAcc->getPerson()->getBalance();

    ostringstream body;
    body
        << "<!DOCTYPE html>" << endl
        << "<html lang=\"en\">" << endl
        << "<head>" << endl
        << "    <meta charset=\"UTF-8\">" << endl
        << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">" << endl
        << "    <title>Wallet - AP-UTKala</title>" << endl
        << "    <link rel=\"stylesheet\" href=\"/css/style.css\">" << endl
        << "</head>" << endl
        << "<body>" << endl
        << "    <header>" << endl
        << "        <h1>Wallet</h1>" << endl
        << "    </header>" << endl
        << "    <main>" << endl
        << "        <div class=\"container wallet-container\">" << endl
        << "            <p class=\"balance-amount\">$" << balance << "</p>" << endl
        << "            <form action=\"addBalance\" method=\"POST\">" << endl
        << "                <label for=\"balance\">Balance:</label>" << endl
        << "                <input type=\"text\" id=\"balance\" name=\"Balance\" required />" << endl
        << "                <button type=\"submit\">Add Balance</button>" << endl
        << "            </form>" << endl
        << "            <p>" << endl
        << "                <a href=\"/buyerHome\" class=\"button-link\">Back</a>" << endl
        << "            </p>" << endl
        << "        </div>" << endl
        << "    </main>" << endl
        << "    <footer>" << endl
        << "        <a href=\"/\">AP-UTKala</a>" << endl
        << "    </footer>" << endl
        << "    <script src=\"/js/script.js\"></script>" << endl
        << "</body>" << endl
        << "</html>" << endl;

    res->setBody(body.str());
    return res;
}


Response* Wallet::callback(Request* req) {
    if(stoi(req->getBodyParam("Balance")) <= 0)
        return Response::redirect("InvalidBalanceRange");
    UTkala::loggAcc->increase_credit(stoi(req->getBodyParam("Balance")));
    return Response::redirect("BalanceAddedSUCC");
}

Response* ShowItemsHandeler::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;
    
    body << "<!DOCTYPE html>" << endl
         << "<html lang=\"en\">" << endl
         << "<head>" << endl
         << "    <meta charset=\"UTF-8\">" << endl
         << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">" << endl
         << "    <title>Show Items - AP-UTKala</title>" << endl
         << "    <link rel=\"stylesheet\" href=\"/css/style.css\">" << endl
         << "</head>" << endl
         << "<body>" << endl
         << "    <header>" << endl
         << "        <h1>Items</h1>" << endl
         << "    </header>" << endl
         << "    <main>" << endl
         << "        <div class=\"container items-container\">" << endl;

    for (auto account : UTkala::accounts) {
        for (auto item : account.getItmes()) {
            body << "            <div class=\"item\">" << endl
                 << "                <p><strong>Id:</strong> " << item->getItemId() << "</p>" << endl
                 << "                <p><strong>Name:</strong> " << item->getItemName() << "</p>" << endl
                 << "                <p><strong>Category:</strong> " << item->getItemCategory() << "</p>" << endl
                 << "                <p><strong>Price:</strong> $" << item->getItemPrice() << "</p>" << endl
                 << "                <p><strong>Quantity:</strong> " << item->getItemQuantity() << "</p>" << endl
                 << "                <p><strong>Bought:</strong> " << item->getItemBought() << "</p>" << endl
                 << "                <p><strong>Seller:</strong> " << item->getItemSeller() << "</p>" << endl
                 << "                <p><strong>Average Rating:</strong> " << item->averageRating() << "</p>" << endl
                 << "            </div>" << endl;
        }
    }
    
    body << "        </div>" << endl
         << "        <p><a href=\"/buyerHome\" class=\"button-link\">Back</a></p>" << endl
         << "    </main>" << endl
         << "    <footer>" << endl
         << "        <a href=\"/\">AP-UTKala</a>" << endl
         << "    </footer>" << endl
         << "    <script src=\"/js/script.js\"></script>" << endl
         << "</body>" << endl
         << "</html>" << endl;

    res->setBody(body.str());
    return res;
}

Response* BuyItemHandeler::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;

    body << "<!DOCTYPE html>" << endl
         << "<html lang=\"en\">" << endl
         << "<head>" << endl
         << "    <meta charset=\"UTF-8\">" << endl
         << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">" << endl
         << "    <title>Cart - AP-UTKala</title>" << endl
         << "    <link rel=\"stylesheet\" href=\"/css/style.css\">" << endl
         << "</head>" << endl
         << "<body>" << endl
         << "    <header>" << endl
         << "        <h1>Cart</h1>" << endl
         << "    </header>" << endl
         << "    <main>" << endl
         << "        <div class=\"container cart-container\">" << endl;

    // Iterating through cart items
    for (auto cart : UTkala::loggAcc->getPurchases()) {
        body << "            <div class=\"cart-item\">" << endl
             << "                <p><strong>Id:</strong> " << cart->getItem()->getItemId() << "</p>" << endl
             << "                <p><strong>Name:</strong> " << cart->getItem()->getItemName() << "</p>" << endl
             << "                <p><strong>Price:</strong> $" << cart->getItem()->getItemPrice() << "</p>" << endl
             << "                <p><strong>Count:</strong> " << cart->getCount() << "</p>" << endl
             << "            </div>" << endl;
    }

    body << "            <form action='addItemToCart' method='POST' class='cart-form'>" << endl
         << "                <div class='form-group'>" << endl
         << "                    <label for='ItemId'>Item Id:</label>" << endl
         << "                    <input type='text' name='ItemId' id='ItemId' required />" << endl
         << "                </div>" << endl
         << "                <div class='form-group'>" << endl
         << "                    <label for='ItemCount'>Quantity:</label>" << endl
         << "                    <input type='text' name='ItemCount' id='ItemCount' required />" << endl
         << "                </div>" << endl
         << "                <button type='submit'>Add Item To Cart</button>" << endl
         << "            </form>" << endl

         << "            <form action='clearItems' method='POST' class='cart-form'>" << endl
         << "                <button type='submit' class='clear-cart'>Clear Cart</button>" << endl
         << "            </form>" << endl

         << "            <form action='buyItems' method='POST' class='cart-form'>" << endl
         << "                <div class='form-group'>" << endl
         << "                    <label for='City'>City (Optional):</label>" << endl
         << "                    <input type='text' name='City' id='City' />" << endl
         << "                </div>" << endl
         << "                <button type='submit'>Buy Items In Cart</button>" << endl
         << "            </form>" << endl

         << "            <p><a href=\"/buyerHome\" class=\"button-link\">Back</a></p>" << endl
         << "        </div>" << endl
         << "    </main>" << endl
         << "    <footer>" << endl
         << "        <a href=\"/\">AP-UTKala</a>" << endl
         << "    </footer>" << endl
         << "    <script src=\"/js/script.js\"></script>" << endl
         << "</body>" << endl
         << "</html>" << endl;

    res->setBody(body.str());
    return res;
}

Response* AddItemToCart::callback(Request* req) {
    try {
        buyItem(*UTkala::loggAcc, listItems(UTkala::accounts, false), UTkala::accounts, 
        stoi(req->getBodyParam("ItemId")), stoi(req->getBodyParam("ItemCount")));
    } catch(runtime_error& ex) {
        return Response::redirect("CountMoreThanQuantityErr");
    } catch(int) {
        return Response::redirect("ItemNotFoundErr");
    }
    return Response::redirect("AddedToCartSUCC");
}

Response* BuyItem::callback(Request* req) {
    try {
        purchaseCart(*UTkala::loggAcc, UTkala::accounts, req->getBodyParam("City"));
        deleteCart(*UTkala::loggAcc);
    } catch(int) {
        return Response::redirect("CartEmptyErr");
    } catch(runtime_error& ex) {
        return Response::redirect("NotEnoughBalanceErr");
    }
    return Response::redirect("BoughtItemsSUCC");
}

Response* DeleteCart::callback(Request* req) {
    deleteCart(*UTkala::loggAcc);
    return Response::redirect("CartClearedSUCC");
}

Response* ListPurchases::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;

    body << "<!DOCTYPE html>" << endl
         << "<html lang=\"en\">" << endl
         << "<head>" << endl
         << "    <meta charset=\"UTF-8\">" << endl
         << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">" << endl
         << "    <title>Purchases - AP-UTKala</title>" << endl
         << "    <link rel=\"stylesheet\" href=\"/css/style.css\">" << endl
         << "</head>" << endl
         << "<body>" << endl
         << "    <header>" << endl
         << "        <h1>Purchases</h1>" << endl
         << "    </header>" << endl
         << "    <main>" << endl
         << "        <div class=\"container purchases-container\">" << endl;

    // Iterating through each purchase
    for (auto finalPurchase : UTkala::loggAcc->getFinalFinalPurchases()) {
        body << "            <div class=\"purchase-entry\">" << endl
             << "                <p><strong>Id:</strong> " << finalPurchase->getId() << "</p>" << endl
             << "                <p><strong>Date:</strong> " << finalPurchase->getRealse().getDate() << "</p>" << endl
             << "                <h3>Items:</h3>" << endl;

        int count = 1;
        for (auto purchase : finalPurchase->getFinalPurchases()) {
            body << "                <div class=\"purchase-item\">" << endl
                 << "                    <p><strong>(" << count << ")</strong></p>" << endl
                 << "                    <p><strong>Seller:</strong> " << purchase->getSellerUser() << "</p>" << endl
                 << "                    <p><strong>Item Id:</strong> " << purchase->getItem()->getId() << "</p>" << endl
                 << "                    <p><strong>Item Name:</strong> " << purchase->getItem()->getItemName() << "</p>" << endl
                 << "                    <p><strong>Item Price:</strong> $" << purchase->getItem()->getItemPrice() << "</p>" << endl
                 << "                    <p><strong>Purchased Count:</strong> " << purchase->getCount() << "</p>" << endl
                 << "                    <p><strong>Delivery Cost:</strong> $" << purchase->getDelevCost() << "</p>" << endl
                 << "                    <p><strong>Total Cost:</strong> $" << purchase->getTotalCost() << "</p>" << endl
                 << "                </div>" << endl;
            count++;
        }

        body << "            </div>" << endl;
    }

    body << "            <p><a href=\"/buyerHome\" class=\"button-link\">Back</a></p>" << endl
         << "        </div>" << endl
         << "    </main>" << endl
         << "    <footer>" << endl
         << "        <a href=\"/\">AP-UTKala</a>" << endl
         << "    </footer>" << endl
         << "    <script src=\"/js/script.js\"></script>" << endl
         << "</body>" << endl
         << "</html>" << endl;

    res->setBody(body.str());
    return res;
}

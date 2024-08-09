#include "account.hpp"
#include "signup.hpp"
#include "signin.hpp"
#include "post.hpp"
#include "getdel.hpp"
#include "utilities.hpp"
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <system_error>
#include <vector>
#include "handelers.hpp"
#include "Server/APHTTP/server/server.hpp"

// AP-UTKala-Phase-Server

using namespace std;

int main() {
    vector<Account> accounts;
    try {
        Server server(8080);

        server.setNotFoundErrPage("Server/APHTTP/static/404.html");

        server.serveStatic("/css/style.css", "Server/APHTTP/static/css/style.css", "text/css");
        server.serveStatic("/css/main.css", "Server/APHTTP/static/css/main.css", "text/css");
        server.serveStatic("/js/script.js", "Server/APHTTP/static/js/script.js", "application/javascript");
        server.serveStatic("/images/logo.png", "Server/APHTTP/static/images/logo.png", "image/png");
        server.serveStatic("/images/homePage.png", "Server/APHTTP/static/images/HomePage.png", "image/png");

        server.get("/", new ShowPage("Server/APHTTP/static/index.html"));
        server.get("/signIn", new ShowPage("Server/APHTTP/static/signin.html"));
        server.get("/signUp", new ShowPage("Server/APHTTP/static/signup.html"));
        server.get("/sellerHome", new ShowPage("Server/APHTTP/static/sellerHub.html"));
        server.get("/buyerHome", new ShowPage("Server/APHTTP/static/buyerHub.html"));

        server.get("/AddItem", new ShowPage("Server/APHTTP/static/addItem.html"));
        server.get("/Wallet", new WalletHandeler);
        server.get("/ShowItems", new ShowItemsHandeler);
        server.get("/Cart", new BuyItemHandeler);
        server.get("/listPurchases", new ListPurchases);

        server.get("/SameUserErr", new Error("User Already Exists"));
        server.get("/RoleErr", new Error("Invalid Role"));
        server.get("/UserNotFoundErr", new Error("Username Not Found"));
        server.get("/WrongPasswordErr", new Error("Wrong Password"));

        server.get("/SameItemNameErr", new ErrorWithURL("Item Already Exists", "sellerHome"));
        server.get("/InvalidRangePriceQuantityErr", new ErrorWithURL("Invalid Intiger Range", "sellerHome"));
        server.get("/InvalidBalanceRange", new ErrorWithURL("Invalid Balance Range", "Wallet"));
        server.get("/CountMoreThanQuantityErr", new ErrorWithURL("Can't Buy More Than Stock", "Cart"));
        server.get("/ItemNotFoundErr", new ErrorWithURL("Item Not Found", "Cart"));
        server.get("/CartEmptyErr", new ErrorWithURL("Cart Is Empty", "Cart"));
        server.get("/NotEnoughBalanceErr", new ErrorWithURL("Not Enough Balance", "Cart"));

        server.get("/ItemAddedSUC", new Success("Item Added Succesfully", "sellerHome"));
        server.get("/BalanceAddedSUCC", new Success("Balance Added Succesfully", "Wallet"));
        server.get("/AddedToCartSUCC", new Success("Item Added Succesfully", "Cart"));
        server.get("/BoughtItemsSUCC", new Success("Items Bought Succesfully", "Cart"));
        server.get("/CartClearedSUCC", new Success("Cart Cleared Succesfully", "Cart"));

        server.post("/clearItems", new DeleteCart);
        server.post("/buyItems", new BuyItem);
        server.post("/addItemToCart", new AddItemToCart);
        server.post("/addBalance", new Wallet);
        server.post("/signUp", new SignUp(accounts));
        server.post("/signIn", new SignIn(accounts));
        server.post("/addItem", new AddItem(accounts));

        server.run();
    } catch (Server::Exception e) {
        cout << e.getMessage() << endl;
    }
    return 0;
}

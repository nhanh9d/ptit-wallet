#include "wallet.h"
#include <fstream>
Wallet::Wallet() : wallet_id(""), balance(0) {}
Wallet::Wallet(const std::string& id, int initial_balance) : wallet_id(id), balance(initial_balance) {}
std::string Wallet::getId() const { return wallet_id; }
int Wallet::getBalance() const { return balance; }
void Wallet::setBalance(int amount) { balance = amount; }
void Wallet::setId(const std::string& id) { wallet_id = id; }
bool Wallet::transferTo(Wallet& to, int amount) {
    if (balance >= amount) {
        balance -= amount;
        to.balance += amount;
        return true;
    }
    return false;
}
// ... các hàm khác nếu có 
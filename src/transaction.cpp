#include "transaction.h"
#include <fstream>
Transaction::Transaction(const std::string& from, const std::string& to, int amount, const std::string& status)
    : from_wallet(from), to_wallet(to), amount(amount), status(status), timestamp(std::time(nullptr)) {}
std::string Transaction::getFromWallet() const { return from_wallet; }
std::string Transaction::getToWallet() const { return to_wallet; }
int Transaction::getAmount() const { return amount; }
std::string Transaction::getStatus() const { return status; }
std::time_t Transaction::getTimestamp() const { return timestamp; }
void Transaction::setTimestamp(std::time_t ts) { timestamp = ts; } 
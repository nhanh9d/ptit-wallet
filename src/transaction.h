#pragma once
#include <string>
#include <ctime>
#include <fstream>

class Transaction {
private:
    std::string from_wallet;
    std::string to_wallet;
    int amount;
    std::string status;
    std::time_t timestamp;
public:
    Transaction(const std::string& from, const std::string& to, int amount, const std::string& status);
    std::string getFromWallet() const;
    std::string getToWallet() const;
    int getAmount() const;
    std::string getStatus() const;
    std::time_t getTimestamp() const;
    void setTimestamp(std::time_t ts);
    // Các phương thức lưu/đọc file nếu cần
}; 
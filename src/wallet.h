#pragma once
#include <string>
#include <fstream>

class Wallet {
private:
    std::string wallet_id;
    int balance;
public:
    Wallet();
    Wallet(const std::string& id, int initial_balance = 0);
    std::string getId() const;
    int getBalance() const;
    void setBalance(int amount);
    bool transferTo(Wallet& to, int amount);
    void setId(const std::string& id);
    // Các phương thức lưu/đọc file, backup (nếu cần)
}; 
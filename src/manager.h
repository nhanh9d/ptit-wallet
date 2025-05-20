#pragma once
#include "user.h"
#include "transaction.h"

class Manager : public User {
public:
    Manager();
    Manager(const std::string& username, const std::string& password, const std::string& full_name, const std::string& email);
    // Các phương thức quản lý: tạo tài khoản, duyệt danh sách, điều chỉnh thông tin hộ user
    User* createUser(std::vector<User*>& users, std::vector<Manager*>& managers);
    void editUser(User* target, std::vector<User*>& users, std::vector<Manager*>& managers);
    void depositToUser(User* target, int amount, int& system_wallet_balance, std::vector<User*>& users, std::vector<Manager*>& managers);
    static void listUsers(const std::vector<User*>& users, const std::vector<Manager*>& managers);
    static void showReport(const std::vector<User*>& users, const std::vector<Manager*>& managers, const std::vector<Transaction>& transactions, int system_wallet_balance);
}; 
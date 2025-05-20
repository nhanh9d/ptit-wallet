#pragma once
#include <string>
#include <vector>
#include <fstream>
class Manager;
#include "wallet.h"

class User {
protected:
    std::string username;
    std::string hashed_password;
    std::string full_name;
    std::string email;
    Wallet wallet;
    bool is_manager;
    bool is_first_login;
    std::string secret_key;
public:
    User();
    User(const std::string& username, const std::string& password, const std::string& full_name, const std::string& email, bool is_manager = false);
    virtual ~User();
    std::string getUsername() const;
    bool checkPassword(const std::string& password) const;
    void setPassword(const std::string& new_password);
    void setFullName(const std::string& name);
    void setEmail(const std::string& email);
    Wallet& getWallet();
    bool isManager() const;
    bool isFirstLogin() const;
    void setFirstLogin(bool val);
    static User* registerUser(std::vector<User*>& users, std::vector<Manager*>& managers);
    static User* loginUser(const std::vector<User*>& users, const std::vector<Manager*>& managers);
    bool saveToFile(std::ofstream& out) const;
    static User* loadFromFile(std::ifstream& in);
    std::string getHashedPassword() const;
    std::string getFullName() const;
    std::string getEmail() const;
    std::string getSecretKey() const;
    void setSecretKey(const std::string& key);
    // Các phương thức xác thực OTP, cập nhật thông tin, lưu/đọc file
}; 
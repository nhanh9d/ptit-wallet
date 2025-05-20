#pragma once
#include <string>
#include <vector>
#include "user.h"
#include "manager.h"
namespace Utils {
    std::string hashPassword(const std::string& password);
    std::string generateOTP();
    bool isUsernameTaken(const std::string& username, const std::vector<User*>& users, const std::vector<Manager*>& managers);
    std::string generateRandomPassword();
    bool isNumber(const std::string& s);
    std::string encodeBase32(const std::string& data);
    std::string decodeBase32(const std::string& base32);
    // Các hàm tiện ích khác
} 
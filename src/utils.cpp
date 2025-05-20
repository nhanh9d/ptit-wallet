#include "utils.h"
#include <random>
#include <sstream>
#include <algorithm>
#include <ctime>
namespace Utils {
    std::string hashPassword(const std::string& password) {
        std::hash<std::string> hasher;
        size_t hash = hasher(password);
        std::stringstream ss;
        ss << hash;
        return ss.str();
    }
    std::string generateOTP() {
        srand(time(0));
        int otp = 100000 + rand() % 900000;
        return std::to_string(otp);
    }
    bool isUsernameTaken(const std::string& username, const std::vector<User*>& users, const std::vector<Manager*>& managers) {
        for (auto u : users) if (u->getUsername() == username) return true;
        for (auto m : managers) if (m->getUsername() == username) return true;
        return false;
    }
    std::string generateRandomPassword() {
        static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        std::string pass;
        srand(time(0));
        for (int i = 0; i < 8; ++i) pass += alphanum[rand() % (sizeof(alphanum) - 1)];
        return pass;
    }
    bool isNumber(const std::string& s) {
        return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
    }
    // Bảng mã base32 chuẩn RFC 4648
    static const char* BASE32_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    std::string encodeBase32(const std::string& data) {
        std::string result;
        int buffer = 0, bitsLeft = 0;
        for (unsigned char c : data) {
            buffer = (buffer << 8) | c;
            bitsLeft += 8;
            while (bitsLeft >= 5) {
                result += BASE32_ALPHABET[(buffer >> (bitsLeft - 5)) & 0x1F];
                bitsLeft -= 5;
            }
        }
        if (bitsLeft > 0) {
            result += BASE32_ALPHABET[(buffer << (5 - bitsLeft)) & 0x1F];
        }
        return result;
    }
    std::string decodeBase32(const std::string& base32) {
        std::string result;
        int buffer = 0, bitsLeft = 0;
        for (char c : base32) {
            if ('a' <= c && c <= 'z') c -= 32; // chuyển về in hoa
            const char* p = strchr(BASE32_ALPHABET, c);
            if (!p) continue;
            int val = p - BASE32_ALPHABET;
            buffer = (buffer << 5) | val;
            bitsLeft += 5;
            if (bitsLeft >= 8) {
                result += char((buffer >> (bitsLeft - 8)) & 0xFF);
                bitsLeft -= 8;
            }
        }
        return result;
    }
} 
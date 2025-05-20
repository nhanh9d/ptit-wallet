#include "otp.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <cstring>

namespace OTP {
    // Hàm chuyển số nguyên thành chuỗi hex
    std::string intToHex(uint64_t num) {
        std::stringstream ss;
        ss << std::hex << num;
        return ss.str();
    }
    // Hàm sinh TOTP (tham khảo repo cpp-otp)
    std::string generateTOTP(const std::string& secret, int interval) {
        std::time_t now = std::time(nullptr);
        uint64_t counter = now / interval;
        unsigned char hash[EVP_MAX_MD_SIZE];
        unsigned int hash_len;
        HMAC(EVP_sha1(), secret.c_str(), secret.length(), (unsigned char*)&counter, sizeof(counter), hash, &hash_len);
        int offset = hash[hash_len - 1] & 0x0F;
        uint32_t binary = ((hash[offset] & 0x7f) << 24) |
                          ((hash[offset + 1] & 0xff) << 16) |
                          ((hash[offset + 2] & 0xff) << 8) |
                          (hash[offset + 3] & 0xff);
        int otp = binary % 1000000;
        std::stringstream ss;
        ss << std::setw(6) << std::setfill('0') << otp;
        return ss.str();
    }
    bool verifyTOTP(const std::string& secret, const std::string& otp, int interval) {
        // Cho phép lệch 1 interval để tránh sai số thời gian
        std::time_t now = std::time(nullptr);
        for (int i = -1; i <= 1; ++i) {
            uint64_t counter = (now / interval) + i;
            unsigned char hash[EVP_MAX_MD_SIZE];
            unsigned int hash_len;
            HMAC(EVP_sha1(), secret.c_str(), secret.length(), (unsigned char*)&counter, sizeof(counter), hash, &hash_len);
            int offset = hash[hash_len - 1] & 0x0F;
            uint32_t binary = ((hash[offset] & 0x7f) << 24) |
                              ((hash[offset + 1] & 0xff) << 16) |
                              ((hash[offset + 2] & 0xff) << 8) |
                              (hash[offset + 3] & 0xff);
            int code = binary % 1000000;
            std::stringstream ss;
            ss << std::setw(6) << std::setfill('0') << code;
            if (ss.str() == otp) return true;
        }
        return false;
    }
} 
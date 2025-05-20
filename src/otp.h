#pragma once
#include <string>
namespace OTP {
    std::string generateTOTP(const std::string& secret, int interval = 30);
    bool verifyTOTP(const std::string& secret, const std::string& otp, int interval = 30);
} 
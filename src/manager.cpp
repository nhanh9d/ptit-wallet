#include "manager.h"
#include <iostream>
#include <vector>
#include "utils.h"
#include "otp.h"
#include "data_manager.h"
#include <random>
Manager::Manager() : User() {}
Manager::Manager(const std::string& username, const std::string& password, const std::string& full_name, const std::string& email)
    : User(username, password, full_name, email, true) {}
// TODO: Triển khai các phương thức quản lý 
User* Manager::createUser(std::vector<User*>& users, std::vector<Manager*>& managers) {
    std::string username, password, full_name, email, role;
    std::cout << "Nhập username: "; std::cin >> username;
    if (Utils::isUsernameTaken(username, users, managers)) {
        std::cout << "Username đã tồn tại!\n";
        return nullptr;
    }
    std::cout << "Nhập họ tên: "; std::cin.ignore(); std::getline(std::cin, full_name);
    std::cout << "Nhập email: "; std::getline(std::cin, email);
    std::cout << "Chọn vai trò (user/manager): "; std::getline(std::cin, role);
    std::cout << "Nhập mật khẩu (bỏ trống để sinh tự động): "; std::getline(std::cin, password);
    if (password.empty()) password = Utils::generateRandomPassword();
    std::string hashed = Utils::hashPassword(password);
    if (role == "manager") {
        Manager* m = new Manager(username, hashed, full_name, email);
        m->getWallet().setId(username);
        m->getWallet().setBalance(1000);
        std::string raw_secret(10, '\0');
        std::random_device rd; std::mt19937 gen(rd()); std::uniform_int_distribution<> dis(0, 255);
        for (char& c : raw_secret) c = dis(gen);
        m->setSecretKey(Utils::encodeBase32(raw_secret));
        managers.push_back(m);
        std::cout << "Tạo manager thành công. Mật khẩu: " << password << "\n";
        DataManager::saveUsers(users, managers);
        return m;
    } else {
        User* u = new User(username, hashed, full_name, email);
        u->getWallet().setId(username);
        u->getWallet().setBalance(1000);
        std::string raw_secret(10, '\0');
        std::random_device rd; std::mt19937 gen(rd()); std::uniform_int_distribution<> dis(0, 255);
        for (char& c : raw_secret) c = dis(gen);
        u->setSecretKey(Utils::encodeBase32(raw_secret));
        users.push_back(u);
        std::cout << "Tạo user thành công. Mật khẩu: " << password << "\n";
        DataManager::saveUsers(users, managers);
        return u;
    }
}
void Manager::editUser(User* target, std::vector<User*>& users, std::vector<Manager*>& managers) {
    std::string new_name, new_email, otp;
    std::cout << "Nhập họ tên mới: "; std::getline(std::cin, new_name);
    std::cout << "Nhập email mới: "; std::getline(std::cin, new_email);
    std::string raw_secret = Utils::decodeBase32(target->getSecretKey());
    std::string otp_code = OTP::generateTOTP(raw_secret);
    std::cout << "Mã OTP xác thực (gửi cho user): " << otp_code << "\n";
    std::cout << "Nhập OTP do user cung cấp: "; std::getline(std::cin, otp);
    if (OTP::verifyTOTP(raw_secret, otp)) {
        target->setFullName(new_name);
        target->setEmail(new_email);
        std::cout << "Cập nhật thông tin user thành công!\n";
        DataManager::saveUsers(users, managers);
    } else {
        std::cout << "Sai OTP!\n";
    }
}
void Manager::depositToUser(User* target, int amount, int& system_wallet_balance, std::vector<User*>& users, std::vector<Manager*>& managers) {
    if (amount > system_wallet_balance) {
        std::cout << "Ví tổng không đủ điểm!\n";
        return;
    }
    target->getWallet().setBalance(target->getWallet().getBalance() + amount);
    system_wallet_balance -= amount;
    std::cout << "Nạp điểm thành công!\n";
    DataManager::saveUsers(users, managers);
}
void Manager::listUsers(const std::vector<User*>& users, const std::vector<Manager*>& managers) {
    std::cout << "\n===== DANH SÁCH NGƯỜI DÙNG =====\n";
    std::cout << "Loại\tUsername\tHọ tên\tEmail\tSố dư\n";
    for (const auto& u : users) {
        std::cout << "User\t" << u->getUsername() << "\t" << u->getFullName() << "\t" << u->getEmail() << "\t" << u->getWallet().getBalance() << "\n";
    }
    for (const auto& m : managers) {
        std::cout << "Manager\t" << m->getUsername() << "\t" << m->getFullName() << "\t" << m->getEmail() << "\t" << m->getWallet().getBalance() << "\n";
    }
}
void Manager::showReport(const std::vector<User*>& users, const std::vector<Manager*>& managers, const std::vector<Transaction>& transactions, int system_wallet_balance) {
    int total_users = users.size();
    int total_managers = managers.size();
    int total_transactions = transactions.size();
    int total_balance = 0;
    for (const auto& u : users) total_balance += u->getWallet().getBalance();
    for (const auto& m : managers) total_balance += m->getWallet().getBalance();
    std::cout << "\n===== BÁO CÁO TỔNG HỢP =====\n";
    std::cout << "Tổng số user: " << total_users << "\n";
    std::cout << "Tổng số manager: " << total_managers << "\n";
    std::cout << "Tổng số giao dịch: " << total_transactions << "\n";
    std::cout << "Tổng số điểm trong hệ thống: " << total_balance << "\n";
    std::cout << "Số dư ví tổng: " << system_wallet_balance << "\n";
} 
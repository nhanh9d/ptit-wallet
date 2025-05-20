#include "user.h"
#include "manager.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "utils.h"
#include <sstream>
#include <random>
// Triển khai các phương thức của User
User::User() {}
User::User(const std::string& username, const std::string& password, const std::string& full_name, const std::string& email, bool is_manager)
    : username(username), hashed_password(password), full_name(full_name), email(email), is_manager(is_manager), is_first_login(true) {}
User::~User() {}
std::string User::getUsername() const { return username; }
bool User::checkPassword(const std::string& password) const {
    return hashed_password == Utils::hashPassword(password);
}
void User::setPassword(const std::string& new_password) {
    hashed_password = Utils::hashPassword(new_password);
}
void User::setFullName(const std::string& name) { full_name = name; }
void User::setEmail(const std::string& email) { this->email = email; }
Wallet& User::getWallet() { return wallet; }
bool User::isManager() const { return is_manager; }
bool User::isFirstLogin() const { return is_first_login; }
void User::setFirstLogin(bool val) { is_first_login = val; }
std::string User::getHashedPassword() const { return hashed_password; }
std::string User::getFullName() const { return full_name; }
std::string User::getEmail() const { return email; }
std::string User::getSecretKey() const { return secret_key; }
void User::setSecretKey(const std::string& key) { secret_key = key; }
User* User::registerUser(std::vector<User*>& users, std::vector<Manager*>& managers) {
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
        return u;
    }
}
User* User::loginUser(const std::vector<User*>& users, const std::vector<Manager*>& managers) {
    std::string username, password;
    std::cout << "Username: "; std::cin >> username;
    std::cout << "Password: "; std::cin >> password;
    std::string hashed = Utils::hashPassword(password);
    for (auto u : users) if (u->getUsername() == username && u->checkPassword(password)) return u;
    for (auto m : managers) if (m->getUsername() == username && m->checkPassword(password)) return m;
    std::cout << "Sai thông tin đăng nhập!\n";
    return nullptr;
}
bool User::saveToFile(std::ofstream& out) const {
    out << username << "," << hashed_password << "," << full_name << "," << email << "," << (is_manager ? 1 : 0) << "\n";
    return true;
}
User* User::loadFromFile(std::ifstream& in) {
    std::string line;
    if (!std::getline(in, line)) return nullptr;
    std::istringstream iss(line);
    std::string username, hashed, full_name, email, is_manager;
    std::getline(iss, username, ',');
    std::getline(iss, hashed, ',');
    std::getline(iss, full_name, ',');
    std::getline(iss, email, ',');
    std::getline(iss, is_manager, ',');
    if (is_manager == "1") return new Manager(username, hashed, full_name, email);
    else return new User(username, hashed, full_name, email);
} 
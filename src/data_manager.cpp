#include "data_manager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <chrono>

namespace DataManager {
    bool loadUsers(std::vector<User*>& users, std::vector<Manager*>& managers) {
        std::ifstream in("users.txt");
        if (!in.is_open()) return false;
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            std::string username, hashed, full_name, email, is_manager, wallet_id, balance_str, secret_key;
            std::getline(iss, username, ',');
            std::getline(iss, hashed, ',');
            std::getline(iss, full_name, ',');
            std::getline(iss, email, ',');
            std::getline(iss, is_manager, ',');
            std::getline(iss, wallet_id, ',');
            std::getline(iss, balance_str, ',');
            std::getline(iss, secret_key, ',');
            int balance = balance_str.empty() ? 1000 : std::stoi(balance_str);
            if (is_manager == "1") {
                Manager* m = new Manager(username, hashed, full_name, email);
                m->getWallet().setId(wallet_id.empty() ? username : wallet_id);
                m->getWallet().setBalance(balance);
                m->setSecretKey(secret_key);
                managers.push_back(m);
            } else {
                User* u = new User(username, hashed, full_name, email);
                u->getWallet().setId(wallet_id.empty() ? username : wallet_id);
                u->getWallet().setBalance(balance);
                u->setSecretKey(secret_key);
                users.push_back(u);
            }
        }
        in.close();
        return true;
    }
    bool saveUsers(const std::vector<User*>& users, const std::vector<Manager*>& managers) {
        std::ofstream out("users.txt");
        if (!out.is_open()) return false;
        for (auto u : users) {
            out << u->getUsername() << "," << u->getHashedPassword() << "," << u->getFullName() << "," << u->getEmail() << "," << 0 << "," << u->getWallet().getId() << "," << u->getWallet().getBalance() << "," << u->getSecretKey() << "\n";
        }
        for (auto m : managers) {
            out << m->getUsername() << "," << m->getHashedPassword() << "," << m->getFullName() << "," << m->getEmail() << "," << 1 << "," << m->getWallet().getId() << "," << m->getWallet().getBalance() << "," << m->getSecretKey() << "\n";
        }
        out.close();
        return true;
    }
    bool loadTransactions(std::vector<Transaction>& transactions) {
        std::ifstream in("transactions.txt");
        if (!in.is_open()) return false;
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            std::string from, to, amount_str, status, timestamp_str;
            std::getline(iss, from, ',');
            std::getline(iss, to, ',');
            std::getline(iss, amount_str, ',');
            std::getline(iss, status, ',');
            std::getline(iss, timestamp_str, ',');
            int amount = std::stoi(amount_str);
            std::time_t ts = std::stoll(timestamp_str);
            Transaction t(from, to, amount, status);
            t.setTimestamp(ts);
            transactions.push_back(t);
        }
        in.close();
        return true;
    }
    bool saveTransactions(const std::vector<Transaction>& transactions) {
        std::ofstream out("transactions.txt");
        if (!out.is_open()) return false;
        for (const auto& t : transactions) {
            out << t.getFromWallet() << "," << t.getToWallet() << "," << t.getAmount() << "," << t.getStatus() << "," << t.getTimestamp() << "\n";
        }
        out.close();
        return true;
    }
    bool backupAll() {
        namespace fs = std::filesystem;
        try {
            auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::string ts = std::to_string(now);
            fs::create_directories("backup");
            fs::copy_file("users.txt", "backup/users_" + ts + ".txt", fs::copy_options::overwrite_existing);
            fs::copy_file("transactions.txt", "backup/transactions_" + ts + ".txt", fs::copy_options::overwrite_existing);
            return true;
        } catch (...) { return false; }
    }
    bool restoreAll() {
        namespace fs = std::filesystem;
        try {
            std::string latest_users, latest_trans;
            std::time_t latest_time = 0;
            for (const auto& entry : fs::directory_iterator("backup")) {
                std::string name = entry.path().filename().string();
                if (name.find("users_") == 0) {
                    std::string ts = name.substr(6, name.size() - 10);
                    std::time_t t = std::stoll(ts);
                    if (t > latest_time) { latest_time = t; latest_users = entry.path().string(); }
                }
            }
            latest_time = 0;
            for (const auto& entry : fs::directory_iterator("backup")) {
                std::string name = entry.path().filename().string();
                if (name.find("transactions_") == 0) {
                    std::string ts = name.substr(13, name.size() - 17);
                    std::time_t t = std::stoll(ts);
                    if (t > latest_time) { latest_time = t; latest_trans = entry.path().string(); }
                }
            }
            if (!latest_users.empty()) fs::copy_file(latest_users, "users.txt", fs::copy_options::overwrite_existing);
            if (!latest_trans.empty()) fs::copy_file(latest_trans, "transactions.txt", fs::copy_options::overwrite_existing);
            return true;
        } catch (...) { return false; }
    }
} 
#include <iostream>
#include <sstream>
#include "user.h"
#include "manager.h"
#include "wallet.h"
#include "transaction.h"
#include "utils.h"
#include "data_manager.h"
#include "otp.h"
#include "qrcodegen.hpp"
#include <iomanip>

using namespace std;

int system_wallet_balance = 1000000; // Ví tổng hệ thống

void showUserMenu(User* u, std::vector<User*>& users, std::vector<Manager*>& managers, std::vector<Transaction>& transactions);
void showManagerMenu(Manager* m, std::vector<User*>& users, std::vector<Manager*>& managers, std::vector<Transaction>& transactions);
void handleTransfer(User* u, std::vector<User*>& users, std::vector<Manager*>& managers, std::vector<Transaction>& transactions);
void handleChangePassword(User* u, std::vector<User*>& users, std::vector<Manager*>& managers);
void handleUpdateInfo(User* u, std::vector<User*>& users, std::vector<Manager*>& managers);
void showUserQRCode(User* u);
void printHex(const std::string& s);

int main() {
    std::vector<User*> users;
    std::vector<Manager*> managers;
    std::vector<Transaction> transactions;
    DataManager::loadUsers(users, managers);
    DataManager::loadTransactions(transactions);
    int choice;
    while (true) {
        std::cout << "===== HỆ THỐNG QUẢN LÝ VÍ ĐIỂM THƯỞNG =====\n";
        std::cout << "1. Đăng nhập\n2. Đăng ký\n3. Thoát\nChọn: ";
        std::cin >> choice;
        if (choice == 1) {
            User* u = User::loginUser(users, managers);
            if (u) {
                std::cout << "Đăng nhập thành công!\n";
                if (u->isManager())
                    showManagerMenu(static_cast<Manager*>(u), users, managers, transactions);
                else
                    showUserMenu(u, users, managers, transactions);
            }
        } else if (choice == 2) {
            User* u = User::registerUser(users, managers);
            if (u) DataManager::saveUsers(users, managers);
        } else if (choice == 3) {
            break;
        }
    }
    DataManager::saveUsers(users, managers);
    DataManager::saveTransactions(transactions);
    for (auto u : users) delete u;
    for (auto m : managers) delete m;
    return 0;
}

void showUserMenu(User* u, std::vector<User*>& users, std::vector<Manager*>& managers, std::vector<Transaction>& transactions) {
    bool logged_in = true;
    while (logged_in) {
        std::cout << "\n===== MENU NGƯỜI DÙNG =====\n";
        std::cout << "1. Xem thông tin cá nhân\n2. Đổi mật khẩu\n3. Cập nhật thông tin cá nhân\n4. Chuyển điểm\n5. Xem số dư ví\n6. Xem lịch sử giao dịch\n7. Đăng xuất\n8. Xem mã QR OTP để scan\nChọn: ";
        int user_choice; std::cin >> user_choice; std::cin.ignore();
        if (user_choice == 1) {
            std::cout << "Tên đăng nhập: " << u->getUsername() << "\n";
            std::cout << "Họ tên: " << u->getFullName() << "\n";
            std::cout << "Email: " << u->getEmail() << "\n";
        } else if (user_choice == 2) {
            handleChangePassword(u, users, managers);
        } else if (user_choice == 3) {
            handleUpdateInfo(u, users, managers);
        } else if (user_choice == 4) {
            handleTransfer(u, users, managers, transactions);
        } else if (user_choice == 5) {
            std::cout << "Số dư ví: " << u->getWallet().getBalance() << " điểm\n";
        } else if (user_choice == 6) {
            std::cout << "===== Lịch sử giao dịch =====\n";
            for (const auto& t : transactions) {
                if (t.getFromWallet() == u->getWallet().getId() || t.getToWallet() == u->getWallet().getId()) {
                    std::cout << "Từ: " << t.getFromWallet() << " Đến: " << t.getToWallet() << " Số điểm: " << t.getAmount() << " Trạng thái: " << t.getStatus() << "\n";
                }
            }
        } else if (user_choice == 7) {
            logged_in = false;
        } else if (user_choice == 8) {
            showUserQRCode(u);
        }
    }
}

void showManagerMenu(Manager* m, std::vector<User*>& users, std::vector<Manager*>& managers, std::vector<Transaction>& transactions) {
    extern int system_wallet_balance;
    bool logged_in = true;
    while (logged_in) {
        std::cout << "\n===== MENU QUẢN LÝ =====\n";
        std::cout << "1. Xem thông tin cá nhân\n2. Đổi mật khẩu\n3. Tạo tài khoản mới\n4. Xem danh sách user\n5. Điều chỉnh thông tin user\n6. Xem báo cáo tổng hợp\n7. Đăng xuất\n8. Backup dữ liệu\n9. Phục hồi dữ liệu\n10. Nạp điểm cho user từ ví tổng\nChọn: ";
        int manager_choice; std::cin >> manager_choice; std::cin.ignore();
        if (manager_choice == 1) {
            std::cout << "Tên đăng nhập: " << m->getUsername() << "\n";
            std::cout << "Họ tên: " << m->getFullName() << "\n";
            std::cout << "Email: " << m->getEmail() << "\n";
        } else if (manager_choice == 2) {
            handleChangePassword(m, users, managers);
        } else if (manager_choice == 3) {
            m->createUser(users, managers);
        } else if (manager_choice == 4) {
            Manager::listUsers(users, managers);
        } else if (manager_choice == 5) {
            std::string username;
            std::cout << "Nhập username cần chỉnh sửa: "; std::cin >> username; std::cin.ignore();
            User* target = nullptr;
            for (auto u : users) if (u->getUsername() == username) target = u;
            for (auto m2 : managers) if (m2->getUsername() == username) target = m2;
            if (!target) {
                std::cout << "Không tìm thấy user!\n";
            } else {
                m->editUser(target, users, managers);
            }
        } else if (manager_choice == 6) {
            Manager::showReport(users, managers, transactions, system_wallet_balance);
        } else if (manager_choice == 7) {
            logged_in = false;
        } else if (manager_choice == 8) {
            if (DataManager::backupAll()) std::cout << "Backup thành công!\n";
            else std::cout << "Backup thất bại!\n";
        } else if (manager_choice == 9) {
            if (DataManager::restoreAll()) std::cout << "Phục hồi thành công!\n";
            else std::cout << "Phục hồi thất bại!\n";
        } else if (manager_choice == 10) {
            std::string username;
            int amount;
            std::cout << "Nhập username user cần nạp điểm: "; std::cin >> username;
            std::cout << "Nhập số điểm muốn nạp: "; std::cin >> amount; std::cin.ignore();
            User* target = nullptr;
            for (auto u : users) if (u->getUsername() == username) target = u;
            for (auto m2 : managers) if (m2->getUsername() == username) target = m2;
            if (!target) {
                std::cout << "Không tìm thấy user!\n";
            } else {
                m->depositToUser(target, amount, system_wallet_balance, users, managers);
            }
        }
    }
}

void handleTransfer(User* u, std::vector<User*>& users, std::vector<Manager*>& managers, std::vector<Transaction>& transactions) {
    std::string to_username, otp;
    int amount;
    std::cout << "Nhập username người nhận: "; std::getline(std::cin, to_username);
    std::cout << "Nhập số điểm muốn chuyển: "; std::cin >> amount; std::cin.ignore();
    User* to_user = nullptr;
    for (auto u2 : users) if (u2->getUsername() == to_username) to_user = u2;
    for (auto m2 : managers) if (m2->getUsername() == to_username) to_user = m2;
    if (!to_user) {
        std::cout << "Không tìm thấy người nhận!\n";
        return;
    }
    if (u->getWallet().getBalance() < amount) {
        std::cout << "Số dư không đủ!\n";
        return;
    }
    std::string raw_secret = Utils::decodeBase32(u->getSecretKey());
    std::string otp_code = OTP::generateTOTP(raw_secret);
    std::cout << "Mã OTP xác thực (giả lập): " << otp_code << "\n";
    std::cout << "Nhập OTP: "; std::getline(std::cin, otp);
    if (OTP::verifyTOTP(raw_secret, otp)) {
        u->getWallet().setBalance(u->getWallet().getBalance() - amount);
        to_user->getWallet().setBalance(to_user->getWallet().getBalance() + amount);
        transactions.emplace_back(u->getWallet().getId(), to_user->getWallet().getId(), amount, "SUCCESS");
        std::cout << "Chuyển điểm thành công!\n";
        DataManager::saveUsers(users, managers);
        DataManager::saveTransactions(transactions);
    } else {
        std::cout << "Sai OTP!\n";
    }
}

void handleChangePassword(User* u, std::vector<User*>& users, std::vector<Manager*>& managers) {
    std::string new_pass, otp;
    std::cout << "Nhập mật khẩu mới: "; std::getline(std::cin, new_pass);
    std::string secret_base32 = u->getSecretKey();
    std::string raw_secret = Utils::decodeBase32(secret_base32);
    std::string otp_code = OTP::generateTOTP(raw_secret);
    std::cout << "[DEBUG] SECRET BASE32: " << secret_base32 << "\n";
    printHex(raw_secret);
    std::cout << "[DEBUG] OTP sinh ra từ code: " << otp_code << "\n";
    std::cout << "Mã OTP xác thực (giả lập): " << otp_code << "\n";
    std::cout << "Nhập OTP: "; std::getline(std::cin, otp);
    if (OTP::verifyTOTP(raw_secret, otp)) {
        u->setPassword(new_pass);
        std::cout << "Đổi mật khẩu thành công!\n";
        DataManager::saveUsers(users, managers);
    } else {
        std::cout << "Sai OTP!\n";
    }
}

void handleUpdateInfo(User* u, std::vector<User*>& users, std::vector<Manager*>& managers) {
    std::string new_name, new_email, otp;
    std::cout << "Nhập họ tên mới: "; std::getline(std::cin, new_name);
    std::cout << "Nhập email mới: "; std::getline(std::cin, new_email);
    std::string raw_secret = Utils::decodeBase32(u->getSecretKey());
    std::string otp_code = OTP::generateTOTP(raw_secret);
    std::cout << "Mã OTP xác thực (giả lập): " << otp_code << "\n";
    std::cout << "Nhập OTP: "; std::getline(std::cin, otp);
    if (OTP::verifyTOTP(raw_secret, otp)) {
        u->setFullName(new_name);
        u->setEmail(new_email);
        std::cout << "Cập nhật thông tin thành công!\n";
        DataManager::saveUsers(users, managers);
    } else {
        std::cout << "Sai OTP!\n";
    }
}

void showUserQRCode(User* u) {
    std::string issuer = "PTITWallet";
    std::string username = u->getUsername();
    std::string secret = u->getSecretKey();
    std::ostringstream oss;
    oss << "otpauth://totp/" << issuer << ":" << username
        << "?secret=" << secret << "&issuer=" << issuer;
    std::string uri = oss.str();
    std::cout << "\n--- Scan QR code này bằng app Google Authenticator/Microsoft Authenticator ---\n";
    using qrcodegen::QrCode;
    QrCode qr = QrCode::encodeText(uri.c_str(), QrCode::Ecc::LOW);
    int size = qr.getSize();
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++)
            std::cout << (qr.getModule(x, y) ? "\u2588\u2588" : "  ");
        std::cout << std::endl;
    }
    std::cout << "\n(Nếu không scan được, dán link này vào web tạo QR: https://www.qr-code-generator.com/)\n";
    std::cout << uri << "\n";
}

void printHex(const std::string& s) {
    std::cout << "[RAW BYTES HEX]: ";
    for (unsigned char c : s) std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c << " ";
    std::cout << std::dec << std::endl;
} 
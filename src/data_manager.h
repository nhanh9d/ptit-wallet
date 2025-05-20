#pragma once
#include <vector>
#include "user.h"
#include "manager.h"
#include "transaction.h"

namespace DataManager {
    bool loadUsers(std::vector<User*>& users, std::vector<Manager*>& managers);
    bool saveUsers(const std::vector<User*>& users, const std::vector<Manager*>& managers);
    bool loadTransactions(std::vector<Transaction>& transactions);
    bool saveTransactions(const std::vector<Transaction>& transactions);
    bool backupAll();
    bool restoreAll();
} 
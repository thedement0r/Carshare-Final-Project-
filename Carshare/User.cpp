#include "User.h"
#include <stdexcept>
User::User(const std::string& username, double moneyAmount, double discount)
        : username(username), moneyAmount(moneyAmount), discount(discount) {
    if (moneyAmount < 0.0 || discount < 0.0) {
        throw std::invalid_argument("Negative numbers, must be > 0.0");
    }
}

const std::string& User::getUsername() const {
    return username;
}

double User::getMoneyAmount() const {
    return moneyAmount;
}

void User::deductMoney(double amount) {
    moneyAmount -= amount;
}

double User::getDiscount() const {
    return discount;
}

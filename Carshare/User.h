#ifndef UNTITLED1_USER_H
#define UNTITLED1_USER_H

#include <string>
class User {
private:
    std::string username;
    double moneyAmount;
    double discount;

public:
    User(const std::string& username, double moneyAmount, double discount);

    const std::string& getUsername() const;

    double getMoneyAmount() const;

    void deductMoney(double amount);

    double getDiscount() const;


};

#endif //UNTITLED1_USER_H

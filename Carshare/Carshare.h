#ifndef UNTITLED1_CARSHARE_H
#define UNTITLED1_CARSHARE_H

#include <vector>
#include "car.h"
#include "user.h"

//I will add the StatusArray for using array element instead of text like in Carshare.cpp

class CarSharingSystem {
private:
    std::vector<Car> cars;
    std::vector<User> users;
    double exchangeRate;

public:
    CarSharingSystem(double exchangeRate);

    void addCar(const std::string& model, const std::chrono::system_clock::time_point& availableDate, double price);

    void addUser(const std::string& username, double moneyAmount, double discount);

    void displayCars() const;

    void displayUsers() const;

    double convertCurrency(double amount, const std::string& fromCurrency, const std::string& toCurrency) const;

    double calculateDiscountedPrice(const Car& car, const User& user) const;

    void rentCar(const std::string& username, const std::string& licensePlate);

    const std::vector<Car>& getCars() const {
        return cars;
    }

    const std::vector<User>& getUsers() const {
        return users;
    }
};
#endif //UNTITLED1_CARSHARE_H

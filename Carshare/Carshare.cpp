#include "Carshare.h"
#include <iostream>
#include <fstream>
#include <sstream>

CarSharingSystem::CarSharingSystem(double exchangeRate) : exchangeRate(exchangeRate) {}

void CarSharingSystem::addCar(const std::string& model, const std::chrono::system_clock::time_point& availableDate, double price) {
    cars.emplace_back(model, availableDate, price);
}

void CarSharingSystem::addUser(const std::string& username, double moneyAmount, double discount) {
    users.emplace_back(username, moneyAmount, discount);
}

void CarSharingSystem::displayUsers() const {
    std::cout << "Users in the system:\n";
    for (const auto& user : users) {
        std::cout << "Username: " << user.getUsername() << ", Money Amount: $" << user.getMoneyAmount()
                  << ", Discount: " << user.getDiscount() << "%\n";
    }
}

void CarSharingSystem::displayCars() const {
    std::cout << "Available Cars:\n";
    for (const auto& car : cars) {
        if (car.getAvailability()) {
            std::cout << "Model: " << car.getModel() << ", Available until: " << car.getAvailableDate().time_since_epoch().count() << ", Original Price: $" << car.getPrice() << "\n";
        }
    }
}

double CarSharingSystem::convertCurrency(double amount, const std::string& fromCurrency, const std::string& toCurrency) const {
    // Perform currency conversion
    if (fromCurrency == "USD" && toCurrency == "EUR") {
        return amount * exchangeRate;
    } else if (fromCurrency == "EUR" && toCurrency == "USD") {
        return amount / exchangeRate;
    } else {
        std::cerr << "Unsupported currency conversion: " << fromCurrency << " to " << toCurrency << std::endl;
        return amount;
    }
}

double CarSharingSystem::calculateDiscountedPrice(const Car& car, const User& user) const {
    double discountedPrice = car.getPrice() - (car.getPrice() * (user.getDiscount() / 100.0));
    return discountedPrice > 0.0 ? discountedPrice : 0.0;
}

void CarSharingSystem::rentCar(const std::string& username, const std::string& model) {
    for (auto& car : cars) {
        if (car.getModel() == model && car.getAvailability()) {
            for (auto& user : users) {
                if (user.getUsername() == username && user.getMoneyAmount() >= calculateDiscountedPrice(car, user)) {
                    double discountedPrice = calculateDiscountedPrice(car, user);

                    std::cout << username << " rented " << car.getModel() << " (Available until: " << car.getAvailableDate().time_since_epoch().count() << ") for $" << discountedPrice << " (Original Price: $" << car.getPrice() << ")\n";

                    user.deductMoney(discountedPrice);

                    car.setAvailability(false);
                    return;
                }
            }
            std::cout << "User " << username << " does not have enough money to rent the car.\n";
            return;
        }
    }
    std::cout << "Car with model " << model << " not available for rent.\n";
}

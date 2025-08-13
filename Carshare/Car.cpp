#include "Car.h"
#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>
using namespace std;

Car::Car(const string& model, const chrono::system_clock::time_point& availableDate, double price)
        : model(model), availableDate(availableDate), price(price), availability(true) {
    if (price < 0.0) {
        throw std::invalid_argument("Price must be positive number!");
    }
}

const string& Car::getModel() const {
    return model;
}

const chrono::system_clock::time_point& Car::getAvailableDate() const {
    return availableDate;
}

double Car::getPrice() const {
    return price;
}

bool Car::getAvailability() const {
    return availability;
}

void Car::setAvailability(bool availability) {
    this->availability = availability;
}

int Car::calculateRemainingDays() const {
    auto now = chrono::system_clock::now();
    auto remainingTime = chrono::duration_cast<chrono::hours>(availableDate - now);
    return remainingTime.count() / 24; // 24 to convert for day (24 hours)
}
#ifndef UNTITLED1_CAR_H
#define UNTITLED1_CAR_H
#include <utility>
using namespace std;
#include <string>
#include <string>
#include <chrono>

class Car {
private:
    string model;
    chrono::system_clock::time_point availableDate;
    double price;
    bool availability;

public:
    Car(const string& model, const chrono::system_clock::time_point& availableDate, double price);

    const string& getModel() const;

    const chrono::system_clock::time_point& getAvailableDate() const;

    double getPrice() const;

    bool getAvailability() const;

    void setAvailability(bool availability);

    int calculateRemainingDays() const;
};

#endif //UNTITLED1_CAR_H

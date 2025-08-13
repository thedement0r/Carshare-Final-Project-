#include <iostream>
#include "gtest/gtest.h"
#include "Carshare.h"
#include "car.h"
#include "user.h"
#include <chrono>
#include <stdexcept>

// Car test
TEST(CarTest, CreateCar) {
    auto availableDate = std::chrono::system_clock::now() + std::chrono::hours(24);
    Car car("Test Model", availableDate, 10000.0);
    EXPECT_EQ(car.getModel(), "Test Model");
    EXPECT_EQ(car.getAvailableDate(), availableDate);
    EXPECT_EQ(car.getPrice(), 10000.0);
    EXPECT_TRUE(car.getAvailability());
}

// User test
TEST(UserTest, CreateUser) {
    User user("TestUser", 15000.0, 10.0);
    EXPECT_EQ(user.getUsername(), "TestUser");
    EXPECT_EQ(user.getMoneyAmount(), 15000.0);
    EXPECT_EQ(user.getDiscount(), 10.0);
}

TEST(UserTest, UserWithNegativeValues) {
    EXPECT_THROW(User("UserWithNegativeValues", -5000.0, 5.0), std::invalid_argument);
}

// Carshare test
TEST(CarSharingSystemTest, AddCarAndUser) {
    CarSharingSystem carSharingSystem(1.0);
    auto availableDate = std::chrono::system_clock::now() + std::chrono::hours(5 * 24);
    carSharingSystem.addCar("Test Car", availableDate, 10000.0);
    carSharingSystem.addUser("TestUser", 15000.0, 10.0);
    const auto& cars = carSharingSystem.getCars();
    ASSERT_EQ(cars.size(), 1);
    const auto& users = carSharingSystem.getUsers();
    ASSERT_EQ(users.size(), 1);
    EXPECT_EQ(cars[0].getModel(), "Test Car");
    EXPECT_EQ(users[0].getUsername(), "TestUser");
}

TEST(CarSharingSystemTest, AddAndDisplayCars) {
    CarSharingSystem carSharingSystem(1.0);
    carSharingSystem.addCar("Car1", std::chrono::system_clock::now() + std::chrono::hours(24), 10000.0);
    carSharingSystem.addCar("Car2", std::chrono::system_clock::now() + std::chrono::hours(48), 12000.0);
    testing::internal::CaptureStdout();
    carSharingSystem.displayCars();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Car1"), std::string::npos);
    EXPECT_NE(output.find("Car2"), std::string::npos);
}

TEST(CarSharingSystemTest, AddAndDisplayUsers) {
    CarSharingSystem carSharingSystem(1.0);
    carSharingSystem.addUser("User1", 15000.0, 5.0);
    carSharingSystem.addUser("User2", 20000.0, 8.0);
    testing::internal::CaptureStdout();
    carSharingSystem.displayUsers();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("User1"), std::string::npos);
    EXPECT_NE(output.find("User2"), std::string::npos);
}

TEST(CarSharingSystemTest, RentCarNoMoney) {
    CarSharingSystem carSharingSystem(1.0);
    carSharingSystem.addUser("UserWithInsufficientFunds", 5000.0, 0.0);
    auto availableDate = std::chrono::system_clock::now() + std::chrono::hours(24);
    carSharingSystem.addCar("Test Car", availableDate, 10000.0);
    testing::internal::CaptureStdout();
    carSharingSystem.rentCar("BrokeUser", "Test Car");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("BrokeUser does not have enough money to rent the car."), std::string::npos);
}

TEST(CarSharingSystemTest, RentCar) {
    CarSharingSystem carSharingSystem(1.0);
    carSharingSystem.addUser("TestUser", 15000.0, 10.0);
    auto availableDate = std::chrono::system_clock::now() + std::chrono::hours(24);
    carSharingSystem.addCar("Test Car", availableDate, 10000.0);
    const auto& carsBeforeRent = carSharingSystem.getCars();
    ASSERT_EQ(carsBeforeRent.size(), 1);
    ASSERT_TRUE(carsBeforeRent[0].getAvailability());
    const auto& usersBeforeRent = carSharingSystem.getUsers();
    ASSERT_EQ(usersBeforeRent.size(), 1);
    double moneyBeforeRent = usersBeforeRent[0].getMoneyAmount();
    carSharingSystem.rentCar("TestUser", "Test Car");
    const auto& carsAfterRent = carSharingSystem.getCars();
    ASSERT_EQ(carsAfterRent.size(), 1);
    ASSERT_FALSE(carsAfterRent[0].getAvailability());
    const auto& usersAfterRent = carSharingSystem.getUsers();
    ASSERT_EQ(usersAfterRent.size(), 1);
    double moneyAfterRent = usersAfterRent[0].getMoneyAmount();
    EXPECT_EQ(moneyAfterRent, moneyBeforeRent - 9000.0);
}

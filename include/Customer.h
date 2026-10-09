#pragma once
#include "Entity.h"
#include <iostream>
#include <iomanip>
#include <sstream>

class Customer : public Entity {
private:
    std::string customerId;
    std::string fullName;
    std::string idCard;
    std::string address;

public:
    Customer() {}
    Customer(std::string id, std::string name, std::string card, std::string addr)
        : customerId(id), fullName(name), idCard(card), address(addr) {}

    std::string getId() const override { return customerId; }
    std::string getFullName() const { return fullName; }
    std::string getIdCard() const { return idCard; }
    std::string getAddress() const { return address; }

    void setFullName(const std::string& name) { fullName = name; }
    void setAddress(const std::string& addr) { address = addr; }

    void display() const override {
        std::cout << "| " << std::left << std::setw(8) << customerId 
                  << "| " << std::setw(22) << fullName 
                  << "| " << std::setw(15) << idCard 
                  << "| " << std::setw(25) << address << " |\n";
    }

    std::string toFileString() const override {
        return customerId + "|" + fullName + "|" + idCard + "|" + address;
    }

    void fromFileString(const std::string& line) override {
        std::stringstream ss(line);
        std::getline(ss, customerId, '|');
        std::getline(ss, fullName, '|');
        std::getline(ss, idCard, '|');
        std::getline(ss, address, '|');
    }
};
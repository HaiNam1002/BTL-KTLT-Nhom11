#pragma once
#include "Entity.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
class Customer : public Entity {
private:
    string customerId;
    string fullName;
    string idCard;
    string address;

public:
    Customer() {}
    Customer(string id, string name, string card, string addr)
        : customerId(id), fullName(name), idCard(card), address(addr) {}

    string getId() const override { return customerId; }
    string getFullName() const { return fullName; }
    string getIdCard() const { return idCard; }
    string getAddress() const { return address; }

    void setFullName(const string& name) { fullName = name; }
    void setAddress(const string& addr) { address = addr; }

    void display() const override {
        cout << "| " << left << setw(8) << customerId 
                  << "| " << setw(22) << fullName 
                  << "| " << setw(15) << idCard 
                  << "| " << setw(25) << address << " |\n";
    }

    string toFileString() const override {
        return customerId + "|" + fullName + "|" + idCard + "|" + address;
    }

    void fromFileString(const string& line) override {
        stringstream ss(line);
        getline(ss, customerId, '|');
        getline(ss, fullName, '|');
        getline(ss, idCard, '|');
        getline(ss, address, '|');
    }
};
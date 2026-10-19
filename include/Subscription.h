#pragma once
#include "Entity.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
class Subscription : public Entity {
private:
    string subId;        
    string phoneNumber;
    string customerId;
    string subType;
    double balance;
    string status;

public:
    Subscription() : balance(0.0) {}
    Subscription(string id, string phone, string cusId, 
                 string type, double bal, string st)
        : subId(id), phoneNumber(phone), customerId(cusId), 
          subType(type), balance(bal), status(st) {}

    string getId() const override { return subId; }
    string getPhoneNumber() const { return phoneNumber; }
    string getCustomerId() const { return customerId; }
    string getSubType() const { return subType; }
    double getBalance() const { return balance; }
    string getStatus() const { return status; }

    void setStatus(const string& st) { status = st; }
    void setBalance(double bal) { balance = bal; }

    void display() const override {
        cout << "| " << left << setw(8) << subId 
                  << "| " << setw(13) << phoneNumber 
                  << "| " << setw(9) << customerId 
                  << "| " << setw(12) << subType 
                  << "| " << right << setw(13) << fixed << setprecision(0) << balance 
                  << " | " << left << setw(10) << status << " |\n";
    }

    string toFileString() const override {
        return subId + "|" + phoneNumber + "|" + customerId + "|" + 
               subType + "|" + to_string((long long)balance) + "|" + status;
    }

    void fromFileString(const string& line) override {
        stringstream ss(line);
        string balStr;
        getline(ss, subId, '|');
        getline(ss, phoneNumber, '|');
        getline(ss, customerId, '|');
        getline(ss, subType, '|');
        getline(ss, balStr, '|');
        getline(ss, status, '|');
        balance = balStr.empty() ? 0.0 : stod(balStr);
    }
};

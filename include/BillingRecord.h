#pragma once
#include "Entity.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

class BillingRecord : public Entity {
private:
    std::string transactionId; // Mã giao dịch
    std::string phoneNumber;   // Số thuê bao
    std::string serviceType;   // Loại dịch vụ (Cuộc gọi, SMS, Data,...)
    std::string timestamp;     // Thời điểm phát sinh
    double usage;              // Dung lượng sử dụng (MB, giây,...)
    double amount;             // Thành tiền

public:
    BillingRecord() : usage(0.0), amount(0.0) {}

    BillingRecord(std::string transId, std::string phone, std::string service, 
                  std::string time, double use, double amt)
        : transactionId(transId), phoneNumber(phone), serviceType(service), 
          timestamp(time), usage(use), amount(amt) {}

    // Getters
    std::string getId() const override { return transactionId; }
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getServiceType() const { return serviceType; }
    std::string getTimestamp() const { return timestamp; }
    double getUsage() const { return usage; }
    double getAmount() const { return amount; }

    // Setters
    void setServiceType(const std::string& service) { serviceType = service; }
    void setAmount(double amt) { amount = amt; }

    void display() const override {
        std::cout << "| " << std::left << std::setw(12) << transactionId 
                  << "| " << std::setw(13) << phoneNumber 
                  << "| " << std::setw(15) << serviceType 
                  << "| " << std::setw(20) << timestamp 
                  << "| " << std::right << std::setw(10) << std::fixed << std::setprecision(2) << usage 
                  << " | " << std::setw(12) << amount << " |\n";
    }

    std::string toFileString() const override {
        std::stringstream ss;
        ss << transactionId << "|" << phoneNumber << "|" << serviceType << "|"
           << timestamp << "|" << usage << "|" << amount;
        return ss.str();
    }

    void fromFileString(const std::string& line) override {
        std::stringstream ss(line);
        std::string usageStr, amountStr;

        std::getline(ss, transactionId, '|');
        std::getline(ss, phoneNumber, '|');
        std::getline(ss, serviceType, '|');
        std::getline(ss, timestamp, '|');
        std::getline(ss, usageStr, '|');
        std::getline(ss, amountStr, '|');

        if (!usageStr.empty()) usage = std::stod(usageStr);
        if (!amountStr.empty()) amount = std::stod(amountStr);
    }
};
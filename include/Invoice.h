#pragma once
#include "Entity.h"
#include <iostream>
#include <iomanip>
#include <sstream>

class RatingRule : public Entity {
private:
    std::string ruleId;         // Mã quy tắc (RR001...)
    std::string serviceCode;    // Mã loại dịch vụ (VOICE, SMS, DATA)
    std::string description;    // Mô tả quy tắc
    double unitPrice;           // Đơn giá (VND)
    int blockUnit;              // Đơn vị tính (giây/MB)

public:
    RatingRule() : unitPrice(0.0), blockUnit(1) {}
    RatingRule(std::string id, std::string code, std::string desc, double price, int block)
        : ruleId(id), serviceCode(code), description(desc), unitPrice(price), blockUnit(block) {}

    std::string getId() const override { return ruleId; }
    std::string getServiceCode() const { return serviceCode; }
    std::string getDescription() const { return description; }
    double getUnitPrice() const { return unitPrice; }
    int getBlockUnit() const { return blockUnit; }

    void setUnitPrice(double price) { unitPrice = price; }
    void setDescription(const std::string& desc) { description = desc; }

    void display() const override {
        std::cout << "| " << std::left << std::setw(8) << ruleId 
                  << "| " << std::setw(18) << serviceCode 
                  << "| " << std::setw(26) << description 
                  << "| " << std::right << std::setw(12) << std::fixed << std::setprecision(1) << unitPrice 
                  << "| " << std::setw(8) << blockUnit << " |\n";
    }

    std::string toFileString() const override {
        std::ostringstream oss;
        oss << ruleId << "|" << serviceCode << "|" << description << "|" 
            << std::fixed << std::setprecision(1) << unitPrice << "|" << blockUnit;
        return oss.str();
    }

    void fromFileString(const std::string& line) override {
        std::stringstream ss(line);
        std::string priceStr, blockStr;
        std::getline(ss, ruleId, '|');
        std::getline(ss, serviceCode, '|');
        std::getline(ss, description, '|');
        std::getline(ss, priceStr, '|');
        std::getline(ss, blockStr, '|');
        unitPrice = priceStr.empty() ? 0.0 : std::stod(priceStr);
        blockUnit = blockStr.empty() ? 1 : std::stoi(blockStr);
    }
};
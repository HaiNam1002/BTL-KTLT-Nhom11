#pragma once
#include "Entity.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

class Invoice : public Entity {
private:
    string id;
    string subscriberId;
    string month;
    double totalAmount;
    string paymentStatus;
    string date;

public:
    Invoice() : totalAmount(0.0) {}

    Invoice(std::string id, std::string subId, std::string m, double amount, std::string status, std::string d) {
        this->id = id;
        this->subscriberId = subId;
        this->month = m;
        this->totalAmount = amount;
        this->paymentStatus = status;
        this->date = d;
    }

    std::string getId() const override { 
        return id; 
    }

    std::string getPaymentStatus() const { return paymentStatus; }
    double getTotalAmount() const { return totalAmount; }

    void setPaymentStatus(const std::string& status) { paymentStatus = status; }

    // Đọc từ file txt với ký tự ngăn cách là '|'
    void fromFileString(const std::string& line) override {
        stringstream ss(line);
        string token;
        vector<std::string> tokens;

        while (std::getline(ss, token, '|')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 6) {
            this->id = tokens[0];
            this->subscriberId = tokens[1];
            this->month = tokens[2];
            try {
                this->totalAmount = std::stod(tokens[3]);
            } catch (...) {
                this->totalAmount = 0.0;
            }
            this->paymentStatus = tokens[4];
            this->date = tokens[5];
        }
    }

    // Ghi ra file dùng dấu '|' đồng bộ với dữ liệu gốc
    string toFileString() const override {
        return this->id + "|" + subscriberId + "|" + month + "|" + 
               std::to_string((long long)totalAmount) + "|" + paymentStatus + "|" + date;
    }

    // In dạng bảng căn lề chuẩn theo khung hiển thị của main.cpp
    void display() const override {
        cout << "| " << left << setw(10) << id
             << "| " << left << setw(10) << subscriberId
             << "| " << left << setw(10) << month
             << "| " << right << setw(14) << (long long)totalAmount
             << " | " << left << setw(12) << paymentStatus
             << "| " << left << setw(13) << date << "|\n";
    }
};
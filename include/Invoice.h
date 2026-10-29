#pragma once
#include "Entity.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
class Invoice : public Entity {
private:
    string id; // Khai báo id tại đây để lưu trữ
    string subscriberId;
    string month;
    double totalAmount;
    string paymentStatus;
    string date;

public:
    Invoice() : totalAmount(0.0) {}

    Invoice(std::string id, std::string subId, std::string m, double amount, std::string status, std::string d) {
        this->id = id; // Gán trực tiếp, không dùng setId()
        this->subscriberId = subId;
        this->month = m;
        this->totalAmount = amount;
        this->paymentStatus = status;
        this->date = d;
    }

    // --- BẮT BUỘC: Ghi đè hàm getId() từ Entity để Invoice không bị abstract ---
    std::string getId() const override { 
        return id; 
    }

    // --- Getters (Đã xóa [[nodiscard]] để không báo warning ở C++11) ---
    std::string getPaymentStatus() const { return paymentStatus; }
    double getTotalAmount() const { return totalAmount; }

    // --- Setters ---
    void setPaymentStatus(const std::string& status) { paymentStatus = status; }

    // --- Các hàm bắt buộc từ Entity ---
    void fromFileString(const std::string& line) override {
        stringstream ss(line);
        string token;
        vector<std::string> tokens;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 6) {
            this->id = tokens[0]; // Gán trực tiếp, không dùng setId()
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

    string toFileString() const override {
        return this->id + "," + subscriberId + "," + month + "," + 
               std::to_string(totalAmount) + "," + paymentStatus + "," + date;
    }

    void display() const override {
       cout << "ID: " << id << " | KH: " << subscriberId << " | Thang: " << month 
                  << " | Tong tien: " << totalAmount << " | Trang thai: " << paymentStatus 
                  << " | Ngay: " << date << "\n";
    }
};

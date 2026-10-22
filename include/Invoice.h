#pragma once
#include "Entity.h"
#include <string>
#include <iostream>
#include <sstream>

class Invoice : public Entity {
private:
    std::string subscriberId;
    std::string month;
    double totalAmount{0.0}; // Khởi tạo mặc định ngay tại vị trí khai báo
    std::string paymentStatus;
    std::string date;

public:
    // Sử dụng default constructor của compiler
    Invoice() = default;

    Invoice(const std::string& id, const std::string& subId, const std::string& m, 
            double amount, const std::string& status, const std::string& d): subscriberId(subId), month(m), totalAmount(amount), paymentStatus(status), date(d) {
        setId(id);
    }

    [[nodiscard]] std::string getPaymentStatus() const { return paymentStatus; }
    [[nodiscard]] double getTotalAmount() const { return totalAmount; }

    // Setters: Truyền bằng tham chiếu hằng
    void setPaymentStatus(const std::string& status) { paymentStatus = status; }

    // Hoàn thiện hàm đọc file sử dụng std::stringstream
    void fromFileString(const std::string& line) override 
    {
        std::stringstream ss(line);
        std::string tempId, amountStr;
        
        std::getline(ss, tempId, ',');
        setId(tempId);
        std::getline(ss, subscriberId, ',');
        std::getline(ss, month, ',');
        std::getline(ss, amountStr, ',');
        totalAmount = std::stod(amountStr); // Chuyển chuỗi thành double
        std::getline(ss, paymentStatus, ',');
        std::getline(ss, date, ',');
    }

    [[nodiscard]] std::string toFileString() const override 
    {
        return getId() + "," + subscriberId + "," + month + "," + 
               std::to_string(totalAmount) + "," + paymentStatus + "," + date;
    }

    void display() const override {
        std::cout << "ID: " << getId() << " | KH: " << subscriberId << " | Thang: " << month 
                  << " | Tong tien: " << totalAmount << " | Trang thai: " << paymentStatus 
                  << " | Ngay: " << date << '\n';
    }
};
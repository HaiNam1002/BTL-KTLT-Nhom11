#pragma once
#include "Entity.h"
#include <iostream>
#include <iomanip>
#include <sstream>

class BillingHistory : public Entity {
private:
    std::string historyId;      // Mã lịch sử
    std::string phoneNumber;    // Số thuê bao
    std::string billingCycle;   // Kỳ cước (VD: "03/2026")
    double totalAmount;         // Tổng tiền thanh toán
    std::string paymentStatus;  // Trạng thái thanh toán (VD: "Da thanh toan", "Chua thanh toan")
    std::string updatedDate;    // Ngày cập nhật (VD: "2026-03-15")

public:
    BillingHistory() : totalAmount(0.0) {}

    BillingHistory(std::string id, std::string phone, std::string cycle, double amount, std::string status, std::string date)
        : historyId(id), phoneNumber(phone), billingCycle(cycle), totalAmount(amount), paymentStatus(status), updatedDate(date) {}

    // Getters
    std::string getId() const override { return historyId; }
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getBillingCycle() const { return billingCycle; }
    double getTotalAmount() const { return totalAmount; }
    std::string getPaymentStatus() const { return paymentStatus; }
    std::string getUpdatedDate() const { return updatedDate; }

    // Setters
    void setTotalAmount(double amount) { totalAmount = amount; }
    void setPaymentStatus(const std::string& status) { paymentStatus = status; }
    void setUpdatedDate(const std::string& date) { updatedDate = date; }

    // Hiển thị thông tin lịch sử cước dạng bảng
    void display() const override {
        std::cout << "| " << std::left << std::setw(12) << historyId 
                  << "| " << std::setw(13) << phoneNumber 
                  << "| " << std::setw(10) << billingCycle 
                  << "| " << std::setw(15) << std::fixed << std::setprecision(0) << totalAmount 
                  << "| " << std::setw(18) << paymentStatus 
                  << "| " << std::setw(13) << updatedDate << " |\n";
    }

    // Chuyển đối tượng thành chuỗi để ghi file
    std::string toFileString() const override {
        return historyId + "|" + phoneNumber + "|" + billingCycle + "|" 
             + std::to_string(totalAmount) + "|" + paymentStatus + "|" + updatedDate;
    }

    // Đọc dữ liệu từ dòng file vào đối tượng
    void fromFileString(const std::string& line) override {
        std::stringstream ss(line);
        std::string amountStr;

        std::getline(ss, historyId, '|');
        std::getline(ss, phoneNumber, '|');
        std::getline(ss, billingCycle, '|');
        std::getline(ss, amountStr, '|');
        std::getline(ss, paymentStatus, '|');
        std::getline(ss, updatedDate, '|');

        if (!amountStr.empty()) {
            totalAmount = std::stod(amountStr);
        } else {
            totalAmount = 0.0;
        }
    }
};
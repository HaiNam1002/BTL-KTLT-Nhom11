#pragma once
#include "Entity.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

class BillingHistory : public Entity {
private:
    string historyId;      // Mã lịch sử
    string phoneNumber;    // Số thuê bao
    string billingCycle;   // Kỳ cước (VD: "03/2026")
    double totalAmount;    // Tổng tiền thanh toán
    string paymentStatus;  // Trạng thái thanh toán (VD: "Da thanh toan", "Chua thanh toan")
    string updatedDate;    // Ngày cập nhật (VD: "2026-03-15")

public:
    // Khởi tạo mặc định đầy đủ (an toàn cho Repository)
    BillingHistory() : historyId(""), phoneNumber(""), billingCycle(""), totalAmount(0.0), paymentStatus(""), updatedDate("") {}

    // Constructor tối ưu: Dùng tham chiếu hằng (const string&) để tránh copy dữ liệu thừa
    BillingHistory(const string& id, const string& phone, const string& cycle, double amount, const string& status, const string& date)
        : historyId(id), phoneNumber(phone), billingCycle(cycle), totalAmount(amount), paymentStatus(status), updatedDate(date) {}

    // Getters
    string getId() const override { return historyId; }
    string getPhoneNumber() const { return phoneNumber; }
    string getBillingCycle() const { return billingCycle; }
    double getTotalAmount() const { return totalAmount; }
    string getPaymentStatus() const { return paymentStatus; }
    string getUpdatedDate() const { return updatedDate; }

    // Setters
    void setTotalAmount(double amount) { totalAmount = amount; }
    void setPaymentStatus(const string& status) { paymentStatus = status; }
    void setUpdatedDate(const string& date) { updatedDate = date; }

    // Hiển thị thông tin lịch sử cước dạng bảng
    void display() const override {
        cout << "| " << left << setw(12) << historyId 
             << "| " << setw(13) << phoneNumber 
             << "| " << setw(10) << billingCycle 
             << "| " << setw(15) << (long long)totalAmount // Ép kiểu để bỏ phần thập phân thừa
             << "| " << setw(18) << paymentStatus 
             << "| " << setw(13) << updatedDate << " |\n";
    }

    // Chuyển đối tượng thành chuỗi để ghi file
    string toFileString() const override {
        // Tối ưu: Ép (long long) trước khi to_string để file txt không bị dính số 0 vô nghĩa (VD: 150000.000000)
        return historyId + "|" + phoneNumber + "|" + billingCycle + "|" 
             + to_string((long long)totalAmount) + "|" + paymentStatus + "|" + updatedDate;
    }

    // Đọc dữ liệu từ dòng file vào đối tượng
    void fromFileString(const string& line) override {
        stringstream ss(line);
        string amountStr;

        getline(ss, historyId, '|');
        getline(ss, phoneNumber, '|');
        getline(ss, billingCycle, '|');
        getline(ss, amountStr, '|');
        getline(ss, paymentStatus, '|');
        getline(ss, updatedDate, '|');

        if (!amountStr.empty()) {
            totalAmount = stod(amountStr);
        } else {
            totalAmount = 0.0;
        }
    }
};

#endif

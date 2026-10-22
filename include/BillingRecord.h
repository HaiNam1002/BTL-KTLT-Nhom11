#pragma once
#include "Entity.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

class BillingRecord : public Entity {
private:
    string transactionId; // Mã giao dịch
    string phoneNumber;   // Số thuê bao
    string serviceType;   // Loại dịch vụ (Cuộc gọi, SMS, Data,...)
    string timestamp;     // Thời điểm phát sinh
    double usage;         // Dung lượng sử dụng (MB, giây,...)
    double amount;        // Thành tiền

public:
    BillingRecord() : usage(0.0), amount(0.0) {}

    // Tối ưu: Dùng tham chiếu hằng (const string&) để tránh copy dữ liệu chuỗi khi khởi tạo
    BillingRecord(const string& transId, const string& phone, const string& service, 
                  const string& time, double use, double amt)
        : transactionId(transId), phoneNumber(phone), serviceType(service), 
          timestamp(time), usage(use), amount(amt) {}

    // Getters
    string getId() const override { return transactionId; }
    string getPhoneNumber() const { return phoneNumber; }
    string getServiceType() const { return serviceType; }
    string getTimestamp() const { return timestamp; }
    double getUsage() const { return usage; }
    double getAmount() const { return amount; }

    // Setters
    void setServiceType(const string& service) { serviceType = service; }
    void setAmount(double amt) { amount = amt; }

    void display() const override {
        cout << "| " << left << setw(12) << transactionId 
             << "| " << setw(13) << phoneNumber 
             << "| " << setw(15) << serviceType 
             << "| " << setw(20) << timestamp 
             << "| " << right << setw(10) << fixed << setprecision(2) << usage 
             // Ép kiểu amount về long long để tránh lỗi hiển thị khoa học (e) với số tiền lớn
             << " | " << setw(12) << (long long)amount << " |\n";
    }

    string toFileString() const override {
        // Tối ưu: Thay thế stringstream bằng nối chuỗi trực tiếp để tăng tốc độ ghi file
        return transactionId + "|" + phoneNumber + "|" + serviceType + "|"
             + timestamp + "|" + to_string(usage) + "|" + to_string((long long)amount);
    }

    void fromFileString(const string& line) override {
        stringstream ss(line);
        string usageStr, amountStr;

        getline(ss, transactionId, '|');
        getline(ss, phoneNumber, '|');
        getline(ss, serviceType, '|');
        getline(ss, timestamp, '|');
        getline(ss, usageStr, '|');
        getline(ss, amountStr, '|');

        if (!usageStr.empty()) usage = stod(usageStr);
        if (!amountStr.empty()) amount = stod(amountStr);
    }
};

#pragma once
#include "Entity.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

class TopUp : public Entity {
private:
    string topupId;      // Mã phiếu nạp (Khóa chính)
    string phoneNumber;  // Số điện thoại nạp
    double amount;       // Mệnh giá nạp
    string topupDate;    // Ngày nạp

public:
    TopUp() : amount(0.0) {}

    // Tối ưu truyền const string& để tránh copy chuỗi
    TopUp(const string& id, const string& phone, double amt, const string& date)
        : topupId(id), phoneNumber(phone), amount(amt), topupDate(date) {}

    // Getters
    string getId() const override { return topupId; }
    string getPhoneNumber() const { return phoneNumber; }
    double getAmount() const { return amount; }
    string getTopupDate() const { return topupDate; }

    // Setters (phục vụ thao tác Update)
    void setAmount(double amt) { if (amt >= 0) amount = amt; }
    void setPhoneNumber(const string& phone) { phoneNumber = phone; }
    void setTopupDate(const string& date) { topupDate = date; }

    // Hiển thị dạng dòng bảng căn cột
    void display() const override {
        cout << "| " << left << setw(10) << topupId 
             << "| " << setw(15) << phoneNumber 
             << "| " << setw(16) << (long long)amount 
             << "| " << setw(15) << topupDate << " |\n";
    }

    // Chuyển đối tượng thành chuỗi ghi file text
    string toFileString() const override {
        return topupId + "|" + phoneNumber + "|" + to_string((long long)amount) + "|" + topupDate;
    }

    // Đọc dữ liệu từ file text
    void fromFileString(const string& line) override {
        stringstream ss(line);
        string amtStr;

        getline(ss, topupId, '|');
        getline(ss, phoneNumber, '|');
        getline(ss, amtStr, '|');
        getline(ss, topupDate, '|');

        amount = amtStr.empty() ? 0.0 : stod(amtStr);
    }
};
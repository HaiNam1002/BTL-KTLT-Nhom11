#pragma once
#include "Entity.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class TopUp : public Entity {
private:
    string maPhieu;
    string phoneNumber;
    double amount;
    string date;

public:
    // Constructor mặc định
    TopUp() {
        maPhieu = "";
        phoneNumber = "";
        amount = 0.0;
        date = "";
    }

    // Constructor đầy đủ tham số
    TopUp(string id, string phone, double amt, string d) {
        maPhieu = id;
        phoneNumber = phone;
        amount = amt;
        date = d;
    }

    // Getters
    string getId() const override { return maPhieu; }
    string getPhoneNumber() const { return phoneNumber; }
    double getAmount() const { return amount; }
    string getDate() const { return date; }

    // Setters (Bổ sung đầy đủ để fix lỗi)
    void setMaPhieu(string id) { maPhieu = id; }
    void setPhoneNumber(string phone) { phoneNumber = phone; }
    void setAmount(double amt) { if (amt >= 0) amount = amt; }
    void setDate(string d) { date = d; }   // <-- Hàm này sẽ giải quyết dứt điểm lỗi của bạn

    // Hiển thị dạng bảng
    void display() const override {
        cout << "| " << maPhieu;
        for (int i = maPhieu.length(); i < 9; i++) cout << " ";
        cout << " | " << phoneNumber;
        for (int i = phoneNumber.length(); i < 15; i++) cout << " ";
        cout << " | " << (long long)amount;
        string amtStr = to_string((long long)amount);
        for (int i = amtStr.length(); i < 15; i++) cout << " ";
        cout << " | " << date;
        for (int i = date.length(); i < 12; i++) cout << " ";
        cout << " |\n";
    }

    // Tuần tự hóa file
    string toFileString() const override {
        return maPhieu + "|" + phoneNumber + "|" + to_string((long long)amount) + "|" + date;
    }

    // Giải tuần tự hóa file
    void fromFileString(const string& line) override {
        stringstream ss(line);
        string amtStr;
        getline(ss, maPhieu, '|');
        getline(ss, phoneNumber, '|');
        getline(ss, amtStr, '|');
        getline(ss, date, '|');
        
        amount = amtStr.empty() ? 0.0 : stod(amtStr);
    }
};
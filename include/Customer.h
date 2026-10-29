#pragma once
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Customer {
private:
    string id;          // Ma khach hang
    string fullName;    // Ho va ten
    string idCard;      // So CCCD
    string address;     // Dia chi

public:
    // Constructor mac dinh
    Customer() {
        id = "";
        fullName = "";
        idCard = "";
        address = "";
    }

    // Constructor day du tham so
    Customer(string id, string fullName, string idCard, string address) {
        this->id = id;
        this->fullName = fullName;
        this->idCard = idCard;
        this->address = address;
    }

    // Các ham Getter & Setter
    string getId() const { return id; }
    void setId(string id) { this->id = id; }

    string getFullName() const { return fullName; }
    void setFullName(string fullName) { this->fullName = fullName; }

    string getIdCard() const { return idCard; }
    void setIdCard(string idCard) { this->idCard = idCard; }

    string getAddress() const { return address; }
    void setAddress(string address) { this->address = address; }

    // Ham hien thi thong tin dang bang (dong bo voi giao diện main)
    void display() const {
        cout << "| " << id;
        for (int i = id.length(); i < 7; i++) cout << " ";
        cout << " | " << fullName;
        for (int i = fullName.length(); i < 21; i++) cout << " ";
        cout << " | " << idCard;
        for (int i = idCard.length(); i < 14; i++) cout << " ";
        cout << " | " << address;
        for (int i = address.length(); i < 25; i++) cout << " ";
        cout << " |\n";
    }

    // 1. TUẦN TỰ HÓA: Chuyen doi doi tuong thanh 1 chuoi de ghi vao file .txt
    string toFileString() const {
        return id + "|" + fullName + "|" + idCard + "|" + address;
    }

    // 2. GIẢI TUẦN TỰ HÓA: Đọc 1 dòng từ file .txt và tách dữ liệu gán vào thuộc tính
    void fromFileString(const string& line) {
        stringstream ss(line);
        getline(ss, id, '|');
        getline(ss, fullName, '|');
        getline(ss, idCard, '|');
        getline(ss, address, '|');
    }
};
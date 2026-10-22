
#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "Entity.h"

using namespace std;

class RatingRule : public Entity {
private:
    string id;             // Mã quy tắc (VD: RR011)
    string serviceType;    // Loại dịch vụ (VD: VOICE, SMS, DATA)
    string description;    // Mô tả quy tắc
    double unitPrice;      // Đơn giá (VND)
    int block;             // Block tính cước (VD: 1 giây, 6 giây, 1024 MB)

public:
    // 1. Constructor mặc định
    RatingRule() : id(""), serviceType(""), description(""), unitPrice(0.0), block(1) {}

    // 2. Constructor có tham số 
    // [TỐI ƯU]: Dùng tham chiếu hằng (const string&) thay vì truyền tham trị (string) để tránh việc copy dữ liệu chuỗi thừa thãi trong RAM.
    RatingRule(const string& id, const string& serviceType, const string& description, double unitPrice, int block)
        : id(id), serviceType(serviceType), description(description), unitPrice(unitPrice), block(block) {}

    // 3. Getter / Setter cơ bản
    string getId() const override { return id; }
    string getServiceType() const { return serviceType; }
    string getDescription() const { return description; }
    
    double getUnitPrice() const { return unitPrice; }
    void setUnitPrice(double price) { unitPrice = price; }
    
    int getBlock() const { return block; }
    void setBlock(int b) { block = b; }

    // 4. In thông tin hiển thị dạng bảng
    void display() const override {
        cout << "| " << left << setw(8) << id
             << "| " << setw(18) << serviceType
             << "| " << setw(27) << description
             << "| " << setw(13) << (long long)unitPrice
             << "| " << setw(9) << block << "|\n";
    }

    string toFileString() const override {
        return id + "|" + serviceType + "|" + description + "|" + 
               to_string((long long)unitPrice) + "|" + to_string(block);
    }

    void fromFileString(const string& line) override {
        stringstream ss(line);
        string item;

        getline(ss, id, '|');
        getline(ss, serviceType, '|');
        getline(ss, description, '|');

        if (getline(ss, item, '|')) unitPrice = stod(item);
        if (getline(ss, item, '|')) block = stoi(item);
    }
};


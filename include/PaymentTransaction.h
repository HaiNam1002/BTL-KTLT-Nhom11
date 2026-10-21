#pragma once
#include "Entity.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

class PaymentTransaction : public Entity {
private:
    string paymentId;      // Mã giao dịch (Khóa chính)
    string invoiceId;      // Mã hóa đơn
    double amount;          // Số tiền thanh toán
    string paymentMethod;  // Phương thức thanh toán
    string paymentDate;    // Ngày giao dịch

public:
    PaymentTransaction() : amount(0.0) {}

    // Tối ưu truyền const string& để tránh copy chuỗi
    PaymentTransaction(const string& id, const string& invId, double amt, const string& method, const string& date)
        : paymentId(id), invoiceId(invId), amount(amt), paymentMethod(method), paymentDate(date) {}

    // Getters
    string getId() const override { return paymentId; }
    string getInvoiceId() const { return invoiceId; }
    double getAmount() const { return amount; }
    string getPaymentMethod() const { return paymentMethod; }
    string getPaymentDate() const { return paymentDate; }

    // Setters (phục vụ thao tác Update)
    void setAmount(double amt) { if (amt >= 0) amount = amt; }
    void setPaymentMethod(const string& method) { paymentMethod = method; }
    void setPaymentDate(const string& date) { paymentDate = date; }

    // Hiển thị dạng dòng bảng căn cột
    void display() const override {
        cout << "| " << left << setw(10) << paymentId 
             << "| " << setw(12) << invoiceId 
             << "| " << setw(16) << (long long)amount 
             << "| " << setw(15) << paymentMethod 
             << "| " << setw(12) << paymentDate << " |\n";
    }

    // Chuyển đối tượng thành chuỗi ghi file text
    string toFileString() const override {
        return paymentId + "|" + invoiceId + "|" + to_string((long long)amount) + "|" + paymentMethod + "|" + paymentDate;
    }

    // Đọc dữ liệu từ file text
    void fromFileString(const string& line) override {
        stringstream ss(line);
        string amtStr;

        getline(ss, paymentId, '|');
        getline(ss, invoiceId, '|');
        getline(ss, amtStr, '|');
        getline(ss, paymentMethod, '|');
        getline(ss, paymentDate, '|');

        amount = amtStr.empty() ? 0.0 : stod(amtStr);
    }
};
#pragma once
#include "Entity.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class GoiCuoc : public Entity {
private:
    string maGoi;
    string tenGoi;
    double giaCuoc;
    int thoiHan; // Tính bằng ngày

public:
    // Constructor mac dinh
    GoiCuoc() {
        maGoi = "";
        tenGoi = "";
        giaCuoc = 0.0;
        thoiHan = 0;
    }

    // Constructor day du tham so
    GoiCuoc(string ma, string ten, double gia, int han) {
        maGoi = ma;
        tenGoi = ten;
        giaCuoc = gia;
        thoiHan = han;
    }

    // Getters (Bắt buộc phải có chữ const ở cuối để khớp với Entity.h)
    string getId() const override { return maGoi; } 
    string getMaGoi() { return maGoi; }        
    string getTenGoi() { return tenGoi; }
    double getGiaCuoc() { return giaCuoc; }
    int getThoiHan() { return thoiHan; }

    // Setters
    void setMaGoi(string ma) { maGoi = ma; }
    void setTenGoi(string ten) { tenGoi = ten; }
    void setGiaCuoc(double gia) { 
        if (gia >= 0) giaCuoc = gia; 
    }
    void setThoiHan(int han) { 
        if (han > 0) thoiHan = han; 
    }

    // Ham hien thi thong tin dang bang (Phải có const override)
    void display() const override {
        cout << "| " << maGoi;
        for (int i = maGoi.length(); i < 7; i++) cout << " ";
        cout << " | " << tenGoi;
        for (int i = tenGoi.length(); i < 20; i++) cout << " ";
        cout << " | " << (long long)giaCuoc;
        string giaStr = to_string((long long)giaCuoc);
        for (int i = giaStr.length(); i < 14; i++) cout << " ";
        cout << " | " << thoiHan << " ngay |\n";
    }

    // Tuan tu hoa (Phải có const override)
    string toFileString() const override {
        return maGoi + "|" + tenGoi + "|" + to_string((long long)giaCuoc) + "|" + to_string(thoiHan);
    }

    // Giai tuan tu hoa (Phải khớp tham số const string&)
    void fromFileString(const string& line) override {
        stringstream ss(line);
        string giaStr, hanStr;

        getline(ss, maGoi, '|');
        getline(ss, tenGoi, '|');
        getline(ss, giaStr, '|');
        getline(ss, hanStr, '|');

        if (giaStr != "") {
            giaCuoc = stod(giaStr);
        } else {
            giaCuoc = 0.0;
        }

        if (hanStr != "") {
            thoiHan = stoi(hanStr);
        } else {
            thoiHan = 0;
        }
    }
};
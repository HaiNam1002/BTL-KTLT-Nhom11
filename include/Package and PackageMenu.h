#pragma once
#include "Entity.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

class GoiCuoc : public Entity {
private:
    string maGoi;
    string tenGoi;
    double giaCuoc;
    int thoiHan; // Tính bằng ngày

public:
    GoiCuoc() : giaCuoc(0.0), thoiHan(0) {}
    GoiCuoc(const string& ma, const string& ten, double gia, int han)
        : maGoi(ma), tenGoi(ten), giaCuoc(gia), thoiHan(han) {}

    // Getters
    string getId() const override { return maGoi; }
    string getTenGoi() const { return tenGoi; }
    double getGiaCuoc() const { return giaCuoc; }
    int getThoiHan() const { return thoiHan; }

    // Setters
    void setTenGoi(const string& ten) { tenGoi = ten; }
    void setGiaCuoc(double gia) { if (gia >= 0) giaCuoc = gia; }
    void setThoiHan(int han) { if (han > 0) thoiHan = han; }

    void display() const override {
        cout << "| " << left << setw(10) << maGoi 
             << "| " << setw(20) << tenGoi 
             << "| " << setw(15) << (long long)giaCuoc 
             << "| " << setw(10) << thoiHan << " ngay |\n";
    }

    string toFileString() const override {
        return maGoi + "|" + tenGoi + "|" + to_string((long long)giaCuoc) + "|" + to_string(thoiHan);
    }

    void fromFileString(const string& line) override {
        stringstream ss(line);
        string giaStr, hanStr;

        getline(ss, maGoi, '|');
        getline(ss, tenGoi, '|');
        getline(ss, giaStr, '|');
        getline(ss, hanStr, '|');

        giaCuoc = giaStr.empty() ? 0.0 : stod(giaStr);
        thoiHan = hanStr.empty() ? 0 : stoi(hanStr);
    }
};

class DangKy : public Entity {
private:
    string maDangKy;
    string maThueBao;
    string maGoiCuoc;
    string ngayDangKy;

public:
    DangKy() {}
    DangKy(const string& maDK, const string& maTB, const string& maGC, const string& ngay)
        : maDangKy(maDK), maThueBao(maTB), maGoiCuoc(maGC), ngayDangKy(ngay) {}

    string getId() const override { return maDangKy; }
    string getMaThueBao() const { return maThueBao; }
    string getMaGoiCuoc() const { return maGoiCuoc; }
    string getNgayDangKy() const { return ngayDangKy; }

    void setMaThueBao(const string& maTB) { maThueBao = maTB; }
    void setMaGoiCuoc(const string& maGC) { maGoiCuoc = maGC; }
    void setNgayDangKy(const string& ngay) { ngayDangKy = ngay; }

    void display() const override {
        cout << "| " << left << setw(10) << maDangKy 
             << "| " << setw(15) << maThueBao 
             << "| " << setw(15) << maGoiCuoc 
             << "| " << setw(15) << ngayDangKy << " |\n";
    }

    string toFileString() const override {
        return maDangKy + "|" + maThueBao + "|" + maGoiCuoc + "|" + ngayDangKy;
    }

    void fromFileString(const string& line) override {
        stringstream ss(line);
        getline(ss, maDangKy, '|');
        getline(ss, maThueBao, '|');
        getline(ss, maGoiCuoc, '|');
        getline(ss, ngayDangKy, '|');
    }
};

#pragma once
#include "Entity.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

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
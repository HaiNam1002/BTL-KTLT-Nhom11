#pragma once
#include "Entity.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class DangKy : public Entity {
private:
    string maDangKy;
    string maThueBao;
    string maGoiCuoc;
    string ngayDangKy;

public:
    // Constructor mac dinh
    DangKy() {
        maDangKy = "";
        maThueBao = "";
        maGoiCuoc = "";
        ngayDangKy = "";
    }

    // Constructor day du tham so
    DangKy(string maDK, string maTB, string maGC, string ngay) {
        maDangKy = maDK;
        maThueBao = maTB;
        maGoiCuoc = maGC;
        ngayDangKy = ngay;
    }

    // Getters
    string getId() const override { return maDangKy; } 
    string getMaDangKy() { return maDangKy; }  
    string getMaThueBao() { return maThueBao; }
    string getMaGoiCuoc() { return maGoiCuoc; }
    string getNgayDangKy() { return ngayDangKy; }

    // Setters
    void setMaDangKy(string maDK) { maDangKy = maDK; }
    void setMaThueBao(string maTB) { maThueBao = maTB; }
    void setMaGoiCuoc(string maGC) { maGoiCuoc = maGC; }
    void setNgayDangKy(string ngay) { ngayDangKy = ngay; }

    // Ham hien thi thong tin dang bang (Đã sửa lỗi gọi hàm phụ)
    void display() const override {
        cout << "| " << maDangKy;
        for (int i = maDangKy.length(); i < 7; i++) cout << " ";
        cout << " | " << maThueBao;
        for (int i = maThueBao.length(); i < 8; i++) cout << " ";
        cout << " | " << maGoiCuoc;
        for (int i = maGoiCuoc.length(); i < 7; i++) cout << " "; // Dùng trực tiếp maGoiCuoc.length()
        cout << " | " << ngayDangKy;
        for (int i = ngayDangKy.length(); i < 12; i++) cout << " ";
        cout << " |\n";
    }

    // Tuan tu hoa: Chuyen doi doi tuong thanh chuoi de ghi vao file .txt
    string toFileString() const override {
        return maDangKy + "|" + maThueBao + "|" + maGoiCuoc + "|" + ngayDangKy;
    }

    // Giai tuan tu hoa: Doc 1 dong tu file .txt va tach du lieu gan vao thuoc tinh
    void fromFileString(const string& line) override {
        stringstream ss(line);
        getline(ss, maDangKy, '|');
        getline(ss, maThueBao, '|');
        getline(ss, maGoiCuoc, '|');
        getline(ss, ngayDangKy, '|');
    }
};
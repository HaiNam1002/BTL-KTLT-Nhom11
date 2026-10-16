#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct GoiCuoc {
    string maGoi;
    string tenGoi;
    double giaCuoc;
    int thoiHan;
};

struct ThueBao {
    string maThueBao;
    string tenThueBao;
    string soDienThoai;
};

struct DangKy {
    string maDangKy;
    string maThueBao;
    string maGoiCuoc;
    string ngayDangKy;
};

const string FILE_GOI_CUOC = "goicuoc.txt";
const string FILE_DANG_KY = "dangky.txt";

vector<GoiCuoc> danhSachGoiCuoc;
vector<DangKy> danhSachDangKy;

void docFileGoiCuoc() {
    danhSachGoiCuoc.clear();
    ifstream file(FILE_GOI_CUOC);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        GoiCuoc gc;
        if (getline(ss, gc.maGoi, '|') &&
            getline(ss, gc.tenGoi, '|') &&
            ss >> gc.giaCuoc && ss.ignore() &&
            ss >> gc.thoiHan) {
            danhSachGoiCuoc.push_back(gc);
        }
    }
    file.close();
}

void ghiFileGoiCuoc() {
    ofstream file(FILE_GOI_CUOC);
    if (!file.is_open()) return;
    for (const auto& gc : danhSachGoiCuoc) {
        file << gc.maGoi << "|" << gc.tenGoi << "|" << gc.giaCuoc << "|" << gc.thoiHan << "\n";
    }
    file.close();
}

void docFileDangKy() {
    danhSachDangKy.clear();
    ifstream file(FILE_DANG_KY);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        DangKy dk;
        if (getline(ss, dk.maDangKy, '|') &&
            getline(ss, dk.maThueBao, '|') &&
            getline(ss, dk.maGoiCuoc, '|') &&
            getline(ss, dk.ngayDangKy)) {
            danhSachDangKy.push_back(dk);
        }
    }
    file.close();
}

void ghiFileDangKy() {
    ofstream file(FILE_DANG_KY);
    if (!file.is_open()) return;
    for (const auto& dk : danhSachDangKy) {
        file << dk.maDangKy << "|" << dk.maThueBao << "|" << dk.maGoiCuoc << "|" << dk.ngayDangKy << "\n";
    }
    file.close();
}

bool kiemTraTonTaiGoiCuoc(const string& maGoi) {
    for (const auto& gc : danhSachGoiCuoc) {
        if (gc.maGoi == maGoi) return true;
    }
    return false;
}

bool kiemTraTonTaiDangKy(const string& maDK) {
    for (const auto& dk : danhSachDangKy) {
        if (dk.maDangKy == maDK) return true;
    }
    return false;
}

void themGoiCuoc() {
    GoiCuoc gc;
    cout << "Nhap ma goi cuoc: ";
    cin >> gc.maGoi;
    if (kiemTraTonTaiGoiCuoc(gc.maGoi)) {
        cout << "Loi: Ma goi cuoc da ton tai.\n";
        return;
    }
    cout << "Nhap ten goi cuoc: ";
    cin.ignore();
    getline(cin, gc.tenGoi);
    cout << "Nhap gia cuoc: ";
    cin >> gc.giaCuoc;
    if (gc.giaCuoc < 0) {
        cout << "Loi: Gia cuoc khong hop le.\n";
        return;
    }
    cout << "Nhap thoi han (ngay): ";
    cin >> gc.thoiHan;
    if (gc.thoiHan <= 0) {
        cout << "Loi: Thoi han khong hop le.\n";
        return;
    }
    danhSachGoiCuoc.push_back(gc);
    ghiFileGoiCuoc();
    cout << "Them goi cuoc thanh cong.\n";
}

void hienThiDanhSachGoiCuoc() {
    if (danhSachGoiCuoc.empty()) {
        cout << "Danh sach goi cuoc trong.\n";
        return;
    }
    cout << "--- DANH SACH GOI CUOC ---\n";
    for (const auto& gc : danhSachGoiCuoc) {
        cout << "Ma goi: " << gc.maGoi << " | Ten goi: " << gc.tenGoi 
             << " | Gia: " << gc.giaCuoc << " | Thoi han: " << gc.thoiHan << " ngay\n";
    }
}

void timKiemGoiCuoc() {
    string tuKhoa;
    cout << "Nhap ma hoac ten goi cuoc can tim: ";
    cin.ignore();
    getline(cin, tuKhoa);
    bool found = false;
    for (const auto& gc : danhSachGoiCuoc) {
        if (gc.maGoi.find(tuKhoa) != string::npos || gc.tenGoi.find(tuKhoa) != string::npos) {
            cout << "Ma goi: " << gc.maGoi << " | Ten goi: " << gc.tenGoi 
                 << " | Gia: " << gc.giaCuoc << " | Thoi han: " << gc.thoiHan << " ngay\n";
            found = true;
        }
    }
    if (!found) {
        cout << "Khong tim thay goi cuoc phu hop.\n";
    }
}

void capNhatGoiCuoc() {
    string maGoi;
    cout << "Nhap ma goi cuoc can cap nhat: ";
    cin >> maGoi;
    for (auto& gc : danhSachGoiCuoc) {
        if (gc.maGoi == maGoi) {
            cout << "Nhap ten goi cuoc moi: ";
            cin.ignore();
            getline(cin, gc.tenGoi);
            cout << "Nhap gia cuoc moi: ";
            cin >> gc.giaCuoc;
            if (gc.giaCuoc < 0) {
                cout << "Loi: Gia cuoc khong hop le.\n";
                return;
            }
            cout << "Nhap thoi han moi (ngay): ";
            cin >> gc.thoiHan;
            if (gc.thoiHan <= 0) {
                cout << "Loi: Thoi han khong hop le.\n";
                return;
            }
            ghiFileGoiCuoc();
            cout << "Cap nhat thanh cong.\n";
            return;
        }
    }
    cout << "Khong tim thay goi cuoc co ma nay.\n";
}

void xoaGoiCuoc() {
    string maGoi;
    cout << "Nhap ma goi cuoc can xoa: ";
    cin >> maGoi;
    for (const auto& dk : danhSachDangKy) {
        if (dk.maGoiCuoc == maGoi) {
            cout << "Loi: Khong the xoa goi cuoc vi dang duoc su dung trong dang ky.\n";
            return;
        }
    }
    auto it = remove_if(danhSachGoiCuoc.begin(), danhSachGoiCuoc.end(), [&](const GoiCuoc& gc) {
        return gc.maGoi == maGoi;
    });
    if (it != danhSachGoiCuoc.end()) {
        danhSachGoiCuoc.erase(it, danhSachGoiCuoc.end());
        ghiFileGoiCuoc();
        cout << "Xoa goi cuoc thanh cong.\n";
    } else {
        cout << "Khong tim thay goi cuoc co ma nay.\n";
    }
}

void taoDangKy() {
    DangKy dk;
    cout << "Nhap ma dang ky: ";
    cin >> dk.maDangKy;
    if (kiemTraTonTaiDangKy(dk.maDangKy)) {
        cout << "Loi: Ma dang ky da ton tai.\n";
        return;
    }
    cout << "Nhap ma thue bao: ";
    cin >> dk.maThueBao;
    if (dk.maThueBao.empty()) {
        cout << "Loi: Thieu thong tin thue bao bat buoc.\n";
        return;
    }
    cout << "Nhap ma goi cuoc: ";
    cin >> dk.maGoiCuoc;
    if (!kiemTraTonTaiGoiCuoc(dk.maGoiCuoc)) {
        cout << "Loi: Ma goi cuoc khong ton tai.\n";
        return;
    }
    cout << "Nhap ngay dang ky (DD/MM/YYYY): ";
    cin >> dk.ngayDangKy;
    danhSachDangKy.push_back(dk);
    ghiFileDangKy();
    cout << "Tao dang ky thanh cong.\n";
}

void hienThiDanhSachDangKy() {
    if (danhSachDangKy.empty()) {
        cout << "Danh sach dang ky trong.\n";
        return;
    }
    cout << "--- DANH SACH DANG KY ---\n";
    for (const auto& dk : danhSachDangKy) {
        cout << "Ma DK: " << dk.maDangKy << " | Ma thue bao: " << dk.maThueBao 
             << " | Ma goi: " << dk.maGoiCuoc << " | Ngay DK: " << dk.ngayDangKy << "\n";
    }
}

void timKiemDangKy() {
    string tuKhoa;
    cout << "Nhap ma dang ky hoac ma thue bao can tim: ";
    cin >> tuKhoa;
    bool found = false;
    for (const auto& dk : danhSachDangKy) {
        if (dk.maDangKy == tuKhoa || dk.maThueBao == tuKhoa) {
            cout << "Ma DK: " << dk.maDangKy << " | Ma thue bao: " << dk.maThueBao 
                 << " | Ma goi: " << dk.maGoiCuoc << " | Ngay DK: " << dk.ngayDangKy << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "Khong tim thay thong tin dang ky phu hop.\n";
    }
}

void capNhatDangKy() {
    string maDK;
    cout << "Nhap ma dang ky can cap nhat: ";
    cin >> maDK;
    for (auto& dk : danhSachDangKy) {
        if (dk.maDangKy == maDK) {
            cout << "Nhap ma thue bao moi: ";
            cin >> dk.maThueBao;
            if (dk.maThueBao.empty()) {
                cout << "Loi: Thieu thong tin thue bao bat buoc.\n";
                return;
            }
            cout << "Nhap ma goi cuoc moi: ";
            cin >> dk.maGoiCuoc;
            if (!kiemTraTonTaiGoiCuoc(dk.maGoiCuoc)) {
                cout << "Loi: Ma goi cuoc khong ton tai.\n";
                return;
            }
            cout << "Nhap ngay dang ky moi (DD/MM/YYYY): ";
            cin >> dk.ngayDangKy;
            ghiFileDangKy();
            cout << "Cap nhat dang ky thanh cong.\n";
            return;
        }
    }
    cout << "Khong tim thay ma dang ky nay.\n";
}

void huyDangKy() {
    string maDK;
    cout << "Nhap ma dang ky can huy: ";
    cin >> maDK;
    auto it = remove_if(danhSachDangKy.begin(), danhSachDangKy.end(), [&](const DangKy& dk) {
        return dk.maDangKy == maDK;
    });
    if (it != danhSachDangKy.end()) {
        danhSachDangKy.erase(it, danhSachDangKy.end());
        ghiFileDangKy();
        cout << "Huy dang ky thanh cong.\n";
    } else {
        cout << "Khong tim thay ma dang ky nay.\n";
    }
}

void menuQuanLyGoiCuoc() {
    int chon;
    do {
        cout << "\n=== QUAN LY GOI CUOC ===\n";
        cout << "1. Them goi cuoc\n";
        cout << "2. Hien thi danh sach goi cuoc\n";
        cout << "3. Tim kiem goi cuoc\n";
        cout << "4. Cap nhat thong tin goi cuoc\n";
        cout << "5. Xoa goi cuoc\n";
        cout << "6. Quay lai menu chinh\n";
        cout << "Chon chuc nang (1-6): ";
        cin >> chon;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Du lieu khong hop le. Vui long chon lai.\n";
            continue;
        }
        switch (chon) {
            case 1: themGoiCuoc(); break;
            case 2: hienThiDanhSachGoiCuoc(); break;
            case 3: timKiemGoiCuoc(); break;
            case 4: capNhatGoiCuoc(); break;
            case 5: xoaGoiCuoc(); break;
            case 6: break;
            default: cout << "Lua chon khong hop le. Vui long chon lai.\n";
        }
    } while (chon != 6);
}

void menuQuanLyDangKy() {
    int chon;
    do {
        cout << "\n=== QUAN LY DANG KY GOI CUOC ===\n";
        cout << "1. Tao dang ky goi cuoc\n";
        cout << "2. Hien thi danh sach dang ky\n";
        cout << "3. Tim kiem dang ky\n";
        cout << "4. Cap nhat thong tin dang ky\n";
        cout << "5. Huy dang ky\n";
        cout << "6. Quay lai menu chinh\n";
        cout << "Chon chuc nang (1-6): ";
        cin >> chon;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Du lieu khong hop le. Vui long chon lai.\n";
            continue;
        }
        switch (chon) {
            case 1: taoDangKy(); break;
            case 2: hienThiDanhSachDangKy(); break;
            case 3: timKiemDangKy(); break;
            case 4: capNhatDangKy(); break;
            case 5: huyDangKy(); break;
            case 6: break;
            default: cout << "Lua chon khong hop le. Vui long chon lai.\n";
        }
    } while (chon != 6);
}

int main() {
    docFileGoiCuoc();
    docFileDangKy();
    int chon;
    do {
        cout << "\n=== CHUONG TRINH QUAN LY GOI CUOC VIEN THONG ===\n";
        cout << "1. Quan ly goi cuoc\n";
        cout << "2. Quan ly dang ky goi cuoc\n";
        cout << "3. Thoat chuong trinh\n";
        cout << "Chon phan he (1-3): ";
        cin >> chon;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Du lieu khong hop le. Vui long chon lai.\n";
            continue;
        }
        switch (chon) {
            case 1: menuQuanLyGoiCuoc(); break;
            case 2: menuQuanLyDangKy(); break;
            case 3: cout << "Cam ơn ban da su dung chuong trinh.\n"; break;
            default: cout << "Lua chon khong hop le. Vui long chon lai.\n";
        }
    } while (chon != 3);
    return 0;
}

#include <iostream>
#include <iomanip>
#include "include/Repository.h"
#include "include/Customer.h"
#include "include/Subscription.h"
#include "include/InputHelper.h"

using namespace std;

// --- MENU KHACH HANG ---
void printCustomerHeader() {
    cout << "+---------+-----------------------+----------------+---------------------------+\n";
    cout << "| Ma KH   | Ho va Ten             | CCCD           | Dia Chi                   |\n";
    cout << "+---------+-----------------------+----------------+---------------------------+\n";
}

void menuCustomer(Repository<Customer>& repo, Repository<Subscription>& subRepo) {
    while (true) {
        cout << "\n========== QUAN LY KHACH HANG ==========\n";
        cout << "1. Xem danh sach khach hang\n";
        cout << "2. Them khach hang moi\n";
        cout << "3. Tim kiem khach hang theo Ma\n";
        cout << "4. Cap nhat thong tin khach hang\n";
        cout << "5. Xoa khach hang\n";
        cout << "0. Quay lai Menu chinh\n";
        cout << "========================================\n";
        int choice = InputHelper::getInt("Nhap lua chon: ", 0, 5);
        if (choice == 0) break;

        if (choice == 1) {
            cout << "\n--- DANH SACH KHACH HANG ---\n";
            printCustomerHeader();
            for (const auto& c : repo.getAll()) c.display();
            cout << "+---------+-----------------------+----------------+---------------------------+\n";
            cout << "Tong so: " << repo.getAll().size() << " khach hang.\n";
        }
        else if (choice == 2) {
            string id = InputHelper::getString("Nhap ma KH (vi du KH011): ");
            if (repo.findById(id) != nullptr) {
                cout << "[Loi] Ma khach hang da ton tai!\n";
                continue;
            }
            string name = InputHelper::getString("Nhap ho va ten: ");
            string idCard = InputHelper::getString("Nhap so CCCD: ");
            string addr = InputHelper::getString("Nhap dia chi: ");
            Customer newC(id, name, idCard, addr);
            if (repo.add(newC)) cout << "=> Them thanh cong!\n";
        }
        else if (choice == 3) {
            string id = InputHelper::getString("Nhap ma KH can tim: ");
            Customer* c = repo.findById(id);
            if (c) {
                printCustomerHeader();
                c->display();
                cout << "+---------+-----------------------+----------------+---------------------------+\n";
            } else {
                cout << "[Thong bao] Khong tim thay!\n";
            }
        }
        else if (choice == 4) {
            string id = InputHelper::getString("Nhap ma KH can sua: ");
            Customer* c = repo.findById(id);
            if (!c) { cout << "[Loi] Khong tim thay!\n"; continue; }
            string newName = InputHelper::getString("Nhap ten moi: ");
            string newAddr = InputHelper::getString("Nhap dia chi moi: ");
            c->setFullName(newName);
            c->setAddress(newAddr);
            repo.update(*c);
            cout << "=> Cap nhat thanh cong!\n";
        }
        else if (choice == 5) {
            string id = InputHelper::getString("Nhap ma KH can xoa: ");
            Customer* c = repo.findById(id);
            if (!c) { cout << "[Loi] Khong tim thay!\n"; continue; }

            // Kiem tra rang buoc khoa ngoai
            bool hasSub = false;
            for (const auto& s : subRepo.getAll()) {
                if (s.getCustomerId() == id) { hasSub = true; break; }
            }
            if (hasSub) {
                cout << "[Tu choi] Khach hang dang so huu thue bao, khong the xoa!\n";
                continue;
            }

            string confirm = InputHelper::getString("Xac nhan xoa? (y/n): ");
            if (confirm == "y" || confirm == "Y") {
                repo.remove(id);
                cout << "=> Da xoa thanh cong!\n";
            }
        }
    }
}

// --- MENU THUE BAO ---
void printSubHeader() {
    cout << "+---------+--------------+----------+-------------+---------------+------------+\n";
    cout << "| Ma TB   | So DT        | Ma KH    | Loai Hinh   | So Du (dong)  | Trang Thai |\n";
    cout << "+---------+--------------+----------+-------------+---------------+------------+\n";
}

void menuSubscription(Repository<Subscription>& subRepo, Repository<Customer>& cusRepo) {
    while (true) {
        cout << "\n========== QUAN LY THUE BAO / SIM ==========\n";
        cout << "1. Xem danh sach thue bao\n";
        cout << "2. Dang ky thue bao moi\n";
        cout << "3. Tim kiem thue bao theo So dien thoai\n";
        cout << "4. Doi trang thai thue bao (Khoa/Mo)\n";
        cout << "5. Huy thue bao\n";
        cout << "0. Quay lai Menu chinh\n";
        cout << "============================================\n";
        int choice = InputHelper::getInt("Nhap lua chon: ", 0, 5);
        if (choice == 0) break;

        if (choice == 1) {
            cout << "\n--- DANH SACH THUE BAO ---\n";
            printSubHeader();
            for (const auto& s : subRepo.getAll()) s.display();
            cout << "+---------+--------------+----------+-------------+---------------+------------+\n";
            cout << "Tong so: " << subRepo.getAll().size() << " thue bao.\n";
        }
        else if (choice == 2) {
            string id = InputHelper::getString("Nhap ma TB (vi du TB011): ");
            if (subRepo.findById(id) != nullptr) {
                cout << "[Loi] Ma thue bao da ton tai!\n";
                continue;
            }
            string phone = InputHelper::getString("Nhap so dien thoai (10 chu so): ");
            string cusId = InputHelper::getString("Nhap ma KH so huu: ");
            if (cusRepo.findById(cusId) == nullptr) {
                cout << "[Loi] Ma khach hang khong ton tai tren he thong!\n";
                continue;
            }
            int typeChoice = InputHelper::getInt("Chon loai (1. TRA_TRUOC, 2. TRA_SAU): ", 1, 2);
            string subType = (typeChoice == 1) ? "TRA_TRUOC" : "TRA_SAU";
            double bal = (subType == "TRA_TRUOC") ? 50000.0 : 0.0;

            Subscription newSub(id, phone, cusId, subType, bal, "ACTIVE");
            if (subRepo.add(newSub)) cout << "=> Kich hoat thue bao thanh cong!\n";
        }
        else if (choice == 3) {
            string phone = InputHelper::getString("Nhap so dien thoai can tim: ");
            bool found = false;
            for (const auto& s : subRepo.getAll()) {
                if (s.getPhoneNumber() == phone) {
                    printSubHeader();
                    s.display();
                    cout << "+---------+--------------+----------+-------------+---------------+------------+\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "[Thong bao] Khong tim thay so thue bao nay!\n";
        }
        else if (choice == 4) {
            string id = InputHelper::getString("Nhap ma TB can cap nhat: ");
            Subscription* s = subRepo.findById(id);
            if (!s) { cout << "[Loi] Khong tim thay!\n"; continue; }
            cout << "Trang thai hien tai: " << s->getStatus() << "\n";
            int stChoice = InputHelper::getInt("Chon trang thai moi (1. ACTIVE, 2. BLOCKED, 3. CANCELLED): ", 1, 3);
            string newSt = (stChoice == 1) ? "ACTIVE" : (stChoice == 2 ? "BLOCKED" : "CANCELLED");
            s->setStatus(newSt);
            subRepo.update(*s);
            cout << "=> Cap nhat trang thai thanh cong!\n";
        }
        else if (choice == 5) {
            string id = InputHelper::getString("Nhap ma TB can huy: ");
            Subscription* s = subRepo.findById(id);
            if (!s) { cout << "[Loi] Khong tim thay!\n"; continue; }
            string confirm = InputHelper::getString("Ban co chac chan muon huy so nay? (y/n): ");
            if (confirm == "y" || confirm == "Y") {
                subRepo.remove(id);
                cout << "=> Da huy thue bao thanh cong!\n";
            }
        }
    }
}

// --- HAM MAIN DIEU KHIEN CHINH ---
int main() {
    Repository<Customer> customerRepo("data/customers.txt");
    customerRepo.loadFromFile();

    Repository<Subscription> subRepo("data/subscriptions.txt");
    subRepo.loadFromFile();

    while (true) {
        cout << "\n============================================\n";
        cout << "   HE THONG QUAN LY CUOC & DICH VU VIEN THONG\n";
        cout << "============================================\n";
        cout << "1. Quan ly Khach hang (UC 1)\n";
        cout << "2. Quan ly Thue bao / SIM (UC 2)\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "============================================\n";
        int mainChoice = InputHelper::getInt("Nhap lua chon: ", 0, 2);

        if (mainChoice == 0) break;
        if (mainChoice == 1) menuCustomer(customerRepo, subRepo);
        else if (mainChoice == 2) menuSubscription(subRepo, customerRepo);
    }

    cout << "\nXin cam on da su dung chuong trinh!\n";
    return 0;
}
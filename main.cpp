#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>
#include "include/InputHelper.h"
#include "include/Repository.h"
#include "include/Customer.h"
#include "include/PaymentTransaction.h"
#include "include/TopUp.h"
#include "include/GoiCuoc.h"
#include "include/DangKy.h"

using namespace std;

void menuCustomer(Repository<Customer>& repo);
void menuPayment(Repository<PaymentTransaction>& repo);
void menuTopUp(Repository<TopUp>& topupRepo, Repository<PaymentTransaction>& paymentRepo);

void printHeader() {
    cout << "+---------+-----------------------+----------------+---------------------------+\n";
    cout << "| Ma KH   | Ho va Ten             | CCCD           | Dia Chi                   |\n";
    cout << "+---------+-----------------------+----------------+---------------------------+\n";
}

void printFooter() {
    cout << "+---------+-----------------------+----------------+---------------------------+\n";
}

void menuCustomer(Repository<Customer>& repo) {
    while (true) {
        cout << "\n========== QUAN LY KHACH HANG ==========\n";
        cout << "1. Xem danh sach khach hang\n";
        cout << "2. Them khach hang moi\n";
        cout << "3. Tim kiem khach hang theo Ma\n";
        cout << "4. Cap nhat thong tin khach hang\n";
        cout << "5. Xoa khach hang\n";
        cout << "0. Quay lai / Thoat\n";
        cout << "========================================\n";
        int choice = InputHelper::getInt("Nhap lua chon: ", 0, 5);

        if (choice == 0) break;

        if (choice == 1) {
            cout << "\n--- DANH SACH KHACH HANG ---\n";
            printHeader();
            for (const auto& c : repo.getAll()) {
                c.display();
            }
            printFooter();
            cout << "Tong so: " << repo.getAll().size() << " khach hang.\n";
        }
        else if (choice == 2) {
            cout << "\n--- THEM KHACH HANG MOI ---\n";
            string id = InputHelper::getString("Nhap ma KH (vi du KH011): ");
            if (repo.findById(id) != nullptr) {
                cout << "[Loi] Ma khach hang da ton tai tren he thong!\n";
                continue;
            }
            string name = InputHelper::getString("Nhap ho va ten: ");
            string idCard = InputHelper::getString("Nhap so CCCD: ");
            string addr = InputHelper::getString("Nhap dia chi: ");

            Customer newC(id, name, idCard, addr);
            if (repo.add(newC)) {
                cout << "=> Them thanh cong va da luu vao file!\n";
            }
        }
        else if (choice == 3) {
            string id = InputHelper::getString("Nhap ma KH can tim: ");
            Customer* c = repo.findById(id);
            if (c) {
                cout << "\nThong tin tim thay:\n";
                printHeader();
                c->display();
                printFooter();
            } else {
                cout << "[Thong bao] Khong tim thay ma KH nay!\n";
            }
        }
        else if (choice == 4) {
            string id = InputHelper::getString("Nhap ma KH can sua: ");
            Customer* c = repo.findById(id);
            if (!c) {
                cout << "[Loi] Khong tim thay ma KH nay!\n";
                continue;
            }
            cout << "Thong tin hien tai: " << c->getFullName() << " - " << c->getAddress() << "\n";
            string newName = InputHelper::getString("Nhap ten moi (nhap giu nguyen thi go lai ten): ");
            string newAddr = InputHelper::getString("Nhap dia chi moi: ");
            c->setFullName(newName);
            c->setAddress(newAddr);
            repo.update(*c);
            cout << "=> Cap nhat thanh cong va da dong bo vao file!\n";
        }
        else if (choice == 5) {
            string id = InputHelper::getString("Nhap ma KH can xoa: ");
            Customer* c = repo.findById(id);
            if (!c) {
                cout << "[Loi] Khong tim thay ma KH de xoa!\n";
                continue;
            }
            string confirm = InputHelper::getString("Ban co chac chan muon xoa? (y/n): ");
            if (confirm == "y" || confirm == "Y") {
                repo.remove(id);
                cout << "=> Da xoa thanh cong va cap nhat file!\n";
            } else {
                cout << "=> Da huy thao tac xoa.\n";
            }
        }
    }
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

void printPaymentHeader() {
    cout << "+-----------+-------------+-----------------+----------------+--------------+\n";
    cout << "| Ma GD     | Ma Hoa Don  | So Tien (VND)   | Phuong Thuc    | Ngay GD      |\n";
    cout << "+-----------+-------------+-----------------+----------------+--------------+\n";
}

void printPaymentFooter() {
    cout << "+-----------+-------------+-----------------+----------------+--------------+\n";
}

void menuQuanLyGoiCuoc(Repository<GoiCuoc>& repoGC, Repository<DangKy>& repoDK) {
    while (true) {
        cout << "\n=== QUAN LY GOI CUOC (HAI) ===\n";
        cout << "1. Them goi cuoc moi\n";
        cout << "2. Hien thi danh sach goi cuoc\n";
        cout << "3. Xoa goi cuoc\n";
        cout << "0. Quay lai menu chinh\n";
        
        int chon = InputHelper::getInt("Chon chuc nang: ", 0, 3);
        if (chon == 0) break;

        if (chon == 1) {
            string id = InputHelper::getString("Nhap Ma goi cuoc: ");
            if (repoGC.findById(id) != nullptr) {
                cout << "[Loi] Ma goi da ton tai!\n";
                continue;
            }
            string ten = InputHelper::getString("Nhap Ten goi cuoc: ");
            double gia = InputHelper::getDouble("Nhap Gia cuoc (VNĐ): ", 0);
            int han = InputHelper::getInt("Nhap Thoi han (Ngay): ", 1);

            GoiCuoc gc(id, ten, gia, han);
            repoGC.add(gc);
            cout << "Them goi cuoc thanh cong!\n";

        } else if (chon == 2) {
            cout << "\n--- DANH SACH GOI CUOC ---\n";
            for (const auto& gc : repoGC.getAll()) gc.display();

        } else if (chon == 3) {
            string id = InputHelper::getString("Nhap Ma goi can xoa: ");
            bool dangSuDung = false;
            for (const auto& dk : repoDK.getAll()) {
                if (dk.getMaGoiCuoc() == id) { dangSuDung = true; break; }
            }
            
            if (dangSuDung) {
                cout << "[Loi] Khong the xoa vi co thue bao dang su dung goi nay!\n";
            } else if (repoGC.remove(id)) {
                cout << "Xoa goi cuoc thanh cong!\n";
            } else {
                cout << "[Loi] Khong tim thay ma goi nay!\n";
            }
        }
    }
}

void menuQuanLyDangKy(Repository<DangKy>& repoDK, Repository<GoiCuoc>& repoGC) {
    while (true) {
        cout << "\n=== QUAN LY DANG KY GOI CUOC (HAI) ===\n";
        cout << "1. Dang ky goi cuoc cho thue bao\n";
        cout << "2. Hien thi lich su dang ky\n";
        cout << "0. Quay lai menu chinh\n";

        int chon = InputHelper::getInt("Chon chuc nang: ", 0, 2);
        if (chon == 0) break;

        if (chon == 1) {
            string maDK = InputHelper::getString("Nhap Ma don dang ky: ");
            if (repoDK.findById(maDK) != nullptr) {
                cout << "[Loi] Ma don dang ky da ton tai!\n"; continue;
            }
            string maTB = InputHelper::getString("Nhap Ma thue bao: ");
            string maGC = InputHelper::getString("Nhap Ma goi cuoc can dang ky: ");
            
            if (repoGC.findById(maGC) == nullptr) {
                cout << "[Loi] Ma goi cuoc khong ton tai trong he thong!\n"; continue;
            }
            string ngayDK = InputHelper::getString("Nhap ngay dang ky (DD/MM/YYYY): ");

            DangKy dk(maDK, maTB, maGC, ngayDK);
            repoDK.add(dk);
            cout << "Dang ky goi cuoc thanh cong!\n";

        } else if (chon == 2) {
            cout << "\n--- LICH SU DANG KY ---\n";
            for (const auto& dk : repoDK.getAll()) dk.display();
        }
    }
}

// ====================== HÀM MAIN TỔNG CỦA NHÓM ======================
int main() {
     Repository<Customer> customerRepo("data/customers.txt");
    customerRepo.loadFromFile();
    Repository<PaymentTransaction> paymentRepo("data/payments.txt");
    paymentRepo.loadFromFile();
    Repository<TopUp> topupRepo("data/topups.txt");
    topupRepo.loadFromFile();
    Repository<GoiCuoc> goiCuocRepo("data/goicuoc.txt");
    goiCuocRepo.loadFromFile();
    Repository<DangKy> dangKyRepo("data/dangky.txt");
    dangKyRepo.loadFromFile();

   while (true) {
        cout << "\n================ HE THONG TELECOM BILLING ================\n";
        cout << "1. Quan ly Khach hang (Nam)\n";
        cout << "2. Quan ly Goi cuoc (Hai)\n";
        cout << "3. Quan ly Dang ky goi cuoc (Hai)\n";
        cout << "0. Thoat he thong\n";
        cout << "=========================================================\n";
        
        int choice = InputHelper::getInt("Nhap lua chon cua ban: ", 0, 5);

        if (choice == 0) break;

        switch (choice) {
            case 1:
                menuCustomer(customerRepo);
                break;
            case 2:
                menuQuanLyGoiCuoc(goiCuocRepo, dangKyRepo);
                break;
            case 3:
                menuQuanLyDangKy(dangKyRepo, goiCuocRepo);
                break;
        }
    }

    cout << "\nCam on da su dung he thong!\n";

    return 0;
}

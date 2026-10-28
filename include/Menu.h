#pragma once
#include <iostream>
#include <iomanip>
#include "Repository.h"
#include "RatingRule.h"
#include "Invoice.h"
#include "InputHelper.h"

// ==================== 1. QUẢN LÝ BIỂU PHÍ TÍNH CƯỚC ====================
inline void menuRatingRule(Repository<RatingRule>& repo) {
    while (true) {
        cout << "\n========== QUAN LY BIEU PHI TINH CUOC (RATING) ==========\n";
        cout << "1. Xem danh sach quy tac tinh cuoc\n";
        cout << "2. Them quy tac tinh cuoc moi\n";
        cout << "3. Tim kiem quy tac theo Ma\n";
        cout << "4. Cap nhat don gia quy tac\n";
        cout << "5. Xoa quy tac tinh cuoc\n";
        cout << "0. Quay lai\n";
        cout << "=========================================================\n";
        int choice = InputHelper::getInt("Nhap lua chon: ", 0, 5);

        if (choice == 0) break;

        if (choice == 1) {
            cout << "\n---------------------------- DANH SACH BIEU PHI TINH CUOC ----------------------------\n";
            cout << "+---------+-------------------+----------------------------+--------------+----------+\n";
            cout << "| Ma QT   | Loai Dich Vu      | Mo Ta Quy Tac              | Don Gia(VND) | Block    |\n";
            cout << "+---------+-------------------+----------------------------+--------------+----------+\n";
            for (const auto& item : repo.getAll()) item.display();
            cout << "+---------+-------------------+----------------------------+--------------+----------+\n";
            cout << "Tong so: " << repo.getAll().size() << " quy tac tinh cuoc.\n";
        }
        else if (choice == 2) {
            cout << "\n--- THEM QUY TAC TINH CUOC MOI ---\n";
            string id = InputHelper::getString("Nhap ma quy tac (vi du RR011): ");
            if (repo.findById(id) != nullptr) {
                std::cout << "[Loi] Ma quy tac da ton tai tren he thong!\n";
                continue;
            }
            string code = InputHelper::getString("Nhap loai dich vu (VOICE/SMS/DATA): ");
            string desc = InputHelper::getString("Nhap mo ta quy tac: ");
            double price = InputHelper::getDouble("Nhap don gia (VND): ", 0.0);
            int block = InputHelper::getInt("Nhap block tinh cuoc (giay/MB): ", 1, 3600);

            RatingRule rule(id, code, desc, price, block);
            if (repo.add(rule)) {
                std::
        }
        else if (choice == 3) {
            string id = InputHelper::getString("Nhap ma quy tac can tim: ");
            RatingRule* r = repo.findById(id);
            if (r) {
                cout << "\nThong tin tim thay:\n";
                cout << "+---------+-------------------+----------------------------+--------------+----------+\n";
                r->display();
                cout << "+---------+-------------------+----------------------------+--------------+----------+\n";
            } else {
                std::cout << "[Thong bao] Khong tim thay ma quy tac nay!\n";
            }
        }
        else if (choice == 4) {
            string id = InputHelper::getString("Nhap ma quy tac can sua: ");
            RatingRule* r = repo.findById(id);
            if (!r) {
                cout << "[Loi] Khong tim thay ma quy tac!\n";
                continue;
            }
           cout << "Don gia hien tai: " << (long long)r->getUnitPrice() << " VND\n";
            double newPrice = InputHelper::getDouble("Nhap don gia moi (VND): ", 0.0);
            r->setUnitPrice(newPrice);
            repo.update(*r);
            cout << "=> Cap nhat don gia thanh cong va da luu file!\n";
        }
        else if (choice == 5) {
            string id = InputHelper::getString("Nhap ma quy tac can xoa: ");
            RatingRule* r = repo.findById(id);
            if (!r) {
                std::cout << "[Loi] Khong tim thay ma quy tac de xoa!\n";
                continue;
            }
            string confirm = InputHelper::getString("Xac nhan xoa quy tac nay? (y/n): ");
            if (confirm == "y" || confirm == "Y") {
                repo.remove(id);
               cout << "=> Da xoa quy tac va cap nhat file!\n";
            } else {
                cout << "=> Da huy thao tac xoa.\n";
            }
        }
    }
}

// ==================== 2. QUẢN LÝ HÓA ĐƠN CƯỚC (CÓ THỐNG KÊ) ====================
inline void menuInvoice(Repository<Invoice>& repo) {
    while (true) {
        cout << "\n========== QUAN LY HOA DON THANH TOAN (INVOICE) ==========\n";
        cout << "1. Xem danh sach hoa don\n";
        cout << "2. Lap hoa don cuoc moi\n";
        cout << "3. Tim kiem hoa don theo Ma\n";
        cout << "4. Cap nhat trang thai thanh toan\n";
        cout << "5. Thong ke tong doanh thu & cong no\n";
        cout << "6. Xoa / Huy hoa don\n";
        cout << "0. Quay lai\n";
        cout << "=========================================================\n";
        int choice = InputHelper::getInt("Nhap lua chon: ", 0, 6);

        if (choice == 0) break;

        if (choice == 1) {
            cout << "\n---------------------------- DANH SACH HOA DON CUOC ----------------------------\n";
            cout << "+-----------+-----------+-----------+---------------+-------------+--------------+\n";
            cout << "| Ma HD     | Ma TB     | Chu Ky    | Tong Tien(VND)| Trang Thai  | Ngay Lap     |\n";
            cout << "+-----------+-----------+-----------+---------------+-------------+--------------+\n";
            for (const auto& item : repo.getAll()) item.display();
            cout << "+-----------+-----------+-----------+---------------+-------------+--------------+\n";
            cout << "Tong so: " << repo.getAll().size() << " hoa don.\n";
        }
        else if (choice == 2) {
            cout << "\n--- LAP HOA DON CUOC MOI ---\n";
            string id = InputHelper::getString("Nhap ma hoa don (vi du INV011): ");
            if (repo.findById(id) != nullptr) {
                cout << "[Loi] Ma hoa don da ton tai tren he thong!\n";
                continue;
            }
            string sub = InputHelper::getString("Nhap ma thue bao (vi du TB001): ");
            string month = InputHelper::getString("Nhap chu ky cuoc (MM/YYYY): ");
            double amount = InputHelper::getDouble("Nhap tong tien cuoc (VND): ", 0.0);
            string date = InputHelper::getString("Nhap ngay lap (DD/MM/YYYY): ");

            Invoice inv(id, sub, month, amount, "UNPAID", date);
            if (repo.add(inv)) {
                \cout << "=> Lap hoa don thanh cong va da dong bo vao file!\n";
            }
        }
        else if (choice == 3) {
            std::string id = InputHelper::getString("Nhap ma hoa don can tim: ");
            Invoice* inv = repo.findById(id);
            if (inv) {
                cout << "\nThong tin tim thay:\n";
                cout << "+-----------+-----------+-----------+---------------+-------------+--------------+\n";
                inv->display();
                cout << "+-----------+-----------+-----------+---------------+-------------+--------------+\n";
            } else {
                cout << "[Thong bao] Khong tim thay hoa don nay!\n";
            }
        }
        else if (choice == 4) {
            string id = InputHelper::getString("Nhap ma hoa don can cap nhat: ");
            Invoice* inv = repo.findById(id);
            if (!inv) {
                std::cout << "[Loi] Khong tim thay hoa don!\n";
                continue;
            }
            cout << "Trang thai hien tai: " << inv->getPaymentStatus() << "\n";
            string status = InputHelper::getString("Nhap trang thai moi (PAID/UNPAID): ");
            inv->setPaymentStatus(status);
            repo.update(*inv);
            std::cout << "=> Cap nhat trang thai thanh cong!\n";
        }
        else if (choice == 5) {
            double totalPaid = 0;
            double totalUnpaid = 0;
            int countPaid = 0;
            int countUnpaid = 0;

            for (const auto& inv : repo.getAll()) {
                if (inv.getPaymentStatus() == "PAID") {
                    totalPaid += inv.getTotalAmount();
                    countPaid++;
                } else {
                    totalUnpaid += inv.getTotalAmount();
                    countUnpaid++;
                }
            }

            cout << "\n================ THONG KE TAI CHINH CUOC ================\n";
            cout << "1. Da thanh toan (PAID): " << countPaid << " hoa don - Tong: " << (long long)totalPaid << " VND\n";
            cout << "2. Chua thanh toan (UNPAID): " << countUnpaid << " hoa don - Tong: " << (long long)totalUnpaid << " VND\n";
            cout << "=========================================================\n";
        }
        else if (choice == 6) {
            string id = InputHelper::getString("Nhap ma hoa don can xoa: ");
            Invoice* inv = repo.findById(id);
            if (!inv) {
                cout << "[Loi] Khong tim thay hoa don de xoa!\n";
                continue;
            }
            if (inv->getPaymentStatus() == "UNPAID") {
                cout << "[Canh bao] Hoa don nay CHUA THANH TOAN! ";
            }
            string confirm = InputHelper::getString("Xac nhan xoa hoa don? (y/n): ");
            if (confirm == "y" || confirm == "Y") {
                repo.remove(id);
                cout << "=> Da xoa hoa don va cap nhat file!\n";
            } else {
                cout << "=> Da huy thao tac xoa.\n";
            }
        }
    }
}

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
        std::cout << "\n========== QUAN LY BIEU PHI TINH CUOC (RATING) ==========\n";
        std::cout << "1. Xem danh sach quy tac tinh cuoc\n";
        std::cout << "2. Them quy tac tinh cuoc moi\n";
        std::cout << "3. Tim kiem quy tac theo Ma\n";
        std::cout << "4. Cap nhat don gia quy tac\n";
        std::cout << "5. Xoa quy tac tinh cuoc\n";
        std::cout << "0. Quay lai\n";
        std::cout << "=========================================================\n";
        int choice = InputHelper::getInt("Nhap lua chon: ", 0, 5);

        if (choice == 0) break;

        if (choice == 1) {
            std::cout << "\n---------------------------- DANH SACH BIEU PHI TINH CUOC ----------------------------\n";
            std::cout << "+---------+-------------------+----------------------------+--------------+----------+\n";
            std::cout << "| Ma QT   | Loai Dich Vu      | Mo Ta Quy Tac              | Don Gia(VND) | Block    |\n";
            std::cout << "+---------+-------------------+----------------------------+--------------+----------+\n";
            for (const auto& item : repo.getAll()) item.display();
            std::cout << "+---------+-------------------+----------------------------+--------------+----------+\n";
            std::cout << "Tong so: " << repo.getAll().size() << " quy tac tinh cuoc.\n";
        }
        else if (choice == 2) {
            std::cout << "\n--- THEM QUY TAC TINH CUOC MOI ---\n";
            std::string id = InputHelper::getString("Nhap ma quy tac (vi du RR011): ");
            if (repo.findById(id) != nullptr) {
                std::cout << "[Loi] Ma quy tac da ton tai tren he thong!\n";
                continue;
            }
            std::string code = InputHelper::getString("Nhap loai dich vu (VOICE/SMS/DATA): ");
            std::string desc = InputHelper::getString("Nhap mo ta quy tac: ");
            double price = InputHelper::getDouble("Nhap don gia (VND): ", 0.0);
            int block = InputHelper::getInt("Nhap block tinh cuoc (giay/MB): ", 1, 3600);

            RatingRule rule(id, code, desc, price, block);
            if (repo.add(rule)) {
                std::cout << "=> Them quy tac thanh cong va da dong bo vao file!\n";
            }
        }
        else if (choice == 3) {
            std::string id = InputHelper::getString("Nhap ma quy tac can tim: ");
            RatingRule* r = repo.findById(id);
            if (r) {
                std::cout << "\nThong tin tim thay:\n";
                std::cout << "+---------+-------------------+----------------------------+--------------+----------+\n";
                r->display();
                std::cout << "+---------+-------------------+----------------------------+--------------+----------+\n";
            } else {
                std::cout << "[Thong bao] Khong tim thay ma quy tac nay!\n";
            }
        }
        else if (choice == 4) {
            std::string id = InputHelper::getString("Nhap ma quy tac can sua: ");
            RatingRule* r = repo.findById(id);
            if (!r) {
                std::cout << "[Loi] Khong tim thay ma quy tac!\n";
                continue;
            }
            std::cout << "Don gia hien tai: " << (long long)r->getUnitPrice() << " VND\n";
            double newPrice = InputHelper::getDouble("Nhap don gia moi (VND): ", 0.0);
            r->setUnitPrice(newPrice);
            repo.update(*r);
            std::cout << "=> Cap nhat don gia thanh cong va da luu file!\n";
        }
        else if (choice == 5) {
            std::string id = InputHelper::getString("Nhap ma quy tac can xoa: ");
            RatingRule* r = repo.findById(id);
            if (!r) {
                std::cout << "[Loi] Khong tim thay ma quy tac de xoa!\n";
                continue;
            }
            std::string confirm = InputHelper::getString("Xac nhan xoa quy tac nay? (y/n): ");
            if (confirm == "y" || confirm == "Y") {
                repo.remove(id);
                std::cout << "=> Da xoa quy tac va cap nhat file!\n";
            } else {
                std::cout << "=> Da huy thao tac xoa.\n";
            }
        }
    }
}

// ==================== 2. QUẢN LÝ HÓA ĐƠN CƯỚC (CÓ THỐNG KÊ) ====================
inline void menuInvoice(Repository<Invoice>& repo) {
    while (true) {
        std::cout << "\n========== QUAN LY HOA DON THANH TOAN (INVOICE) ==========\n";
        std::cout << "1. Xem danh sach hoa don\n";
        std::cout << "2. Lap hoa don cuoc moi\n";
        std::cout << "3. Tim kiem hoa don theo Ma\n";
        std::cout << "4. Cap nhat trang thai thanh toan\n";
        std::cout << "5. Thong ke tong doanh thu & cong no\n";
        std::cout << "6. Xoa / Huy hoa don\n";
        std::cout << "0. Quay lai\n";
        std::cout << "=========================================================\n";
        int choice = InputHelper::getInt("Nhap lua chon: ", 0, 6);

        if (choice == 0) break;

        if (choice == 1) {
            std::cout << "\n---------------------------- DANH SACH HOA DON CUOC ----------------------------\n";
            std::cout << "+-----------+-----------+-----------+---------------+-------------+--------------+\n";
            std::cout << "| Ma HD     | Ma TB     | Chu Ky    | Tong Tien(VND)| Trang Thai  | Ngay Lap     |\n";
            std::cout << "+-----------+-----------+-----------+---------------+-------------+--------------+\n";
            for (const auto& item : repo.getAll()) item.display();
            std::cout << "+-----------+-----------+-----------+---------------+-------------+--------------+\n";
            std::cout << "Tong so: " << repo.getAll().size() << " hoa don.\n";
        }
        else if (choice == 2) {
            std::cout << "\n--- LAP HOA DON CUOC MOI ---\n";
            std::string id = InputHelper::getString("Nhap ma hoa don (vi du INV011): ");
            if (repo.findById(id) != nullptr) {
                std::cout << "[Loi] Ma hoa don da ton tai tren he thong!\n";
                continue;
            }
            std::string sub = InputHelper::getString("Nhap ma thue bao (vi du TB001): ");
            std::string month = InputHelper::getString("Nhap chu ky cuoc (MM/YYYY): ");
            double amount = InputHelper::getDouble("Nhap tong tien cuoc (VND): ", 0.0);
            std::string date = InputHelper::getString("Nhap ngay lap (DD/MM/YYYY): ");

            Invoice inv(id, sub, month, amount, "UNPAID", date);
            if (repo.add(inv)) {
                std::cout << "=> Lap hoa don thanh cong va da dong bo vao file!\n";
            }
        }
        else if (choice == 3) {
            std::string id = InputHelper::getString("Nhap ma hoa don can tim: ");
            Invoice* inv = repo.findById(id);
            if (inv) {
                std::cout << "\nThong tin tim thay:\n";
                std::cout << "+-----------+-----------+-----------+---------------+-------------+--------------+\n";
                inv->display();
                std::cout << "+-----------+-----------+-----------+---------------+-------------+--------------+\n";
            } else {
                std::cout << "[Thong bao] Khong tim thay hoa don nay!\n";
            }
        }
        else if (choice == 4) {
            std::string id = InputHelper::getString("Nhap ma hoa don can cap nhat: ");
            Invoice* inv = repo.findById(id);
            if (!inv) {
                std::cout << "[Loi] Khong tim thay hoa don!\n";
                continue;
            }
            std::cout << "Trang thai hien tai: " << inv->getPaymentStatus() << "\n";
            std::string status = InputHelper::getString("Nhap trang thai moi (PAID/UNPAID): ");
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

            std::cout << "\n================ THONG KE TAI CHINH CUOC ================\n";
            std::cout << "1. Da thanh toan (PAID): " << countPaid << " hoa don - Tong: " << (long long)totalPaid << " VND\n";
            std::cout << "2. Chua thanh toan (UNPAID): " << countUnpaid << " hoa don - Tong: " << (long long)totalUnpaid << " VND\n";
            std::cout << "=========================================================\n";
        }
        else if (choice == 6) {
            std::string id = InputHelper::getString("Nhap ma hoa don can xoa: ");
            Invoice* inv = repo.findById(id);
            if (!inv) {
                std::cout << "[Loi] Khong tim thay hoa don de xoa!\n";
                continue;
            }
            if (inv->getPaymentStatus() == "UNPAID") {
                std::cout << "[Canh bao] Hoa don nay CHUA THANH TOAN! ";
            }
            std::string confirm = InputHelper::getString("Xac nhan xoa hoa don? (y/n): ");
            if (confirm == "y" || confirm == "Y") {
                repo.remove(id);
                std::cout << "=> Da xoa hoa don va cap nhat file!\n";
            } else {
                std::cout << "=> Da huy thao tac xoa.\n";
            }
        }
    }
}

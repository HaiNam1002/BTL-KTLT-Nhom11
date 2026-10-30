#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <stdexcept>

// --- THƯ VIỆN LÕI ---
#include "include/InputHelper.h"
#include "include/Repository.h"
#include "include/Entity.h"

// --- THƯ VIỆN CÁC THỰC THỂ ---
#include "include/Customer.h"
#include "include/Subscription.h"
#include "include/GoiCuoc.h"
#include "include/DangKy.h"
#include "include/PaymentTransaction.h"
#include "include/TopUp.h"
#include "include/RatingRule.h"
#include "include/Invoice.h"
#include "include/BillingRecord.h"
#include "include/BillingHistory.h"

using namespace std;

// =========================================================================
// KHAI BÁO PROTOTYPE HÀM 
// =========================================================================
void menuCustomer(Repository<Customer>& repo, Repository<Subscription>& subRepo);
void menuSubscription(Repository<Subscription>& subRepo, Repository<Customer>& cusRepo);
void menuQuanLyGoiCuoc(Repository<GoiCuoc>& repoGC, Repository<DangKy>& repoDK);
void menuQuanLyDangKy(Repository<DangKy>& repoDK, Repository<GoiCuoc>& repoGC);
void menuPayment(Repository<PaymentTransaction>& repo);
void menuTopUp(Repository<TopUp>& topupRepo, Repository<PaymentTransaction>& paymentRepo);
void menuRatingRule(Repository<RatingRule>& repo);
void menuInvoice(Repository<Invoice>& repo);
void menuBillingRecord(Repository<BillingRecord>& repo);
void menuBillingHistory(Repository<BillingHistory>& repo);


// ==================== 1. MENU KHÁCH HÀNG ====================
void printCustomerHeader() {
    cout << "+---------+-----------------------+----------------+---------------------------+\n";
    cout << "| Ma KH   | Ho va Ten             | CCCD           | Dia Chi                   |\n";
    cout << "+---------+-----------------------+----------------+---------------------------+\n";
}
void printCustomerFooter() {
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

        try {
            if (choice == 1) {
                cout << "\n--- DANH SACH KHACH HANG ---\n";
                printCustomerHeader();
                for (const auto& c : repo.getAll()) c.display();
                printCustomerFooter();
                cout << "Tong so: " << repo.getAll().size() << " khach hang.\n";
            }
            else if (choice == 2) {
                cout << "\n--- THEM KHACH HANG MOI ---\n";
                string id = InputHelper::getString("Nhap ma KH (vi du KH011): ");
                if (repo.findById(id) != nullptr) {
                    cout << "[Loi] Ma khach hang da ton tai!\n";
                    continue;
                }
                string name = InputHelper::getString("Nhap ho va ten: ");
                string idCard = InputHelper::getString("Nhap so CCCD: ");
                string addr = InputHelper::getString("Nhap dia chi: ");
                Customer newC(id, name, idCard, addr);
                if (repo.add(newC)) cout << "=> Them thanh cong va da luu vao file!\n";
            }
            else if (choice == 3) {
                string id = InputHelper::getString("Nhap ma KH can tim: ");
                Customer* c = repo.findById(id);
                if (c) {
                    cout << "\nThong tin tim thay:\n";
                    printCustomerHeader();
                    c->display();
                    printCustomerFooter();
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
                string newName = InputHelper::getString("Nhap ten moi (nhap giu nguyen thi go lai ten cu): ");
                string newAddr = InputHelper::getString("Nhap dia chi moi (nhap giu nguyen thi go lai dia chi cu): ");
                
                c->setFullName(newName);
                c->setAddress(newAddr);
                repo.saveToFile();
                cout << "=> Cap nhat thanh cong va da dong bo vao file!\n";
            }
            else if (choice == 5) {
                string id = InputHelper::getString("Nhap ma KH can xoa: ");
                Customer* c = repo.findById(id);
                if (!c) {
                    cout << "[Loi] Khong tim thay ma KH de xoa!\n";
                    continue;
                }

                bool hasSub = false;
                for (const auto& s : subRepo.getAll()) {
                    if (s.getCustomerId() == id) { hasSub = true; break; }
                }
                if (hasSub) {
                    cout << "[Tu choi] Khach hang dang so huu thue bao, khong the xoa!\n";
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
        } catch (const exception& e) {
            cout << "=> [LOI]: " << e.what() << "\n";
        }
    }
}

// ==================== 2. MENU THUÊ BAO ====================
void printSubHeader() {
    cout << "+---------+--------------+----------+-------------+---------------+------------+\n";
    cout << "| Ma TB   | So DT        | Ma KH    | Loai Hinh   | So Du (dong)  | Trang Thai |\n";
    cout << "+---------+--------------+----------+-------------+---------------+------------+\n";
}
void printSubFooter() {
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

        try {
            if (choice == 1) {
                cout << "\n--- DANH SACH THUE BAO ---\n";
                printSubHeader();
                for (const auto& s : subRepo.getAll()) s.display();
                printSubFooter();
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
                        printSubFooter();
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
                subRepo.saveToFile();
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
        } catch (const exception& e) {
            cout << "=> [LOI]: " << e.what() << "\n";
        }
    }
}

// ==================== 3. MENU GÓI CƯỚC ====================
void menuQuanLyGoiCuoc(Repository<GoiCuoc>& repoGC, Repository<DangKy>& repoDK) {
    while (1) {
        cout << "\n==========QUAN LY GOI CUOC==========\n";
        cout << "1. Xem danh sach goi cuoc (Read)\n";
        cout << "2. Them goi cuoc moi\n";
        cout << "3. Tim kiem goi cuoc\n";
        cout << "4. Cap nhat thong tin goi cuoc\n";
        cout << "5. Xoa goi cuoc\n";
        cout << "0. Quay lai menu chinh\n";
        
        int chon = InputHelper::getInt("Chon chuc nang [0-5]: ", 0, 5);
        if (chon == 0) break;

        if (chon == 1) {
            cout << "\n-------------------- DANH SACH GOI CUOC --------------------\n";
            cout << "+---------+----------------------+----------------+----------+\n";
            cout << "| Ma Goi  | Ten Goi Cuoc         | Gia Cuoc (VND) | Thoi Han |\n";
            cout << "+---------+----------------------+----------------+----------+\n";
            
            vector<GoiCuoc> danhSach = repoGC.getAll();
            if (danhSach.size() == 0) {
                cout << "|                  Chua co goi cuoc nao trong he thong!                  |\n";
            } else {
                for (int i = 0; i < danhSach.size(); i++) {
                    danhSach[i].display();
                }
            }
            cout << "+---------+----------------------+----------------+----------+\n";
            cout << "Tong so: " << danhSach.size() << " goi cuoc.\n";
        }
       
        else if (chon == 2) {
            cout << "\n--- THEM GOI CUOC MOI ---\n";
            string maGoi = InputHelper::getString("Nhap Ma goi cuoc: ");
            if (repoGC.findById(maGoi) != nullptr) {
                cout << "[Loi] Ma goi da ton tai trong he thong!\n";
                continue;
            }
            string tenGoi = InputHelper::getString("Nhap Ten goi cuoc: ");
            double giaCuoc = InputHelper::getDouble("Nhap Gia cuoc (VND): ", 0.0);
            int thoiHan = InputHelper::getInt("Nhap Thoi han (Ngay): ", 1, 3650);

            GoiCuoc goiCuocMoi(maGoi, tenGoi, giaCuoc, thoiHan);
            if (repoGC.add(goiCuocMoi)) {
                cout << "=> Them goi cuoc thanh cong va da luu vao file!\n";
            }
        }
    
        else if (chon == 3) {
            cout << "\n--- TIM KIEM GOI CUOC ---\n";
            string tuKhoa = InputHelper::getString("Nhap Ma goi hoac Ten goi can tim: ");
            
            cout << "\n---------------- KET QUA TIM KIEM ----------------\n";
            cout << "+---------+----------------------+----------------+----------+\n";
            cout << "| Ma Goi  | Ten Goi Cuoc         | Gia Cuoc (VND) | Thoi Han |\n";
            cout << "+---------+----------------------+----------------+----------+\n";
            
            vector<GoiCuoc> danhSach = repoGC.getAll();
            int demKetQua = 0;
            
            for (int i = 0; i < danhSach.size(); i++) {
                // Kiểm tra nếu từ khóa khớp với Mã gói hoặc nằm bên trong Tên gói
                if (danhSach[i].getMaGoi() == tuKhoa || danhSach[i].getTenGoi().find(tuKhoa) != string::npos) {
                    danhSach[i].display();
                    demKetQua++;
                }
            }
            
            cout << "+---------+----------------------+----------------+----------+\n";
            if (demKetQua == 0) {
                cout << "=> Khong tim thay goi cuoc nao khop voi tu khoa: \"" << tuKhoa << "\"\n";
            } else {
                cout << "=> Tim thay " << demKetQua << " ket qua phu hop.\n";
            }
        }

        else if (chon == 4) {
            cout << "\n--- CAP NHAT THONG TIN GOI CUOC ---\n";
            string maGoi = InputHelper::getString("Nhap Ma goi cuoc can sua: ");
            GoiCuoc* goiCuoc = repoGC.findById(maGoi);
            
            if (goiCuoc == nullptr) {
                cout << "[Loi] Khong tim thay ma goi cuoc nay!\n";
                continue;
            }

            cout << "=> Tim thay goi cuoc. Nhap thong tin moi:\n";
            string tenMoi = InputHelper::getString("Nhap Ten goi cuoc moi: ");
            double giaMoi = InputHelper::getDouble("Nhap Gia cuoc moi (VND): ", 0.0);
            int thoiHanMoi = InputHelper::getInt("Nhap Thoi han moi (Ngay): ", 1, 3650);

            goiCuoc->setTenGoi(tenMoi);
            goiCuoc->setGiaCuoc(giaMoi);
            goiCuoc->setThoiHan(thoiHanMoi);

            repoGC.saveToFile();
            cout << "=> Cap nhat thong tin goi cuoc thanh cong va da dong bo file!\n";
        }
        else if (chon == 5) {
            cout << "\n--- XOA GOI CUOC ---\n";
            string maGoi = InputHelper::getString("Nhap Ma goi can xoa: ");
            bool dangSuDung = false;
            
            vector<DangKy> danhSachDangKy = repoDK.getAll();
            for (int i = 0; i < danhSachDangKy.size(); i++) {
                if (danhSachDangKy[i].getMaGoiCuoc() == maGoi) { 
                    dangSuDung = true; 
                    break; 
                }
            }
            
            if (dangSuDung) {
                cout << "[Loi] Khong the xoa vi co thue bao dang su dung goi nay!\n";
            } else {
                string xacNhan = InputHelper::getString("Ban co chac chan muon xoa goi nay? (y/n): ");
                if (xacNhan == "y" || xacNhan == "Y") {
                    if (repoGC.remove(maGoi)) {
                        cout << "=> Xoa goi cuoc thanh cong va cap nhat file!\n";
                    } else {
                        cout << "[Loi] Khong tim thay ma goi nay de xoa!\n";
                    }
                } else {
                    cout << "=> Da huy thao tac xoa.\n";
                }
            }
        }
    }
}

// ==================== 4. MENU ĐĂNG KÝ ====================

void menuQuanLyDangKy(Repository<DangKy>& khoDangKy, Repository<GoiCuoc>& khoGoiCuoc) {
    while (1) {
        cout << "\n==========QUAN LY DANG KY GOI CUOC==========\n";
        cout << "1. Xem danh sach dang ky\n";
        cout << "2. Dang ky goi cuoc moi\n";
        cout << "3. Tim kiem thong tin dang ky\n";
        cout << "4. Cap nhat thong tin dang ky\n";
        cout << "5. Huy / Xoa dang ky\n";
        cout << "0. Quay lai menu chinh\n";

        int chon = InputHelper::getInt("Chon chuc nang [0-5]: ", 0, 5);
        if (chon == 0) break;

        // CHỨC NĂNG 1: XEM DANH SÁCH (READ)
        if (chon == 1) {
            cout << "\n----------------- LICH SU DANG KY GOI CUOC -----------------\n";
            cout << "+---------+----------+---------+--------------+\n";
            cout << "| Ma DK   | Ma TB    | Ma Goi  | Ngay Dang Ky |\n";
            cout << "+---------+----------+---------+--------------+\n";
            
            vector<DangKy> danhSach = khoDangKy.getAll();
            if (danhSach.size() == 0) {
                cout << "|            Chua co thong tin dang ky nao!            |\n";
            } else {
                for (int i = 0; i < danhSach.size(); i++) {
                    danhSach[i].display();
                }
            }
            cout << "+---------+----------+---------+--------------+\n";
            cout << "Tong so: " << danhSach.size() << " luot dang ky.\n";
        } 
        // CHỨC NĂNG 2: ĐĂNG KÝ MỚI (CREATE)
        else if (chon == 2) {
            cout << "\n--- DANG KY GOI CUOC MOI ---\n";
            string maDK = InputHelper::getString("Nhap Ma don dang ky: ");
            if (khoDangKy.findById(maDK) != nullptr) {
                cout << "[Loi] Ma don dang ky da ton tai trong he thong!\n"; 
                continue;
            }
            string maTB = InputHelper::getString("Nhap Ma thue bao: ");
            string maGC = InputHelper::getString("Nhap Ma goi cuoc can dang ky: ");
            
            if (khoGoiCuoc.findById(maGC) == nullptr) {
                cout << "[Loi] Ma goi cuoc khong ton tai trong he thong!\n"; 
                continue;
            }
            string ngayDK = InputHelper::getString("Nhap ngay dang ky (DD/MM/YYYY): ");

            DangKy donDangKy(maDK, maTB, maGC, ngayDK);
            if (khoDangKy.add(donDangKy)) {
                cout << "=> Dang ky goi cuoc thanh cong va da luu vao file!\n";
            }
        } 
        // CHỨC NĂNG 3: TÌM KIẾM ĐĂNG KÝ (SEARCH) - BỔ SUNG MỚI
        else if (chon == 3) {
            cout << "\n--- TIM KIEM DON DANG KY ---\n";
            string tuKhoa = InputHelper::getString("Nhap Ma DK hoac Ma thue bao can tim: ");
            
            cout << "\n---------------- KET QUA TIM KIEM ----------------\n";
            cout << "+---------+----------+---------+--------------+\n";
            cout << "| Ma DK   | Ma TB    | Ma Goi  | Ngay Dang Ky |\n";
            cout << "+---------+----------+---------+--------------+\n";
            
            vector<DangKy> danhSach = khoDangKy.getAll();
            int demKetQua = 0;
            
            for (int i = 0; i < danhSach.size(); i++) {
                // Khớp chính xác hoặc gần đúng theo Mã ĐK hoặc Mã Thuê Bao
                if (danhSach[i].getMaDangKy() == tuKhoa || danhSach[i].getMaThueBao() == tuKhoa) {
                    danhSach[i].display();
                    demKetQua++;
                }
            }
            
            cout << "+---------+----------+---------+--------------+\n";
            if (demKetQua == 0) {
                cout << "=> Khong tim thay don dang ky nao khop voi tu khoa: \"" << tuKhoa << "\"\n";
            } else {
                cout << "=> Tim thay " << demKetQua << " ket qua phu hop.\n";
            }
        } 
        // CHỨC NĂNG 4: CẬP NHẬT / SỬA (UPDATE) - BỔ SUNG MỚI
        else if (chon == 4) {
            cout << "\n--- CAP NHAT THONG TIN DANG KY ---\n";
            string maDK = InputHelper::getString("Nhap Ma don dang ky can sua: ");
            DangKy* donDangKy = khoDangKy.findById(maDK);
            
            if (donDangKy == nullptr) {
                cout << "[Loi] Khong tim thay ma don dang ky nay!\n";
                continue;
            }

            cout << "=> Tim thay don dang ky. Nhap thong tin moi:\n";
            string maTBMoi = InputHelper::getString("Nhap Ma thue bao moi: ");
            string maGCMoi = InputHelper::getString("Nhap Ma goi cuoc moi: ");
            
            if (khoGoiCuoc.findById(maGCMoi) == nullptr) {
                cout << "[Loi] Ma goi cuoc moi khong ton tai tren he thong! Huy cap nhat.\n";
                continue;
            }
            string ngayDKMoi = InputHelper::getString("Nhap ngay dang ky moi (DD/MM/YYYY): ");

            // Cập nhật thông tin thông qua Setter
            donDangKy->setMaThueBao(maTBMoi);
            donDangKy->setMaGoiCuoc(maGCMoi);
            donDangKy->setNgayDangKy(ngayDKMoi);

            // Đồng bộ lưu xuống file
            khoDangKy.saveToFile();
            cout << "=> Cap nhat thong tin dang ky thanh cong va da dong bo file!\n";
        } 
        // CHỨC NĂNG 5: HỦY / XÓA ĐĂNG KÝ (DELETE)
        else if (chon == 5) {
            cout << "\n--- HUY DANG KY GOI CUOC ---\n";
            string maDK = InputHelper::getString("Nhap Ma don dang ky can huy: ");
            
            if (khoDangKy.findById(maDK) == nullptr) {
                cout << "[Loi] Khong tim thay ma don dang ky nay!\n";
                continue;
            }

            string xacNhan = InputHelper::getString("Ban co chac chan muon huy don nay? (y/n): ");
            if (xacNhan == "y" || xacNhan == "Y") {
                if (khoDangKy.remove(maDK)) {
                    cout << "=> Huy dang ky thanh cong va da cap nhat file!\n";
                } else {
                    cout << "[Loi] Khong the xoa duoc don dang ky!\n";
                }
            } else {
                cout << "=> Da huy thao tac.\n";
            }
        }
    }
}

// ==================== 5. MENU THANH TOÁN ====================
void printPaymentHeader() {
    cout << "+-----------+-------------+-----------------+----------------+--------------+\n";
    cout << "| Ma GD     | Ma Hoa Don  | So Tien (VND)   | Phuong Thuc    | Ngay GD      |\n";
    cout << "+-----------+-------------+-----------------+----------------+--------------+\n";
}
void printPaymentFooter() {
    cout << "+-----------+-------------+-----------------+----------------+--------------+\n";
}

void menuPayment(Repository<PaymentTransaction>& repo) {
    while (true) {
        cout << "\n========== QUAN LY GIAO DICH THANH TOAN ==========\n";
        cout << "1. Xem danh sach giao dich thanh toan\n";
        cout << "2. Them giao dich thanh toan moi\n";
        cout << "3. Tim kiem giao dich theo Ma GD\n";
        cout << "4. Cap nhat thong tin giao dich\n";
        cout << "5. Xoa / Huy giao dich thanh toan\n";
        cout << "0. Quay lai Menu chinh\n";
        cout << "==================================================\n";
        
        int choice = InputHelper::getInt("Nhap lua chon: ", 0, 5);
        if (choice == 0) break;

        try {
            if (choice == 1) {
                cout << "\n--- DANH SACH GIAO DICH THANH TOAN ---\n";
                printPaymentHeader();
                for (const auto& item : repo.getAll()) item.display();
                printPaymentFooter();
                cout << "Tong so: " << repo.getAll().size() << " giao dich.\n";
            }
            else if (choice == 2) {
                cout << "\n--- THEM GIAO DICH MOI ---\n";
                string id = InputHelper::getString("Nhap Ma giao dich (VD: PAY001): ");
                if (repo.findById(id) != nullptr) {
                    cout << "[Loi] Ma giao dich da ton tai!\n";
                    continue;
                }
                string invId = InputHelper::getString("Nhap Ma Hoa Don can thanh toan: ");
                double amount = InputHelper::getDouble("Nhap So Tien (VND): ", 0.0);
                string method = InputHelper::getString("Nhap Phuong Thuc (Tien mat/Chuyen khoan/The): ");
                string date = InputHelper::getString("Nhap Ngay giao dich (DD/MM/YYYY): ");

                PaymentTransaction payment(id, invId, amount, method, date);
                if (repo.add(payment)) {
                    cout << "=> Them giao dich thanh toan thanh cong!\n";
                }
            }
            else if (choice == 3) {
                string id = InputHelper::getString("Nhap Ma giao dich can tim: ");
                PaymentTransaction* p = repo.findById(id);
                if (p) {
                    cout << "\nThong tin tim thay:\n";
                    printPaymentHeader();
                    p->display();
                    printPaymentFooter();
                } else {
                    cout << "[Thong bao] Khong tim thay giao dich!\n";
                }
            }
            else if (choice == 4) {
                string id = InputHelper::getString("Nhap Ma giao dich can cap nhat: ");
                PaymentTransaction* p = repo.findById(id);
                if (!p) {
                    cout << "[Loi] Khong tim thay giao dich!\n";
                    continue;
                }
                
                cout << "--- Nhap lai thong tin moi hoac go nguyen gia tri cu ---\n";
                string amtStr = InputHelper::getString("Nhap so tien moi: ");
                if (!amtStr.empty()) p->setAmount(stod(amtStr));

                string method = InputHelper::getString("Nhap phuong thuc moi: ");
                if (!method.empty()) p->setPaymentMethod(method);
                
                string date = InputHelper::getString("Nhap ngay giao dich moi: ");
                if (!date.empty()) p->setPaymentDate(date);

                repo.saveToFile();
                cout << "=> Cap nhat thong tin thanh cong!\n";
            }
            else if (choice == 5) {
                string id = InputHelper::getString("Nhap Ma giao dich can xoa: ");
                if (repo.findById(id) == nullptr) {
                    cout << "[Loi] Khong tim thay giao dich de xoa!\n";
                    continue;
                }
                string confirm = InputHelper::getString("Xac nhan xoa giao dich nay? (y/n): ");
                if (confirm == "y" || confirm == "Y") {
                    repo.remove(id);
                    cout << "=> Da xoa giao dich thanh cong!\n";
                }
            }
        } catch (const exception& e) {
            cout << "=> [LOI]: " << e.what() << "\n";
        }
    }
}

// ==================== 6. MENU NẠP TIỀN (FULL CRUD) ====================
void printTopUpHeader() {
    cout << "+-----------+-----------------+-----------------+--------------+\n";
    cout << "| Ma Phieu  | So Dien Thoai   | So Tien (VND)   | Ngay Nap     |\n";
    cout << "+-----------+-----------------+-----------------+--------------+\n";
}
void printTopUpFooter() {
    cout << "+-----------+-----------------+-----------------+--------------+\n";
}

void menuTopUp(Repository<TopUp>& khoNapTien, Repository<PaymentTransaction>& khoThanhToan) {
    while (1) {
        cout << "\n========== QUAN LY NAP TIEN ==========\n";
        cout << "1. Xem danh sach phieu nap (Read)\n";
        cout << "2. Tao phieu nap tien moi (Create)\n";
        cout << "3. Tim kiem phieu nap (Search)\n";
        cout << "4. Cap nhat thong tin phieu nap (Update)\n";
        cout << "5. Xoa phieu nap (Delete)\n";
        cout << "0. Quay lai Menu chinh\n";
        cout << "======================================\n";
        
        int luaChon = InputHelper::getInt("Nhap lua chon [0-5]: ", 0, 5);
        if (luaChon == 0) break;

        // CHỨC NĂNG 1: XEM DANH SÁCH (READ)
        if (luaChon == 1) {
            cout << "\n----------------------- DANH SACH PHIEU NAP -----------------------\n";
            cout << "+-----------+-----------------+-----------------+--------------+\n";
            cout << "| Ma Phieu  | So Dien Thoai   | So Tien (VND)   | Ngay Nap     |\n";
            cout << "+-----------+-----------------+-----------------+--------------+\n";
            
            vector<TopUp> danhSach = khoNapTien.getAll();
            if (danhSach.size() == 0) {
                cout << "|                  Chua co phieu nap nao trong he thong!          |\n";
            } else {
                for (int i = 0; i < danhSach.size(); i++) {
                    danhSach[i].display();
                }
            }
            cout << "+-----------+-----------------+-----------------+--------------+\n";
            cout << "Tong so: " << danhSach.size() << " phieu nap.\n";
        }
        // CHỨC NĂNG 2: TẠO PHIẾU NẠP MỚI (CREATE)
        else if (luaChon == 2) {
            cout << "\n--- THEM PHIEU NAP MOI ---\n";
            string maPhieu = InputHelper::getString("Nhap Ma phieu nap: ");
            if (khoNapTien.findById(maPhieu) != nullptr) {
                cout << "[Loi] Ma phieu da ton tai trong he thong!\n";
                continue;
            }
            string soDienThoai = InputHelper::getString("Nhap So dien thoai can nap: ");
            double soTienNap = InputHelper::getDouble("Nhap So tien nap (VND): ", 0.0);
            string ngayNap = InputHelper::getString("Nhap Ngay nap (DD/MM/YYYY): ");

            TopUp phieuNapMoi(maPhieu, soDienThoai, soTienNap, ngayNap);
            if (khoNapTien.add(phieuNapMoi)) {
                cout << "=> Nap tien thanh cong va da luu vao file!\n";
            }
        }
        // CHỨC NĂNG 3: TÌM KIẾM PHIẾU NẠP (SEARCH)
        else if (luaChon == 3) {
            cout << "\n--- TIM KIEM PHIEU NAP ---\n";
            string tuKhoa = InputHelper::getString("Nhap Ma phieu hoac So dien thoai can tim: ");
            
            cout << "\n---------------- KET QUA TIM KIEM ----------------\n";
            cout << "+-----------+-----------------+-----------------+--------------+\n";
            cout << "| Ma Phieu  | So Dien Thoai   | So Tien (VND)   | Ngay Nap     |\n";
            cout << "+-----------+-----------------+-----------------+--------------+\n";
            
            vector<TopUp> danhSach = khoNapTien.getAll();
            int demKetQua = 0;
            
            for (int i = 0; i < danhSach.size(); i++) {
                if (danhSach[i].getId() == tuKhoa || danhSach[i].getPhoneNumber() == tuKhoa) {
                    danhSach[i].display();
                    demKetQua++;
                }
            }
            
            cout << "+-----------+-----------------+-----------------+--------------+\n";
            if (demKetQua == 0) {
                cout << "=> Khong tim thay phieu nap nao khop voi tu khoa: \"" << tuKhoa << "\"\n";
            } else {
                cout << "=> Tim thay " << demKetQua << " ket qua phu hop.\n";
            }
        }
        // CHỨC NĂNG 4: CẬP NHẬT / SỬA (UPDATE)
        else if (luaChon == 4) {
            cout << "\n--- CAP NHAT THONG TIN PHIEU NAP ---\n";
            string maPhieu = InputHelper::getString("Nhap Ma phieu nap can sua: ");
            TopUp* phieuNap = khoNapTien.findById(maPhieu);
            
            if (phieuNap == nullptr) {
                cout << "[Loi] Khong tim thay ma phieu nap nay!\n";
                continue;
            }

            cout << "=> Tim thay phieu nap. Nhap thong tin moi:\n";
            string soDienThoaiMoi = InputHelper::getString("Nhap So dien thoai moi: ");
            double soTienMoi = InputHelper::getDouble("Nhap So tien moi (VND): ", 0.0);
            string ngayNapMoi = InputHelper::getString("Nhap Ngay nap moi (DD/MM/YYYY): ");

            // Cập nhật thuộc tính thông qua Setter
            phieuNap->setPhoneNumber(soDienThoaiMoi);
            phieuNap->setAmount(soTienMoi);
            phieuNap->setDate(ngayNapMoi);

            // Đồng bộ xuống file text
            khoNapTien.saveToFile();
            cout << "=> Cap nhat thong tin phieu nap thanh cong va da dong bo file!\n";
        }
        // CHỨC NĂNG 5: XÓA PHIẾU NẠP (DELETE)
        else if (luaChon == 5) {
            cout << "\n--- XOA PHIEU NAP ---\n";
            string maPhieu = InputHelper::getString("Nhap Ma phieu nap can xoa: ");
            
            if (khoNapTien.findById(maPhieu) == nullptr) {
                cout << "[Loi] Khong tim thay phieu nap de xoa!\n";
                continue;
            }

            string xacNhan = InputHelper::getString("Ban co chac chan muon xoa phieu nay? (y/n): ");
            if (xacNhan == "y" || xacNhan == "Y") {
                if (khoNapTien.remove(maPhieu)) {
                    cout << "=> Da xoa phieu nap thanh cong va cap nhat file!\n";
                } else {
                    cout << "[Loi] Khong the xoa phieu nap!\n";
                }
            } else {
                cout << "=> Da huy thao tac xoa.\n";
            }
        }
    }
}

// ==================== 7. QUẢN LÝ BIỂU PHÍ TÍNH CƯỚC ====================
void menuRatingRule(Repository<RatingRule>& repo) {
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

        try {
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
                    cout << "[Loi] Ma quy tac da ton tai tren he thong!\n";
                    continue;
                }
                string code = InputHelper::getString("Nhap loai dich vu (VOICE/SMS/DATA): ");
                string desc = InputHelper::getString("Nhap mo ta quy tac: ");
                double price = InputHelper::getDouble("Nhap don gia (VND): ", 0.0);
                int block = InputHelper::getInt("Nhap block tinh cuoc (giay/MB): ", 1, 3600);

                RatingRule rule(id, code, desc, price, block);
                if (repo.add(rule)) {
                    cout << "=> Them quy tac thanh cong va da dong bo vao file!\n";
                }
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
                    cout << "[Thong bao] Khong tim thay ma quy tac nay!\n";
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
                
                repo.saveToFile();
                cout << "=> Cap nhat don gia thanh cong va da luu file!\n";
            }
            else if (choice == 5) {
                string id = InputHelper::getString("Nhap ma quy tac can xoa: ");
                RatingRule* r = repo.findById(id);
                if (!r) {
                    cout << "[Loi] Khong tim thay ma quy tac de xoa!\n";
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
        } catch (const exception& e) {
            cout << "=> [LOI]: " << e.what() << "\n";
        }
    }
}

// ==================== 8. QUẢN LÝ HÓA ĐƠN CƯỚC ====================
void menuInvoice(Repository<Invoice>& repo) {
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

        try {
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
                    cout << "=> Lap hoa don thanh cong va da dong bo vao file!\n";
                }
            }
            else if (choice == 3) {
                string id = InputHelper::getString("Nhap ma hoa don can tim: ");
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
                    cout << "[Loi] Khong tim thay hoa don!\n";
                    continue;
                }
                cout << "Trang thai hien tai: " << inv->getPaymentStatus() << "\n";
                string status = InputHelper::getString("Nhap trang thai moi (PAID/UNPAID): ");
                inv->setPaymentStatus(status);
                
                repo.saveToFile();
                cout << "=> Cap nhat trang thai thanh cong!\n";
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
        } catch (const exception& e) {
            cout << "=> [LOI]: " << e.what() << "\n";
        }
    }
}

// ==================== 9. QUẢN LÝ BẢN GHI CƯỚC ====================
void menuBillingRecord(Repository<BillingRecord>& repo) {
    while (true) {
        cout << "\n================ QUAN LY BAN GHI CUOC ================\n";
        cout << "1. Xem danh sach ban ghi cuoc\n";
        cout << "2. Them ban ghi cuoc moi\n";
        cout << "3. Cap nhat thong tin ban ghi cuoc\n";
        cout << "4. Xoa ban ghi cuoc\n";
        cout << "5. Tim kiem ban ghi theo Ma GD\n";
        cout << "0. Quay lai Menu chinh\n";
        cout << "======================================================\n";
        
        int choice = InputHelper::getInt("Chon chuc nang: ", 0, 5);
        if (choice == 0) break;

        try {
            if (choice == 1) {
                cout << "\n----------------------------------------- DANH SACH BAN GHI CUOC -----------------------------------------\n";
                cout << "+-------------+--------------+---------------+---------------------+------------+--------------+\n";
                cout << "| Ma GD       | So thue bao  | Loai dich vu  | Thoi gian           | Dung luong | Thanh tien   |\n";
                cout << "+-------------+--------------+---------------+---------------------+------------+--------------+\n";
                for (const auto& item : repo.getAll()) item.display();
                cout << "+-------------+--------------+---------------+---------------------+------------+--------------+\n";
                cout << "Tong so: " << repo.getAll().size() << " ban ghi.\n";
            }
            else if (choice == 2) {
                cout << "\n--- THEM BAN GHI CUOC MOI ---\n";
                string id = InputHelper::getString("Nhap Ma giao dich (VD: GD001): ");
                if (repo.findById(id) != nullptr) {
                    cout << "[Loi] Ma giao dich da ton tai!\n";
                    continue;
                }
                string phone = InputHelper::getString("Nhap So thue bao: ");
                string service = InputHelper::getString("Nhap Loai dich vu (Cuoc goi/SMS/Data): ");
                string time = InputHelper::getString("Nhap Thoi gian (YYYY-MM-DD HH:MM): ");
                double usage = InputHelper::getDouble("Nhap Dung luong dung (MB/phut/tin): ", 0.0);
                double amount = InputHelper::getDouble("Nhap Thanh tien (VND): ", 0.0);

                BillingRecord record(id, phone, service, time, usage, amount);
                if (repo.add(record)) {
                    cout << "=> Them ban ghi cuoc thanh cong va da dong bo file!\n";
                }
            }
            else if (choice == 3) {
                string id = InputHelper::getString("Nhap Ma giao dich can cap nhat: ");
                BillingRecord* rec = repo.findById(id);
                if (!rec) {
                    cout << "[Loi] Khong tim thay ban ghi voi Ma GD nay!\n";
                    continue;
                }
                
                string newService = InputHelper::getString("Nhap Loai dich vu moi: ");
                double newAmount = InputHelper::getDouble("Nhap Thanh tien moi (VND): ", 0.0);
                
                rec->setServiceType(newService);
                rec->setAmount(newAmount);
                repo.saveToFile();
                cout << "=> Cap nhat thong tin thanh cong!\n";
            }
            else if (choice == 4) {
                string id = InputHelper::getString("Nhap Ma giao dich can xoa: ");
                if (repo.findById(id) == nullptr) {
                    cout << "[Loi] Khong tim thay ban ghi de xoa!\n";
                    continue;
                }
                string confirm = InputHelper::getString("Xac nhan xoa ban ghi nay? (y/n): ");
                if (confirm == "y" || confirm == "Y") {
                    repo.remove(id);
                    cout << "=> Da xoa ban ghi thanh cong!\n";
                }
            }
            else if (choice == 5) {
                string id = InputHelper::getString("Nhap Ma giao dich can tim: ");
                BillingRecord* rec = repo.findById(id);
                if (rec) {
                    cout << "\nThong tin tim thay:\n";
                    cout << "+-------------+--------------+---------------+---------------------+------------+--------------+\n";
                    rec->display();
                    cout << "+-------------+--------------+---------------+---------------------+------------+--------------+\n";
                } else {
                    cout << "[Thong bao] Khong tim thay ban ghi!\n";
                }
            }
        } catch (const exception& e) {
            cout << "=> [LOI]: " << e.what() << "\n";
        }
    }
}

// ==================== 10. QUẢN LÝ LỊCH SỬ TIÊU DÙNG ====================
void menuBillingHistory(Repository<BillingHistory>& repo) {
    while (true) {
        cout << "\n============ QUAN LY LICH SU TIEU DUNG ============\n";
        cout << "1. Xem danh sach lich su tieu dung\n";
        cout << "2. Them lich su tieu dung moi\n";
        cout << "3. Cap nhat trang thai thanh toan / so tien\n";
        cout << "4. Xoa lich su tieu dung\n";
        cout << "5. Tim kiem lich su theo Ma Lich Su\n";
        cout << "0. Quay lai Menu chinh\n";
        cout << "===================================================\n";
        
        int choice = InputHelper::getInt("Chon chuc nang: ", 0, 5);
        if (choice == 0) break;

        try {
            if (choice == 1) {
                cout << "\n---------------------------------- DANH SACH LICH SU TIEU DUNG ----------------------------------\n";
                cout << "+-------------+--------------+-----------+----------------+-------------------+--------------+\n";
                cout << "| Ma lich su  | So thue bao  | Ky cuoc   | Tong tien(VND) | Trang thai TT     | Ngay cap nhat|\n";
                cout << "+-------------+--------------+-----------+----------------+-------------------+--------------+\n";
                for (const auto& item : repo.getAll()) item.display();
                cout << "+-------------+--------------+-----------+----------------+-------------------+--------------+\n";
                cout << "Tong so: " << repo.getAll().size() << " lich su.\n";
            }
            else if (choice == 2) {
                cout << "\n--- THEM LICH SU TIEU DUNG MOI ---\n";
                string id = InputHelper::getString("Nhap Ma lich su (VD: LS001): ");
                if (repo.findById(id) != nullptr) {
                    cout << "[Loi] Ma lich su da ton tai!\n";
                    continue;
                }
                string phone = InputHelper::getString("Nhap So thue bao: ");
                string cycle = InputHelper::getString("Nhap Ky cuoc (VD: 03/2026): ");
                double amount = InputHelper::getDouble("Nhap Tong tien (VND): ", 0.0);
                string status = InputHelper::getString("Nhap Trang thai TT (Da thanh toan/Chua thanh toan): ");
                string date = InputHelper::getString("Nhap Ngay cap nhat (YYYY-MM-DD): ");

                BillingHistory history(id, phone, cycle, amount, status, date);
                if (repo.add(history)) {
                    cout << "=> Them lich su thanh cong va da dong bo file!\n";
                }
            }
            else if (choice == 3) {
                string id = InputHelper::getString("Nhap Ma lich su can cap nhat: ");
                BillingHistory* hist = repo.findById(id);
                if (!hist) {
                    cout << "[Loi] Khong tim thay lich su nay!\n";
                    continue;
                }
                
                double newAmount = InputHelper::getDouble("Nhap Tong tien moi (VND): ", 0.0);
                string newStatus = InputHelper::getString("Nhap Trang thai TT moi: ");
                string newDate = InputHelper::getString("Nhap Ngay cap nhat moi: ");

                hist->setTotalAmount(newAmount);
                hist->setPaymentStatus(newStatus);
                hist->setUpdatedDate(newDate);

                repo.saveToFile();
                cout << "=> Cap nhat thong tin thanh cong!\n";
            }
            else if (choice == 4) {
                string id = InputHelper::getString("Nhap Ma lich su can xoa: ");
                if (repo.findById(id) == nullptr) {
                    cout << "[Loi] Khong tim thay lich su de xoa!\n";
                    continue;
                }
                string confirm = InputHelper::getString("Xac nhan xoa lich su nay? (y/n): ");
                if (confirm == "y" || confirm == "Y") {
                    repo.remove(id);
                    cout << "=> Da xoa lich su thanh cong!\n";
                }
            }
            else if (choice == 5) {
                string id = InputHelper::getString("Nhap Ma lich su can tim: ");
                BillingHistory* hist = repo.findById(id);
                if (hist) {
                    cout << "\nThong tin tim thay:\n";
                    cout << "+-------------+--------------+-----------+----------------+-------------------+--------------+\n";
                    hist->display();
                    cout << "+-------------+--------------+-----------+----------------+-------------------+--------------+\n";
                } else {
                    cout << "[Thong bao] Khong tim thay lich su tieu dung!\n";
                }
            }
        } catch (const exception& e) {
            cout << "=> [LOI]: " << e.what() << "\n";
        }
    }
}

// =========================================================================
// HÀM MAIN ĐIỀU KHIỂN CHÍNH
// =========================================================================
int main() {
    // 1. Khởi tạo toàn bộ kho dữ liệu từ file text
    Repository<Customer> customerRepo("data/customers.txt");
    customerRepo.loadFromFile();

    Repository<Subscription> subRepo("data/subscriptions.txt");
    subRepo.loadFromFile();

    Repository<PaymentTransaction> paymentRepo("data/payments.txt");
    paymentRepo.loadFromFile();

    Repository<TopUp> topupRepo("data/topups.txt");
    topupRepo.loadFromFile();

    Repository<GoiCuoc> goiCuocRepo("data/goicuoc.txt");    
    goiCuocRepo.loadFromFile();

    Repository<DangKy> dangKyRepo("data/dangky.txt");
    dangKyRepo.loadFromFile();

    Repository<RatingRule> ratingRepo("data/ratingrules.txt");
    ratingRepo.loadFromFile();

    Repository<Invoice> invoiceRepo("data/invoices.txt");
    invoiceRepo.loadFromFile();

    Repository<BillingRecord> recordRepo("data/billing_records.txt");
    recordRepo.loadFromFile();

    Repository<BillingHistory> historyRepo("data/billing_histories.txt");
    historyRepo.loadFromFile();

    // 2. Vòng lặp điều hướng Menu
    while (true) {
        cout << "\n==========================================================\n";
        cout << "       HE THONG QUAN LY CUOC & DICH VU VIEN THONG         \n";
        cout << "==========================================================\n";
        cout << "1. Quan ly Khach hang\n";
        cout << "2. Quan ly Thue bao / SIM\n";
        cout << "3. Quan ly Goi cuoc\n";
        cout << "4. Quan ly Dang ky goi cuoc\n";
        cout << "5. Quan ly Giao dich thanh toan\n";
        cout << "6. Quan ly Nap tien\n";
        cout << "7. Quan ly Bieu phi tinh cuoc\n";
        cout << "8. Quan ly Hoa don & Cong no\n"; 
        cout << "9. Quan ly Ban ghi cuoc (CDR)\n";
        cout << "10. Quan ly Lich su tieu dung\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "==========================================================\n";
        
        int mainChoice = InputHelper::getInt("Nhap lua chon: ", 0, 10); 
        
        if (mainChoice == 0) {
            break;
        } else if (mainChoice == 1) {
            menuCustomer(customerRepo, subRepo);
        } else if (mainChoice == 2) {
            menuSubscription(subRepo, customerRepo);
        } else if (mainChoice == 3) {
            menuQuanLyGoiCuoc(goiCuocRepo, dangKyRepo);
        } else if (mainChoice == 4) {
            menuQuanLyDangKy(dangKyRepo, goiCuocRepo);
        } else if (mainChoice == 5) {
            menuPayment(paymentRepo);
        } else if (mainChoice == 6) {
            menuTopUp(topupRepo, paymentRepo);
        } else if (mainChoice == 7) {
            menuRatingRule(ratingRepo);
        } else if (mainChoice == 8) {
            menuInvoice(invoiceRepo);
        } else if (mainChoice == 9) {
            menuBillingRecord(recordRepo);
        } else if (mainChoice == 10) {
            menuBillingHistory(historyRepo);
        }
    }
    
    cout << "\nXin cam on da su dung chuong trinh!\n";
    return 0;
}
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>
#include "include/InputHelper.h"
#include "include/Repository.h"
#include "include/Customer.h"
#include "include/Subscription.h"
#include "include/GoiCuoc.h"
#include "include/DangKy.h"

using namespace std;

// --- DỌN DẸP BỘ NHỚ ĐỆM ---
void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

// --- KHAI BÁO PROTOTYPE CÁC HÀM MENU (ĐỒNG NHẤT KIỂU DỮ LIỆU) ---
void menuCustomer(Repository<Customer>& repo, Repository<Subscription>& subRepo);
void menuSubscription(Repository<Subscription>& subRepo, Repository<Customer>& cusRepo);
void menuQuanLyGoiCuoc(Repository<GoiCuoc>& repoGC, Repository<DangKy>& repoDK);
void menuQuanLyDangKy(Repository<DangKy>& repoDK, Repository<GoiCuoc>& repoGC);

// --- MENU KHÁCH HÀNG ---
void printHeader() {
#include <limits>
#include <stdexcept>
#include "include/Repository.h"
#include "include/Customer.h"
#include "include/PaymentTransaction.h"
#include "include/TopUp.h"
#include "include/Subscription.h"
#include "include/InputHelper.h"

using namespace std;

// --- KHAI BÁO PROTOTYPE HÀM ---
void menuCustomer(Repository<Customer>& repo, Repository<Subscription>& subRepo);
void menuSubscription(Repository<Subscription>& subRepo, Repository<Customer>& cusRepo);
void menuPayment(Repository<PaymentTransaction>& repo);
void menuTopUp(Repository<TopUp>& topupRepo, Repository<PaymentTransaction>& paymentRepo);

// --- HEADER / FOOTER BẢNG KHÁCH HÀNG ---
void printCustomerHeader() {
    cout << "+---------+-----------------------+----------------+---------------------------+\n";
    cout << "| Ma KH   | Ho va Ten             | CCCD           | Dia Chi                   |\n";
    cout << "+---------+-----------------------+----------------+---------------------------+\n";
}

void printFooter() {
    cout << "+---------+-----------------------+----------------+---------------------------+\n";
}

// Đã sửa: Thêm tham số subRepo vào định nghĩa hàm
void printCustomerFooter() {
    cout << "+---------+-----------------------+----------------+---------------------------+\n";
}

// --- MENU KHÁCH HÀNG ---
void menuCustomer(Repository<Customer>& repo, Repository<Subscription>& subRepo) {
    while (true) {
        cout << "\n========== QUAN LY KHACH HANG ==========\n";
        cout << "1. Xem danh sach khach hang\n";
        cout << "2. Them khach hang moi\n";
        cout << "3. Tim kiem khach hang theo Ma\n";
        cout << "4. Cap nhat thong tin khach hang\n";
        cout << "5. Xoa khach hang\n";
        cout << "0. Quay lai / Thoat\n";
        cout << "0. Quay lai Menu chinh\n";
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
        try {
            if (choice == 1) {
                cout << "\n--- DANH SACH KHACH HANG ---\n";
                printCustomerHeader();
                for (const auto& c : repo.getAll()) c.display();
                printCustomerFooter();
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
                    printCustomerFooter();
                } else {
                    cout << "[Thong bao] Khong tim thay!\n";
                }
            }
            else if (choice == 4) {
                string id = InputHelper::getString("Nhap ma KH can sua: ");
                Customer* c = repo.findById(id);
                if (!c) { cout << "[Loi] Khong tim thay!\n"; continue; }
                
                cout << "--- Bo trong (Nhan Enter) neu muon giu nguyen gia tri cu ---\n";
                string newName = InputHelper::getString("Nhap ten moi (bo trong neu giu nguyen): ");
                string newAddr = InputHelper::getString("Nhap dia chi moi (bo trong neu giu nguyen): ");
                
                if (!newName.empty()) c->setFullName(newName);
                if (!newAddr.empty()) c->setAddress(newAddr);
                
                repo.saveToFile();
                cout << "=> Cap nhat thanh cong!\n";
            }
            else if (choice == 5) {
                string id = InputHelper::getString("Nhap ma KH can xoa: ");
                Customer* c = repo.findById(id);
                if (!c) { cout << "[Loi] Khong tim thay!\n"; continue; }

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
        } catch (const exception& e) {
            cout << "=> [LOI]: " << e.what() << "\n";
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

// --- MENU THUÊ BAO ---
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
            
            // Đã sửa: Kiểm tra ràng buộc khóa ngoại trước khi xóa khách hàng
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
    }
}

// --- MENU THUÊ BAO (Đã thêm hàm bị thiếu) ---
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


// --- MENU GÓI CƯỚC ---
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
            
            // Đã sửa: Thay InputHelper::getDouble thành stod(getString)
            double gia = stod(InputHelper::getString("Nhap Gia cuoc (VND): "));
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

// --- MENU ĐĂNG KÝ GÓI CƯỚC ---
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
    }
}

// --- MENU GIAO DỊCH THANH TOÁN ---
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
        cout << "2. Them giao dich thanh toan moi (Gach no)\n";
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
                for (const auto& p : repo.getAll()) {
                    p.display();
                }
                printPaymentFooter();
                cout << "Tong so: " << repo.getAll().size() << " giao dich.\n";
            }
            else if (choice == 2) {
                string id = InputHelper::getString("Nhap ma GD moi (vi du PAY011): ");
                if (repo.findById(id) != nullptr) {
                    throw invalid_argument("Ma giao dich nay da ton tai!");
                }
                
                string invId = InputHelper::getString("Nhap ma hoa don thanh toan (vi du INV001): ");
                double amt = InputHelper::getDouble("Nhap so tien thanh toan: ", 0);
                string method = InputHelper::getString("Nhap phuong thuc (TIEN_MAT/CHUYEN_KHOAN/THE): ");
                string date = InputHelper::getString("Nhap ngay giao dich (dd/mm/yyyy): ");

                PaymentTransaction newP(id, invId, amt, method, date);
                repo.add(newP);
                cout << "=> Them giao dich thanh cong va da luu vao file!\n";
            }
            else if (choice == 3) {
                string id = InputHelper::getString("Nhap ma GD can tim: ");
                PaymentTransaction* p = repo.findById(id);
                if (p) {
                    printPaymentHeader();
                    p->display();
                    printPaymentFooter();
                } else {
                    cout << "[Thong bao] Khong tim thay giao dich nay!\n";
                }
            }
            else if (choice == 4) {
                string id = InputHelper::getString("Nhap ma GD can sua: ");
                PaymentTransaction* p = repo.findById(id);
                if (!p) {
                    throw invalid_argument("Khong tim thay ma giao dich!");
                }
                
                cout << "--- Bo trong (Nhan Enter) neu muon giu nguyen gia tri cu ---\n";
                string amtStr = InputHelper::getString("Nhap so tien moi (bo trong neu giu nguyen): ");
                if (!amtStr.empty()) p->setAmount(stod(amtStr));

                string method = InputHelper::getString("Nhap phuong thuc moi (bo trong neu giu nguyen): ");
                if (!method.empty()) p->setPaymentMethod(method);
                
                string date = InputHelper::getString("Nhap ngay giao dich moi (bo trong neu giu nguyen): ");
                if (!date.empty()) p->setPaymentDate(date);

                repo.saveToFile();
                cout << "=> Cap nhat gia tri giao dich thanh cong!\n";
            }
            else if (choice == 5) {
                string id = InputHelper::getString("Nhap ma GD can xoa: ");
                PaymentTransaction* p = repo.findById(id);
                if (!p) {
                    throw invalid_argument("Khong tim thay ma giao dich!");
                }
                
                string confirm = InputHelper::getString("Xac nhan xoa giao dich nay? (y/n): ");
                if (confirm == "y" || confirm == "Y") {
                    repo.remove(id);
                    cout << "=> Da xoa giao dich va cap nhat file!\n";
                }
            }
        } catch (const exception& e) {
            cout << "=> [LOI]: " << e.what() << "\n";
        }
    }
}

// --- MENU NẠP TIỀN & DOANH THU ---
void printTopUpHeader() {
    cout << "+-----------+-----------------+-----------------+--------------+\n";
    cout << "| Ma Phieu  | So Dien Thoai   | So Tien (VND)   | Ngay Nap     |\n";
    cout << "+-----------+-----------------+-----------------+--------------+\n";
}

void printTopUpFooter() {
    cout << "+-----------+-----------------+-----------------+--------------+\n";
}

void menuTopUp(Repository<TopUp>& topupRepo, Repository<PaymentTransaction>& paymentRepo) {
    while (true) {
        cout << "\n========== QUAN LY PHIEU NAP TIEN & DOANH THU ==========\n";
        cout << "1. Xem danh sach phieu nap tien\n";
        cout << "2. Tao phieu nap tien moi (Nap tai khoan)\n";
        cout << "3. Tim kiem phieu nap theo Ma phieu\n";
        cout << "4. Cap nhat phieu nap tien\n";
        cout << "5. Xoa phieu nap tien\n";
        cout << "6. THONG KE TONG DOANH THU NHA MANG\n";
        cout << "0. Quay lai Menu chinh\n";
        cout << "=========================================================\n";
        
        int choice = InputHelper::getInt("Nhap lua chon: ", 0, 6);
        if (choice == 0) break;

        try {
            if (choice == 1) {
                cout << "\n--- DANH SACH PHIEU NAP TIEN ---\n";
                printTopUpHeader();
                for (const auto& t : topupRepo.getAll()) {
                    t.display();
                }
                printTopUpFooter();
                cout << "Tong so: " << topupRepo.getAll().size() << " phieu nap.\n";
            }
            else if (choice == 2) {
                string id = InputHelper::getString("Nhap ma phieu nap (vi du TOP011): ");
                if (topupRepo.findById(id) != nullptr) {
                    throw invalid_argument("Ma phieu nap nay da ton tai!");
                }
                
                string phone = InputHelper::getString("Nhap so dien thoai nap: ");
                double amt = InputHelper::getDouble("Nhap so tien nap (VND): ", 0);
                string date = InputHelper::getString("Nhap ngay nap (dd/mm/yyyy): ");

                TopUp newT(id, phone, amt, date);
                topupRepo.add(newT);
                cout << "=> Nap tien thanh cong va da luu vao file!\n";
            }
            else if (choice == 3) {
                string id = InputHelper::getString("Nhap ma phieu can tim: ");
                TopUp* t = topupRepo.findById(id);
                if (t) {
                    printTopUpHeader();
                    t->display();
                    printTopUpFooter();
                } else {
                    cout << "[Thong bao] Khong tim thay phieu nap nay!\n";
                }
            }
            else if (choice == 4) {
                string id = InputHelper::getString("Nhap ma phieu can sua: ");
                TopUp* t = topupRepo.findById(id);
                if (!t) {
                    throw invalid_argument("Khong tim thay phieu nap!");
                }
                
                cout << "--- Bo trong (Nhan Enter) neu muon giu nguyen gia tri cu ---\n";
                string phone = InputHelper::getString("Nhap so dien thoai moi (bo trong neu giu nguyen): ");
                if (!phone.empty()) t->setPhoneNumber(phone);

                string amtStr = InputHelper::getString("Nhap so tien nap moi (bo trong neu giu nguyen): ");
                if (!amtStr.empty()) t->setAmount(stod(amtStr));
                
                string date = InputHelper::getString("Nhap ngay nap moi (bo trong neu giu nguyen): ");
                if (!date.empty()) t->setTopupDate(date);

                topupRepo.saveToFile(); 
                cout << "=> Cap nhat phieu nap thanh cong!\n";
            }
            else if (choice == 5) {
                string id = InputHelper::getString("Nhap ma phieu can xoa: ");
                TopUp* t = topupRepo.findById(id);
                if (!t) {
                    throw invalid_argument("Khong tim thay phieu nap!");
                }
                
                string confirm = InputHelper::getString("Xac nhan xoa phieu nap nay? (y/n): ");
                if (confirm == "y" || confirm == "Y") {
                    topupRepo.remove(id);
                    cout << "=> Da xoa phieu nap thanh cong!\n";
                }
            }
            else if (choice == 6) {
                double totalPayment = 0.0;
                double totalTopUp = 0.0;

                for (const auto& p : paymentRepo.getAll()) totalPayment += p.getAmount();
                for (const auto& t : topupRepo.getAll()) totalTopUp += t.getAmount();

                cout << "\n================ BAO CAO DOANH THU NHA MANG ================\n";
                cout << "1. Tong doanh thu Thanh toan Hoa don (Tra sau): " << (long long)totalPayment << " VND\n";
                cout << "2. Tong doanh thu Phieu nap tien (Tra truoc):   " << (long long)totalTopUp << " VND\n";
                cout << "------------------------------------------------------------\n";
                cout << "=> TONG DOANH THU TOAN HE THONG TELECOM:        " << (long long)(totalPayment + totalTopUp) << " VND\n";
                cout << "============================================================\n";
            }
        } catch (const exception& e) {
            cout << "=> [LOI]: " << e.what() << "\n";
        }
    }
}

// --- HAM MAIN DIEU KHIEN CHINH ---
int main() {
    Repository<Customer> customerRepo("data/customers.txt");
    customerRepo.loadFromFile();
    Repository<Subscription> subRepo("data/subscriptions.txt");
    subRepo.loadFromFile();
    Repository<GoiCuoc> goiCuocRepo("data/goicuoc.txt");    
    goiCuocRepo.loadFromFile();
    Repository<DangKy> dangKyRepo("data/dangky.txt");
    dangKyRepo.loadFromFile();

    while (true) {
        cout << "\n============================================\n";
        cout << "   HE THONG QUAN LY CUOC & DICH VU VIEN THONG\n";
        cout << "============================================\n";
        cout << "1. Quan ly Khach hang\n";
        cout << "2. Quan ly Thue bao / SIM\n";
        cout << "3. Quan ly Goi cuoc\n";
        cout << "4. Quan ly Dang ky goi cuoc\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "============================================\n";
        int mainChoice = InputHelper::getInt("Nhap lua chon: ", 0, 4);

        if (mainChoice == 0) break;
        if (mainChoice == 1) menuCustomer(customerRepo, subRepo);
        else if (mainChoice == 2) menuSubscription(subRepo, customerRepo);
        else if (mainChoice == 3) menuQuanLyGoiCuoc(goiCuocRepo, dangKyRepo);
        else if (mainChoice == 4) menuQuanLyDangKy(dangKyRepo, goiCuocRepo);
    }

    Repository<Subscription> subRepo("data/subscriptions.txt");
    subRepo.loadFromFile();

    Repository<PaymentTransaction> paymentRepo("data/payments.txt");
    paymentRepo.loadFromFile();

    Repository<TopUp> topupRepo("data/topups.txt");
    topupRepo.loadFromFile();

    while (true) {
        cout << "\n============================================\n";
        cout << "   HE THONG QUAN LY CUOC & DICH VU VIEN THONG\n";
        cout << "============================================\n";
        cout << "1. Quan ly Khach hang\n";
        cout << "2. Quan ly Thue bao / SIM\n";
        cout << "3. Quan ly Giao dich thanh toan\n";
        cout << "4. Quan ly Nap tien & Thong ke doanh thu\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "============================================\n";
        int mainChoice = InputHelper::getInt("Nhap lua chon: ", 0, 4);
        if (mainChoice == 0) break;
        if (mainChoice == 1) menuCustomer(customerRepo, subRepo);
        else if (mainChoice == 2) menuSubscription(subRepo, customerRepo);
        else if (mainChoice == 3) menuPayment(paymentRepo);
        else if (mainChoice == 4) menuTopUp(topupRepo, paymentRepo);
    }
    cout << "\nXin cam on da su dung chuong trinh!\n";
    return 0;
}
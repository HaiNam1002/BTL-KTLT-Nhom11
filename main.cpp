#include <iostream>
#include <string>
#include <iomanip>
#include "C:\\Users\\My Laptop\\Desktop\\BTL-KTLT-Nhom11\\include\\BillingRecord.h"
#include "C:\\Users\\My Laptop\\Desktop\\BTL-KTLT-Nhom11\\include\\BillingHistory.h"
#include "C:\\Users\\My Laptop\\Desktop\\BTL-KTLT-Nhom11\\include\\BillingManager.h"

using namespace std;

// Header hiển thị danh sách Bản ghi cước
void printRecordHeader() {
    cout << "---------------------------------------------------------------------------------------\n";
    cout << "| " << left << setw(12) << "Ma giao dich" 
         << "| " << setw(13) << "So thue bao" 
         << "| " << setw(15) << "Loai dich vu" 
         << "| " << setw(20) << "Thoi gian" 
         << "| " << setw(10) << "Dung luong" 
         << " | " << setw(12) << "Thanh tien" << " |\n";
    cout << "---------------------------------------------------------------------------------------\n";
}

// Header hiển thị danh sách Lịch sử cước
void printHistoryHeader() {
    cout << "----------------------------------------------------------------------------------\n";
    cout << "| " << left << setw(12) << "Ma lich su" 
         << "| " << setw(13) << "So thue bao" 
         << "| " << setw(10) << "Ky cuoc" 
         << "| " << setw(15) << "Tong tien" 
         << "| " << setw(18) << "Trang thai TT" 
         << "| " << setw(13) << "Ngay cap nhat" << " |\n";
    cout << "----------------------------------------------------------------------------------\n";
}

// ------------------- MODULE BẢN GHI CƯỚC (CRUD) -------------------
void menuBillingRecord(DataManager<BillingRecord>& recordManager) {
    int choice;
    do {
        cout << "\n================ QUAN LY BAN GHI CUOC ================\n";
        cout << "1. Xem danh sach ban ghi cuoc\n";
        cout << "2. Them ban ghi cuoc moi\n";
        cout << "3. Cap nhat ban ghi cuoc\n";
        cout << "4. Xoa ban ghi cuoc\n";
        cout << "5. Tim kiem ban ghi theo Ma GD\n";
        cout << "0. Quay lai Menu chinh\n";
        cout << "Chon chuc nang: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            cout << "\n--- DANH SACH BAN GHI CUOC ---\n";
            printRecordHeader();
            recordManager.displayAll();
            break;
        }
        case 2: {
            string id, phone, service, time;
            double usage, amount;
            cout << "\n--- THEM BAN GHI CUOC MOI ---\n";
            cout << "Nhap Ma giao dich: "; getline(cin, id);
            cout << "Nhap So thue bao: "; getline(cin, phone);
            cout << "Nhap Loai dich vu (Cuoc goi/SMS/Data): "; getline(cin, service);
            cout << "Nhap Thoi gian (YYYY-MM-DD HH:MM): "; getline(cin, time);
            cout << "Nhap Dung luong dung (MB/phut/tin): "; cin >> usage;
            cout << "Nhap Thanh tien (VND): "; cin >> amount;

            BillingRecord record(id, phone, service, time, usage, amount);
            if (recordManager.add(record)) {
                cout << "=> Them ban ghi cuoc thanh cong va da luu file!\n";
            }
            break;
        }
        case 3: {
            string id;
            cout << "\nNhap Ma giao dich can cap nhat: "; getline(cin, id);
            BillingRecord* oldRecord = recordManager.findById(id);
            if (!oldRecord) {
                cout << "Loi: Khong tim thay ban ghi voi ID da cho!\n";
                break;
            }

            string newService, newTime;
            double newUsage, newAmount;
            cout << "Nhap Loai dich vu moi: "; getline(cin, newService);
            cout << "Nhap Thoi gian moi: "; getline(cin, newTime);
            cout << "Nhap Dung luong moi: "; cin >> newUsage;
            cout << "Nhap Thanh tien moi: "; cin >> newAmount;

            BillingRecord updatedRecord(id, oldRecord->getPhoneNumber(), newService, newTime, newUsage, newAmount);
            if (recordManager.update(id, updatedRecord)) {
                cout << "=> Cap nhat thanh cong!\n";
            }
            break;
        }
        case 4: {
            string id;
            cout << "\nNhap Ma giao dich can xoa: "; getline(cin, id);
            if (recordManager.remove(id)) {
                cout << "=> Xoa ban ghi thanh cong!\n";
            } else {
                cout << "Loi: Khong tim thay ban ghi de xoa!\n";
            }
            break;
        }
        case 5: {
            string id;
            cout << "\nNhap Ma giao dich can tim: "; getline(cin, id);
            BillingRecord* rec = recordManager.findById(id);
            if (rec) {
                printRecordHeader();
                rec->display();
            } else {
                cout << "Khong tim thấy ban ghi!\n";
            }
            break;
        }
        }
    } while (choice != 0);
}

// ------------------- MODULE LỊCH SỬ TIÊU DÙNG (CRUD) -------------------
void menuBillingHistory(DataManager<BillingHistory>& historyManager) {
    int choice;
    do {
        cout << "\n============ QUAN LY LICH SU TIEU DUNG ============\n";
        cout << "1. Xem danh sach lich su tieu dung\n";
        cout << "2. Them lich su tieu dung moi\n";
        cout << "3. Cap nhat trang thai thanh toan / so tien\n";
        cout << "4. Xoa lich su tieu dung\n";
        cout << "5. Tim kiem lich su theo Ma Lich Su\n";
        cout << "0. Quay lai Menu chinh\n";
        cout << "Chon chuc nang: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            cout << "\n--- DANH SACH LICH SU TIEU DUNG ---\n";
            printHistoryHeader();
            historyManager.displayAll();
            break;
        }
        case 2: {
            string id, phone, cycle, status, date;
            double amount;
            cout << "\n--- THEM LICH SU TIEU DUNG ---\n";
            cout << "Nhap Ma lich su: "; getline(cin, id);
            cout << "Nhap So thue bao: "; getline(cin, phone);
            cout << "Nhap Ky cuoc (VD: 03/2026): "; getline(cin, cycle);
            cout << "Nhap Tong tien (VND): "; cin >> amount; cin.ignore();
            cout << "Nhap Trang thai TT (Da thanh toan/Chua thanh toan): "; getline(cin, status);
            cout << "Nhap Ngay cap nhat (YYYY-MM-DD): "; getline(cin, date);

            BillingHistory history(id, phone, cycle, amount, status, date);
            if (historyManager.add(history)) {
                cout << "=> Them lich su tieu dung thanh cong va da luu file!\n";
            }
            break;
        }
        case 3: {
            string id;
            cout << "\nNhap Ma lich su can cap nhat: "; getline(cin, id);
            BillingHistory* oldHist = historyManager.findById(id);
            if (!oldHist) {
                cout << "Loi: Khong tim thay lich su voi ID da cho!\n";
                break;
            }

            double newAmount;
            string newStatus, newDate;
            cout << "Nhap Tong tien moi: "; cin >> newAmount; cin.ignore();
            cout << "Nhap Trang thai TT moi: "; getline(cin, newStatus);
            cout << "Nhap Ngay cap nhat moi: "; getline(cin, newDate);

            BillingHistory updatedHistory(id, oldHist->getPhoneNumber(), oldHist->getBillingCycle(), newAmount, newStatus, newDate);
            if (historyManager.update(id, updatedHistory)) {
                cout << "=> Cap nhat thanh cong!\n";
            }
            break;
        }
        case 4: {
            string id;
            cout << "\nNhap Ma lich su can xoa: "; getline(cin, id);
            if (historyManager.remove(id)) {
                cout << "=> Xoa lich su thanh cong!\n";
            } else {
                cout << "Loi: Khong tim thay ma lich su de xoa!\n";
            }
            break;
        }
        case 5: {
            string id;
            cout << "\nNhap Ma lich su can tim: "; getline(cin, id);
            BillingHistory* hist = historyManager.findById(id);
            if (hist) {
                printHistoryHeader();
                hist->display();
            } else {
                cout << "Khong tim thay lich su tiêu dung!\n";
            }
            break;
        }
        }
    } while (choice != 0);
}

// ------------------- MAIN MENU -------------------
int main() {
    DataManager<BillingRecord> recordManager("C:\\Users\\My Laptop\\Desktop\\BTL-KTLT-Nhom11\\data\\billing_records.txt");
    DataManager<BillingHistory> historyManager("C:\\Users\\My Laptop\\Desktop\\BTL-KTLT-Nhom11\\data\\billing_histories.txt");

    int mainChoice;
    do {
        cout << "\n===================================================\n";
        cout << "   HE THONG QUAN LY CUOC & TIEU DUNG VIEN THONG   \n";
        cout << "===================================================\n";
        cout << "1. Quan ly Ban ghi cuoc (Billing Records)\n";
        cout << "2. Quan ly Lich su tieu dung (Billing History)\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "===================================================\n";
        cout << "Chon chuc nang: ";
        cin >> mainChoice;

        switch (mainChoice) {
        case 1:
            menuBillingRecord(recordManager);
            break;
        case 2:
            menuBillingHistory(historyManager);
            break;
        case 0:
            cout << "Cam on ban da su dung chuong trinh!\n";
            break;
        default:
            cout << "Lua chon khong hop le, vui long chon lai.\n";
        }
        
    } while (mainChoice != 0);

    return 0;
}
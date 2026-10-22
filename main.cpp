// ==================== 9. QUẢN LÝ BẢN GHI CƯỚC (CDR) ====================
inline void menuBillingRecord(Repository<BillingRecord>& repo) {
    while (true) {
        cout << "\n================ QUAN LY BAN GHI CUOC ================\n";
        cout << "1. Xem danh sach ban ghi cuoc\n";
        cout << "2. Them ban ghi cuoc moi\n";
        cout << "3. Cap nhat thong tin ban ghi cuoc\n";
        cout << "4. Xoa ban ghi cuoc\n";
        cout << "5. Tim kiem ban ghi theo Ma GD\n";
        cout << "0. Quay lai\n";
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
                // Lưu ý: Nếu muốn sửa thêm Usage và Timestamp, bạn cần bổ sung thêm setUsage() và setTimestamp() vào file BillingRecord.h nhé!

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
inline void menuBillingHistory(Repository<BillingHistory>& repo) {
    while (true) {
        cout << "\n============ QUAN LY LICH SU TIEU DUNG ============\n";
        cout << "1. Xem danh sach lich su tieu dung\n";
        cout << "2. Them lich su tieu dung moi\n";
        cout << "3. Cap nhat trang thai thanh toan / so tien\n";
        cout << "4. Xoa lich su tieu dung\n";
        cout << "5. Tim kiem lich su theo Ma Lich Su\n";
        cout << "0. Quay lai\n";
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

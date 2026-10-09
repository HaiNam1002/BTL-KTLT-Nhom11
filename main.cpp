#include <iostream>
#include <iomanip>
#include "include/Repository.h"
#include "include/Customer.h"
#include "include/InputHelper.h"

void printHeader() {
    std::cout << "+---------+-----------------------+----------------+---------------------------+\n";
    std::cout << "| Ma KH   | Ho va Ten             | CCCD           | Dia Chi                   |\n";
    std::cout << "+---------+-----------------------+----------------+---------------------------+\n";
}

void printFooter() {
    std::cout << "+---------+-----------------------+----------------+---------------------------+\n";
}

void menuCustomer(Repository<Customer>& repo) {
    while (true) {
        std::cout << "\n========== QUAN LY KHACH HANG ==========\n";
        std::cout << "1. Xem danh sach khach hang\n";
        std::cout << "2. Them khach hang moi\n";
        std::cout << "3. Tim kiem khach hang theo Ma\n";
        std::cout << "4. Cap nhat thong tin khach hang\n";
        std::cout << "5. Xoa khach hang\n";
        std::cout << "0. Quay lai / Thoat\n";
        std::cout << "========================================\n";
        int choice = InputHelper::getInt("Nhap lua chon: ", 0, 5);

        if (choice == 0) break;

        if (choice == 1) {
            std::cout << "\n--- DANH SACH KHACH HANG ---\n";
            printHeader();
            for (const auto& c : repo.getAll()) {
                c.display();
            }
            printFooter();
            std::cout << "Tong so: " << repo.getAll().size() << " khach hang.\n";
        }
        else if (choice == 2) {
            std::cout << "\n--- THEM KHACH HANG MOI ---\n";
            std::string id = InputHelper::getString("Nhap ma KH (vi du KH011): ");
            if (repo.findById(id) != nullptr) {
                std::cout << "[Loi] Ma khach hang da ton tai tren he thong!\n";
                continue;
            }
            std::string name = InputHelper::getString("Nhap ho va ten: ");
            std::string idCard = InputHelper::getString("Nhap so CCCD: ");
            std::string addr = InputHelper::getString("Nhap dia chi: ");

            Customer newC(id, name, idCard, addr);
            if (repo.add(newC)) {
                std::cout << "=> Them thanh cong va da luu vao file!\n";
            }
        }
        else if (choice == 3) {
            std::string id = InputHelper::getString("Nhap ma KH can tim: ");
            Customer* c = repo.findById(id);
            if (c) {
                std::cout << "\nThong tin tim thay:\n";
                printHeader();
                c->display();
                printFooter();
            } else {
                std::cout << "[Thong bao] Khong tim thay ma KH nay!\n";
            }
        }
        else if (choice == 4) {
            std::string id = InputHelper::getString("Nhap ma KH can sua: ");
            Customer* c = repo.findById(id);
            if (!c) {
                std::cout << "[Loi] Khong tim thay ma KH nay!\n";
                continue;
            }
            std::cout << "Thong tin hien tai: " << c->getFullName() << " - " << c->getAddress() << "\n";
            std::string newName = InputHelper::getString("Nhap ten moi (nhap giu nguyen thi go lai ten): ");
            std::string newAddr = InputHelper::getString("Nhap dia chi moi: ");
            c->setFullName(newName);
            c->setAddress(newAddr);
            repo.update(*c);
            std::cout << "=> Cap nhat thanh cong va da dong bo vao file!\n";
        }
        else if (choice == 5) {
            std::string id = InputHelper::getString("Nhap ma KH can xoa: ");
            Customer* c = repo.findById(id);
            if (!c) {
                std::cout << "[Loi] Khong tim thay ma KH de xoa!\n";
                continue;
            }
            std::string confirm = InputHelper::getString("Ban co chac chan muon xoa? (y/n): ");
            if (confirm == "y" || confirm == "Y") {
                repo.remove(id);
                std::cout << "=> Da xoa thanh cong va cap nhat file!\n";
            } else {
                std::cout << "=> Da huy thao tac xoa.\n";
            }
        }
    }
}

int main() {
    Repository<Customer> customerRepo("data/customers.txt");
    customerRepo.loadFromFile();

    menuCustomer(customerRepo);

    std::cout << "\nCam on da su dung chuong trinh!\n";
    return 0;
}
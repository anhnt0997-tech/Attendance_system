#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <locale.h> // Thư viện hỗ trợ Unicode

using namespace std;

struct Product {
    int id;
    string name;
    string description;
    double price;
    double originalPrice;
    bool discountStatus;
    string seller;
    bool isDeleted;
};

void displayMenu(Product products[], int ids[], int count, int page, int itemsPerPage) {
    int start = (page - 1) * itemsPerPage;
    int end = (start + itemsPerPage) < count ? (start + itemsPerPage) : count;

    if (start >= count) {
        cout << "Bạn đã đến cuối danh sách sản phẩm" << endl;
        return;
    }

    cout << left << setw(15) << "ID sản phẩm"
        << setw(20) << "Tên sản phẩm"
        << setw(30) << "Mô tả"
        << setw(15) << "Giá bán"
        << setw(15) << "Giảm giá %"
        << setw(20) << "Người bán" << endl;
    cout << setfill('-') << setw(115) << "-" << setfill(' ') << endl;

    for (int i = start; i < end; i++) {
        int id = ids[i];
        cout << left << setw(15) << products[id].id
            << setw(20) << products[id].name
            << setw(30) << products[id].description
            << setw(15) << products[id].price;

        if (products[id].discountStatus) {
            double discount = ((products[id].originalPrice - products[id].price) / products[id].originalPrice) * 100;
            cout << setw(15) << (to_string((int)round(discount)) + "%");
        }
        else {
            cout << setw(15) << "";
        }

        cout << setw(20) << products[id].seller << endl;
        cout << setfill('-') << setw(115) << "-" << setfill(' ') << endl;
    }

    cout << "Trang " << page << "/" << ((count + itemsPerPage - 1) / itemsPerPage) << endl;
}

void displayCart(Product cart[], int cartSize) {
    cout << "\nGiỏ hàng:\n";
    cout << left << setw(15) << "ID sản phẩm"
        << setw(20) << "Tên sản phẩm"
        << setw(30) << "Mô tả"
        << setw(15) << "Giá bán"
        << setw(15) << "Giảm giá"
        << setw(20) << "Người bán" << endl;
    cout << setfill('-') << setw(115) << "-" << setfill(' ') << endl;

    for (int i = 0; i < cartSize; ++i) {
        cout << left << setw(15) << cart[i].id
            << setw(20) << cart[i].name
            << setw(30) << cart[i].description
            << setw(15) << cart[i].price;

        if (cart[i].discountStatus) {
            double discount = ((cart[i].originalPrice - cart[i].price) / cart[i].originalPrice) * 100;
            cout << setw(15) << (to_string((int)round(discount)) + "%");
        }
        else {
            cout << setw(15) << "";
        }

        cout << setw(20) << cart[i].seller << endl;
        cout << setfill('-') << setw(115) << "-" << setfill(' ') << endl;
    }
}

int main() {
    setlocale(LC_ALL, "en_US.UTF-8"); // Hỗ trợ Unicode
    Product products[100];
    int numProducts = 0;
    ifstream file("products.txt");

    if (!file.is_open()) {
        cout << "Không thể mở file!" << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        Product product;
        stringstream ss(line);
        string token;

        getline(ss, product.name, ',');
        getline(ss, product.description, ',');
        getline(ss, token, ',');
        product.price = stod(token);
        getline(ss, token, ',');
        product.originalPrice = stod(token);
        getline(ss, token, ',');
        product.discountStatus = stoi(token);
        getline(ss, product.seller, ',');

        product.id = numProducts;
        product.isDeleted = false;
        products[numProducts++] = product;
    }

    file.close();

    if (numProducts == 0) {
        cout << "Không có sản phẩm nào được đọc từ file!" << endl;
        return 1;
    }

    int ids[100];
    int count = 0;
    for (int i = 0; i < numProducts; i++) {
        ids[count++] = products[i].id;
    }

    int page = 1;
    int itemsPerPage = 2;
    char choice;

    while (true) {
        displayMenu(products, ids, count, page, itemsPerPage);

        cout << "\nNhập 'n' để sang trang tiếp theo, 'p' để quay lại trang trước, hoặc 'q' để thoát: ";
        cin >> choice;

        if (choice == 'n') {
            if (page * itemsPerPage < count) {
                page++;
            }
            else {
                cout << "Bạn đang ở trang cuối cùng." << endl;
            }
        }
        else if (choice == 'p') {
            if (page > 1) {
                page--;
            }
            else {
                cout << "Bạn đang ở trang đầu tiên." << endl;
            }
        }
        else if (choice == 'q') {
            break;
        }
        else {
            cout << "Lựa chọn không hợp lệ. Vui lòng thử lại." << endl;
        }
    }

    Product cart[100];
    int cartSize = 0;

    while (true) {
        cout << "\nNhập ID sản phẩm bạn muốn mua (hoặc 'q' để thoát): ";
        cin >> choice;

        if (choice == 'q') {
            break;
        }

        int productId = choice - '0'; // Chuyển đổi ký tự sang số

        if (productId >= 0 && productId < numProducts && !products[productId].isDeleted) {
            cart[cartSize++] = products[productId];
            cout << "Sản phẩm đã được thêm vào giỏ hàng." << endl;
        }
        else {
            cout << "ID sản phẩm không hợp lệ. Vui lòng thử lại." << endl;
        }
    }

    displayCart(cart, cartSize);

    return 0;
}
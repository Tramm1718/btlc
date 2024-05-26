#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Định nghĩa một cấu trúc cho mỗi món trong menu
struct MenuItem {
    string name;
    double price;
};

// Hàm để thêm một món vào menu
void addMenuItem(vector<MenuItem>& menu) {
    MenuItem item;
    cout << "Enter name of the item: ";
    cin >> item.name;
    cout << "Enter price of the item: ";
    cin >> item.price;
    menu.push_back(item);
}

// Hàm để hiển thị menu
void displayMenu(const vector<MenuItem>& menu) {
    cout << "Menu:\n";
    for (size_t i = 0; i < menu.size(); ++i) {
        cout << i + 1 << ". " << menu[i].name << " - $" << menu[i].price << endl;
    }
}

// Hàm để lưu menu vào file
void saveMenuToFile(const vector<MenuItem>& menu, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& item : menu) {
            outFile << item.name << " " << item.price << endl;
        }
        outFile.close();
    }
    else {
        cout << "Unable to open file for writing." << endl;
    }
}

// Hàm để đọc menu từ file
void loadMenuFromFile(vector<MenuItem>& menu, const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        MenuItem item;
        while (inFile >> item.name >> item.price) {
            menu.push_back(item);
        }
        inFile.close();
    }
    else {
        cout << "Unable to open file for reading. Starting with an empty menu." << endl;
    }
}

// Hàm để sửa một món trong menu
void editMenuItem(vector<MenuItem>& menu) {
    displayMenu(menu);
    int index;
    cout << "Enter index of the item to edit: ";
    cin >> index;
    if (index >= 1 && index <= menu.size()) {
        cout << "Enter new name of the item: ";
        cin >> menu[index - 1].name;
        cout << "Enter new price of the item: ";
        cin >> menu[index - 1].price;
    }
    else {
        cout << "Invalid index." << endl;
    }
}

// Hàm để xóa một món trong menu
void deleteMenuItem(vector<MenuItem>& menu) {
    displayMenu(menu);
    int index;
    cout << "Enter index of the item to delete: ";
    cin >> index;
    if (index >= 1 && index <= menu.size()) {
        menu.erase(menu.begin() + index - 1);
        cout << "Item deleted successfully." << endl;
    }
    else {
        cout << "Invalid index." << endl;
    }
}

// Hàm để tính tổng tiền dựa trên số lượng món được chọn
double calculateTotalBill(const vector<MenuItem>& menu) {
    double total = 0.0;
    int quantity;
    for (const auto& item : menu) {
        cout << "Enter quantity of " << item.name << ": ";
        cin >> quantity;
        total += item.price * quantity;
    }
    return total;
}

int main() {
    vector<MenuItem> menu;
    string filename = "menu.txt"; // Tên tập tin để lưu trữ menu

    // Đọc menu từ file khi bắt đầu chương trình
    loadMenuFromFile(menu, filename);

    int choice;
    do {
        cout << "\n1. Add item\n";
        cout << "2. Edit item\n";
        cout << "3. Delete item\n";
        cout << "4. Display menu\n";
        cout << "5. Calculate total bill\n";
        cout << "6. Save menu to file\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            char addMore;
            do {
                addMenuItem(menu);
                cout << "Do you want to add more items? (y/n): ";
                cin >> addMore;
            } while (addMore == 'y' || addMore == 'Y');
            break;
        case 2:
            editMenuItem(menu);
            break;
        case 3:
            deleteMenuItem(menu);
            break;
        case 4:
            displayMenu(menu);
            break;
        case 5:
            cout << "Total bill: $" << calculateTotalBill(menu) << endl;
            break;
        case 6:
            saveMenuToFile(menu, filename);
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}

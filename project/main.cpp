#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Product {
    string name;
    int quantity;
    double price;
};

// ================= FILE =================

void loadData(vector<Product>& products) {
    ifstream file("products.txt");

    if (!file) {
        cout << "Failas nerastas. Bus sukurtas naujas.\n";
        return;
    }

    while (!file.eof()) {
        Product p;
        string line;

        getline(file, line);
        if (line.empty()) continue;

        int pos1 = line.find(';');
        int pos2 = line.find(';', pos1 + 1);

        p.name = line.substr(0, pos1);
        p.quantity = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        p.price = stod(line.substr(pos2 + 1));

        products.push_back(p);
    }

    file.close();
}

void saveData(const vector<Product>& products) {
    ofstream file("products.txt");

    for (const auto& p : products) {
        file << p.name << ";"
             << p.quantity << ";"
             << p.price << endl;
    }

    file.close();
}

// ================= CRUD =================

void addProduct(vector<Product>& products) {
    Product p;

    cout << "Iveskite pavadinima: ";
    cin >> p.name;

    cout << "Iveskite kieki: ";
    cin >> p.quantity;

    cout << "Iveskite kaina: ";
    cin >> p.price;

    products.push_back(p);
    cout << "Preke prideta!\n";
}

void showProducts(const vector<Product>& products) {
    cout << "\nPrekiu sarasas:\n";

    for (int i = 0; i < products.size(); i++) {
        cout << i + 1 << ") "
             << products[i].name << " | "
             << products[i].quantity << " vnt | "
             << products[i].price << " Eur\n";
    }
}

void updateProduct(vector<Product>& products) {
    showProducts(products);

    int index;
    cout << "Pasirinkite preke: ";
    cin >> index;

    if (index < 1 || index > products.size()) {
        cout << "Klaida!\n";
        return;
    }

    Product& p = products[index - 1];

    cout << "Naujas pavadinimas: ";
    cin >> p.name;

    cout << "Naujas kiekis: ";
    cin >> p.quantity;

    cout << "Nauja kaina: ";
    cin >> p.price;

    cout << "Atnaujinta!\n";
}

void deleteProduct(vector<Product>& products) {
    showProducts(products);

    int index;
    cout << "Kuri preke istrinti: ";
    cin >> index;

    if (index < 1 || index > products.size()) {
        cout << "Klaida!\n";
        return;
    }

    products.erase(products.begin() + index - 1);
    cout << "Istrinta!\n";
}

// ================= EXTRA =================

void sortProducts(vector<Product>& products) {
    int choice;
    cout << "\nPasirinkite rikiavima:\n";
    cout << "1. Pagal pavadinima (A-Z)\n";
    cout << "2. Pagal kaina (didejimo tvarka)\n";
    cout << "3. Pagal kaina (mazejimo tvarka)\n";
    cout << "4. Pagal kieki (didejimo tvarka)\n";
    cout << "5. Pagal kieki (mazejimo tvarka)\n";
    cout << "Pasirinkimas: ";
    cin >> choice;

    switch (choice) {
        case 1:
            sort(products.begin(), products.end(), [](Product a, Product b) {
                return a.name < b.name;
            });
            break;

        case 2:
            sort(products.begin(), products.end(), [](Product a, Product b) {
                return a.price < b.price;
            });
            break;

        case 3:
            sort(products.begin(), products.end(), [](Product a, Product b) {
                return a.price > b.price;
            });
            break;

        case 4:
            sort(products.begin(), products.end(), [](Product a, Product b) {
                return a.quantity < b.quantity;
            });
            break;

        case 5:
            sort(products.begin(), products.end(), [](Product a, Product b) {
                return a.quantity > b.quantity;
            });
            break;

        default:
            cout << "Neteisingas pasirinkimas!\n";
            return;
    }

    cout << "Rikiavimas atliktas!\n";
}

void generateReport(const vector<Product>& products) {
    ofstream file("report.txt");

    double total = 0;

    cout << "\n===== VISU PREKIU ATASKAITA =====\n";
    file << "===== VISU PREKIU ATASKAITA =====\n";

    for (size_t i = 0; i < products.size(); i++) {
        double value = products[i].quantity * products[i].price;
        total += value;

        cout << i + 1 << ") "
             << products[i].name << " | "
             << "Kiekis: " << products[i].quantity << " | "
             << "Kaina: " << products[i].price << " | "
             << "Verte: " << value << " Eur\n";

        file << i + 1 << ") "
             << products[i].name << " | "
             << "Kiekis: " << products[i].quantity << " | "
             << "Kaina: " << products[i].price << " | "
             << "Verte: " << value << " Eur\n";
    }

    cout << "\nBendra visu prekiu verte: "
         << total << " Eur\n";

    file << "\nBendra visu prekiu verte: "
         << total << " Eur\n";

    file.close();

    cout << "Ataskaita issaugota i report.txt\n";
}

// ================= MENU =================

void menu() {
    cout << "\n===== MENU =====\n";
    cout << "1. Rodyti prekes\n";
    cout << "2. Prideti preke\n";
    cout << "3. Redaguoti preke\n";
    cout << "4. Istrinti preke\n";
    cout << "5. Rikiuoti prekes\n";
    cout << "6. Ataskaita\n";
    cout << "0. Iseiti\n";
}

// ================= MAIN =================

int main() {
    vector<Product> products;

    loadData(products);

    int choice;

    do {
        menu();
        cout << "Pasirinkimas: ";
        cin >> choice;

        switch (choice) {
            case 1: showProducts(products); break;
            case 2: addProduct(products); break;
            case 3: updateProduct(products); break;
            case 4: deleteProduct(products); break;
            case 5: sortProducts(products); break;
            case 6: generateReport(products); break;
        }

    } while (choice != 0);

    saveData(products);

    return 0;
}

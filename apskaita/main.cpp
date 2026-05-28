#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

struct menuItemType {
    string menuItem;
    double menuPrice;
};
void getData(vector<menuItemType>& menuList) {
    ifstream inFile("menu.txt");

    if (!inFile) {
        cout << "Klaida atidarant faila menu.txt" << endl;
        return;
    }

    string line;

    getline(inFile, line);

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        menuItemType item;

        int pos = line.size() - 1;

        while (pos >= 0 && (isdigit(line[pos]) || line[pos] == '.')) {
            pos--;
        }

        item.menuItem = line.substr(0, pos + 1);
        item.menuPrice = stod(line.substr(pos + 1));

        menuList.push_back(item);
    }

    inFile.close();
}

void showMenu(const vector<menuItemType>& menuList) {
    cout << "Sveiki atvyke i restorana!\n\n";
    cout << "Meniu:\n";

    for (size_t i = 0; i < menuList.size(); i++) {
        cout << i + 1 << ") "
             << menuList[i].menuItem << " - "
             << fixed << setprecision(2)
             << menuList[i].menuPrice << " Eur\n";
    }

    cout << "\nIveskite patiekalo numeri ir kieki.\n";
    cout << "Baigdami iveskite 0.\n\n";
}

void printCheck(const vector<menuItemType>& menuList,
                const vector<int>& quantityList) {

    ofstream outFile("receipt.txt");

    double subtotal = 0.0;

    cout << "\nJusu kvitas:\n\n";
    outFile << "Jusu kvitas:\n\n";

    for (size_t i = 0; i < menuList.size(); i++) {
        if (quantityList[i] > 0) {
            double itemTotal = quantityList[i] * menuList[i].menuPrice;
            subtotal += itemTotal;

            cout << quantityList[i] << " "
                 << menuList[i].menuItem << "   "
                 << fixed << setprecision(2)
                 << itemTotal << " Eur\n";

            outFile << quantityList[i] << " "
                    << menuList[i].menuItem << "   "
                    << fixed << setprecision(2)
                    << itemTotal << " Eur\n";
        }
    }

    double tax = subtotal * 0.21;
    double total = subtotal + tax;

    cout << "\nMokesciai (21%)   "
         << fixed << setprecision(2)
         << tax << " Eur\n";

    cout << "Galutine suma           "
         << total << " Eur\n";

    outFile << "\nMokesciai (21%)   "
            << tax << " Eur\n";

    outFile << "Galutine suma           "
            << total << " Eur\n";

    outFile.close();
}

int main() {
    vector<menuItemType> menuList;
    getData(menuList);

    vector<int> quantityList(menuList.size(), 0);

    showMenu(menuList);

    int choice;

    while (true) {
        cout << "Pasirinkite patiekala (0 - iseiti): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Neteisinga ivestis! Bandykite dar karta.\n";
            continue;
        }

        if (choice == 0)
            break;

        if (choice < 1 || choice > menuList.size()) {
            cout << "Neteisingas pasirinkimas!\n";
            continue;
        }

        int qty;
        cout << "Kiekis: ";
        cin >> qty;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Neteisingas kiekis!\n";
            continue;
        }

        if (qty > 0)
            quantityList[choice - 1] += qty;
    }

    printCheck(menuList, quantityList);
    return 0;
}
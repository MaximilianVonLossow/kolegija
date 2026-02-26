#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double GBP_Bendras = 0.8729, GBP_Pirkti = 0.8600, GBP_Parduoti = 0.9220;
    double USD_Bendras = 1.1793, USD_Pirkti = 1.1460, USD_Parduoti = 1.2340;
    double INR_Bendras = 104.6918, INR_Pirkti = 101.3862, INR_Parduoti = 107.8546;

    int valiuta, operacija;
    double kiekis, rezultatas;

    cout << "Galimos valiutu operacijos su EUR :\n"
         << "1 - GBR:  Pirkti uz 0.8600, parduoti uz 0.9220\n"
         << "2 - USD:  Pirkti uz 1.1460, parduoti uz 1.2340\n"
         << "3 - INR:  Pirkti uz 101.3862, parduoti uz 107.8546\n"
         << "Pasirinkite valiuta: ";
    cin >> valiuta;

    cout << "\nKokia operacija?:\n"
         << "1 - valiutos kurso paliginimas \n"
         << "2 - pirkti valiuta \n"
         << "3 - parduoti valiuta \n"
         << "jus renkates";
    cin >> operacija;
    switch (valiuta) {
        case 1:
            if (operacija == 1) {
                double kursas = round(GBP_Bendras * 100) / 100;
                cout << "1 EUR = " << kursas << " GBR\n";
            }
            else if (operacija == 2) {
                cout << "EUR kiekis: ";
                cin >> kiekis;
                rezultatas = kiekis * GBP_Pirkti;
                rezultatas = round(rezultatas * 100) / 100;
                cout << "jus gausite: " << rezultatas << " GBR\n";
            }
            else if (operacija == 3) {
                cout << "GBR kiekis: ";
                cin >> kiekis;
                rezultatas = kiekis / GBP_Parduoti;
                rezultatas = round(rezultatas * 100) / 100;
                cout << "jus gausite: " << rezultatas << " EUR\n";
            }
            break;

        case 2:
            if (operacija == 1) {
                double kursas = round(USD_Bendras * 100) / 100;
                cout << "1 EUR = " << kursas << " USD\n";
            }
            else if (operacija == 2) {
                cout << "EUR kiekis: ";
                cin >> kiekis;
                rezultatas = kiekis * USD_Pirkti;
                rezultatas = round(rezultatas * 100) / 100;
                cout << "jus gausite: " << rezultatas << " USD\n";
            }
            else if (operacija == 3) {
                cout << "USD kiekis: ";
                cin >> kiekis;
                rezultatas = kiekis / USD_Parduoti;
                rezultatas = round(rezultatas * 100) / 100;
                cout << "jus gausite: " << rezultatas << " EUR\n";
            }
            break;

        case 3:
            if (operacija == 1) {
                double kursas = round(INR_Bendras * 100) / 100;
                cout << "1 EUR = " << kursas << " INR\n";
            }
            else if (operacija == 2) {
                cout << "EUR kiekis: ";
                cin >> kiekis;
                rezultatas = kiekis * INR_Pirkti;
                rezultatas = round(rezultatas * 100) / 100;
                cout << "jus gausite: " << rezultatas << " INR\n";
            }
            else if (operacija == 3) {
                cout << "INR kiekis: ";
                cin >> kiekis;
                rezultatas = kiekis / INR_Parduoti;
                rezultatas = round(rezultatas * 100) / 100;
                cout << "jus gausite: " << rezultatas << " EUR\n";
            }
            break;

        default:
            cout << "Tokios valiutos nera:\n";
    }

        return 0;
}
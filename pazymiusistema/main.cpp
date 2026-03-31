#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int max_mokiniu = 100;
const int max_pazymiai = 10;

void rodyti_meniu();
void prideti_mokini(string mokiniu_vardai[], int mokiniu_pazymiai[][max_pazymiai], int&mokiniu_skaicius);
void perziureti_visus_mokinius(string mokiniu_vardai[], int mokiniu_pazymiai[][max_pazymiai], int mokiniu_skaicius);
void perziureti_mokinio_pazymius(string mokiniu_vardai[], int mokiniu_pazymiai[][max_pazymiai], int mokiniu_skaicius);
void atnaujinti_pazymi(string mokiniu_vardai[], int mokiniu_pazymiai[][max_pazymiai], int mokiniu_skaicius);
void pasalinti_mokini(string mokiniu_vardai[], int mokiniu_pazymiai[][max_pazymiai], int &mokiniu_skaicius);
void rodyti_mokinio_pazymius(string vardas, int pazymiai[], int pazymiu_kiekis);
bool ar_teisingas_pazymys(int pazymys);
int gauti_mokinio_indeksa(string mokinius_vardai[], int mokiniu_skaicius);

int main() {
    string mokiniu_vardai[max_mokiniu];
    int mokiniu_pazymiai[max_mokiniu][max_pazymiai];
    int mokiniu_skaicius = 0;

    for (int i = 0; i < max_mokiniu; i++) {
        for (int j = 0; j < max_pazymiai; j++) {
            mokiniu_pazymiai[i][j] = -1;
        }
    }

    int pasirinkimas;
    do {
        rodyti_meniu();
        cout << "Pasirinkite veiksma (0-5): ";
        cin >> pasirinkimas;

        switch (pasirinkimas) {
            case 1: prideti_mokini(mokiniu_vardai, mokiniu_pazymiai, mokiniu_skaicius); break;
            case 2: perziureti_visus_mokinius(mokiniu_vardai, mokiniu_pazymiai, mokiniu_skaicius); break;
            case 3: perziureti_mokinio_pazymius(mokiniu_vardai, mokiniu_pazymiai, mokiniu_skaicius); break;
            case 4: atnaujinti_pazymi(mokiniu_vardai, mokiniu_pazymiai, mokiniu_skaicius); break;
            case 5: pasalinti_mokini(mokiniu_vardai, mokiniu_pazymiai, mokiniu_skaicius); break;
            case 0: cout << "Programa baigta" << endl; break;
            default: cout << "Neteisingas pasirinkimas. Pasirinkite nuo 0 iki 5." << endl;
        }
        cout << endl;
    } while (pasirinkimas != 0);

    return 0;
}

void rodyti_meniu() {
    cout << "\n MOKINIU PAZYMIU SISTEMA " << endl;
    cout << "1. Prideti mokini" << endl;
    cout << "2. Perziureti visus mokinius" << endl;
    cout << "3. Perziureti konkretaus mokinio pazymius" << endl;
    cout << "4. Atnaujinti mokinio pazymi" << endl;
    cout << "5. Pasalinti mokini" << endl;
    cout << "0. Iseiti" << endl;
}

void prideti_mokini(string mokiniu_vardai[], int mokiniu_pazymiai[][max_pazymiai], int &mokiniu_skaicius) {
    if (mokiniu_skaicius >= max_mokiniu) {
        cout << "klaida: pasiektas maksimalus mokiniu skaicius (" << max_mokiniu << ")" << endl;
        return;
    }
    string vardas;
    cout << "Iveskite mokinio varda: ";
    cin.ignore();
    getline(cin, vardas);

    // patikrinimas ar yra toks mokinys
    for (int i = 0; i < mokiniu_skaicius; i++) {
        if (mokiniu_vardai[i] == vardas) {
            cout << "Mokinys tokiu vardu jau egzistuoja!" << endl;
            return;
        }
    }
    mokiniu_vardai[mokiniu_skaicius] = vardas;

    int pazymiu_kiekis;
    cout << "Kiek pazymiu norite prideti (1-" << max_pazymiai << "): ";
    cin >> pazymiu_kiekis;

    if (pazymiu_kiekis < 1 || pazymiu_kiekis > max_pazymiai) {
        cout << "Neteisingas pazymiu kiekis. Nustatyta 0." << endl;1
        pazymiu_kiekis = 0;
    }

    // Išvalyti eilutę
    for (int i = 0; i < max_pazymiai; i++) {
        mokiniu_pazymiai[mokiniu_skaicius][i] = -1;
    }

    // Pazymių ivedimas
    for (int i = 0; i < pazymiu_kiekis; i++) {
        int pazymys;
        do {
            cout << "Iveskite pazymi #" << (i + 1) << " (2-10): ";
            cin >> pazymys;
            if (!ar_teisingas_pazymys(pazymys)) {
                cout << "Klaida: pazymys turi buti nuo 2 iki 10!" << endl;
            }
        } while (!ar_teisingas_pazymys(pazymys));

        mokiniu_pazymiai[mokiniu_skaicius][i] = pazymys;
    }

    mokiniu_skaicius++;
    cout << "Mokinys \"" << vardas << "\" sekmingai pridetas!" << endl;
}

void perziureti_visus_mokinius(string mokiniu_vardai[], int mokiniu_pazymiai[][max_pazymiai], int mokiniu_skaicius) {
    if (mokiniu_skaicius == 0) {
        cout << "Nera mokiniu sarase!" << endl;
        return;
    }

    cout << "\n MOKINIU SARASAS" << endl;
    cout << left << setw(25) << "mokinio vardas" << "pazymiai" << endl;

    for (int i = 0; i < mokiniu_skaicius; i++) {
        cout << left << setw(25) << mokiniu_vardai[i];

        bool turi_pazymiu = false;
        for (int j = 0; j < max_pazymiai && mokiniu_pazymiai[i][j] != -1; j++) {
            cout << mokiniu_pazymiai[i][j] << " ";
            turi_pazymiu = true;
        }
            if (!turi_pazymiu) {
            cout << "nera pazymiu";
        }
        cout << endl;
    }
    cout << "___________________________________" << endl;
}

void perziureti_mokinio_pazymius(string mokiniu_vardai[], int mokiniu_pazymiai[][max_pazymiai], int mokiniu_skaicius) {
    if (mokiniu_skaicius == 0) {
        cout << "nera mokiniu sarase!" << endl;
        return;
    }

    int indeksas = gauti_mokinio_indeksa(mokiniu_vardai, mokiniu_skaicius);
    if (indeksas == -1) return;

    rodyti_mokinio_pazymius(mokiniu_vardai[indeksas], mokiniu_pazymiai[indeksas], max_pazymiai);
}

void atnaujinti_pazymi(string mokiniu_vardai[], int mokiniu_pazymiai[][max_pazymiai], int mokiniu_skaicius) {
    if (mokiniu_skaicius == 0) {
        cout << "nera mokiniu sarase!" << endl;
        return;
    }

    int indeksas = gauti_mokinio_indeksa(mokiniu_vardai, mokiniu_skaicius);
    if (indeksas == -1) return;

    cout << "/nDabartiniai mokinio \"" << mokiniu_vardai[indeksas] << "\" pazimiai" << endl;
    rodyti_mokinio_pazymius(mokiniu_vardai[indeksas], mokiniu_pazymiai[indeksas], max_pazymiai);

    int pazymio_numeris;
    cout << "kuri pazymi norite atnaujinti (iveskite numerinuo 1 iki " << max_pazymiai << "): ";
    cin >> pazymio_numeris;

    if (pazymio_numeris < 1 || pazymio_numeris > max_pazymiai) {
        cout << "neteisingas pazymio numeris " << endl;
        return;
    }

    int naujas_pazymys;
    do {
        cout << "iveskite nauja pazymi (2-10): ";
        cin >> naujas_pazymys;
        if (!ar_teisingas_pazymys(naujas_pazymys)) {
            cout << "klaida: pazymys turi buti nuo 2 iki 10 " << endl;
        }
    } while (!ar_teisingas_pazymys(naujas_pazymys));

    mokiniu_pazymiai[indeksas][pazymio_numeris - 1] = naujas_pazymys;
    cout << "pazymys sekmingai atnaujintas " << endl;

    cout << "\nAtnaujinti pazymiai: " << endl;
    rodyti_mokinio_pazymius(mokiniu_vardai[indeksas], mokiniu_pazymiai[indeksas], max_pazymiai);
}

void pasalinti_mokini(string mokiniu_vardai[], int mokiniu_pazymiai[][max_pazymiai], int &mokiniu_skaicius) {
    if (mokiniu_skaicius == 0) {
        cout << "nera mokiniu pasalinimui " << endl;
        return;
    }
    int indeksas = gauti_mokinio_indeksa(mokiniu_vardai, mokiniu_skaicius);
    if (indeksas == -1) return;

    cout << "ar tikrai norite pasalinti mokini \"" << mokiniu_vardai[indeksas] << "\"? (y/n)" << endl;
    char patvirtinimas;
    cin >> patvirtinimas;

    if (patvirtinimas != 'y' && patvirtinimas != 'Y') {
        cout << "pasalinimas atsauktas " << endl;
        return;
    }

    // perkelimas likusiu mokiniu viena pozicija i kaire
    for (int i = indeksas; i < mokiniu_skaicius - 1; i++) {
        mokiniu_vardai[i] = mokiniu_vardai[i + 1];
        for (int j = 0; j < max_pazymiai; j++) {
            mokiniu_vardai[i][j] = mokiniu_vardai[i + 1][j];
        }
    }

    // isvaliti paskutini irasa
    mokiniu_vardai[mokiniu_skaicius - 1] = "";
    for (int j = 0; j < max_pazymiai; j++) {
        mokiniu_pazymiai[mokiniu_skaicius - 1][j] = -1;
    }

    mokiniu_skaicius--;
    cout << "mokinys sekmingai pasalintas " << endl;
}

void rodyti_mokinio_pazymius(string vardas, int pazymiai[], int pazymiu_kiekis) {
    cout << "mokinys: " << vardas << endl;
    cout << "pazymiai: ";

    bool turi_pazymiu = false;
    for (int i = 0; i < pazymiu_kiekis && pazymiai[i] != -1; i++) {
        cout << pazymiai[i] << " ";
        turi_pazymiu = true;
    }

    if (!turi_pazymiu) {
        cout << "nera pazymiu ";
    } else {
        double suma = 0;
        int sk = 0;
        for (int i = 0; i < pazymiu_kiekis && pazymiai[i] != -1; i++) {
            suma += pazymiai[i];
            sk++;
        }
        cout << "\nVidurkis: " << fixed << setprecision(2) << suma / sk;
    }
    cout << endl;
}

bool ar_teisingas_pazymys(int pazymys) {
    return pazymys >= 2 && pazymys <= 10;
}

int gauti_mokinio_indeksa(string mokiniu_vardai[], int mokiniu_skaicius) {
    string vardas;
    cout << "iveskite mokinio varda ";
    cin.ignore();
    getline(cin, vardas);

    for (int i = 0; i < mokiniu_skaicius; i++) {
        if (mokiniu_vardai[i] == vardas) {
            return i;
        }
    }

cout << "mokinys vardu \"" << vardas << "\" nerastas" << endl;
    return -1;
}
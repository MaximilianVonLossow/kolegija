#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

// ================= Skaitikliai =================
long long comparisons = 0;
long long swaps = 0;

// ================= Selection Sort =================
void selectionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            comparisons++; // atliksime palyginimą
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // keičiam elementų vietas
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
            swaps++; // apskaičiuojame permainą
        }
    }
}

// ================= Merge Sort =================

// Dviejų masyvo dalių sujungimas
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);

    int i = left;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= right) {
        comparisons++; // palyginimas

        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }

        swaps++; // apskaičiuojame poslinkį
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
        swaps++;
    }

    while (j <= right) {
        temp[k++] = arr[j++];
        swaps++;
    }

    // kopijuojame atgal
    for (int t = 0; t < temp.size(); t++) {
        arr[left + t] = temp[t];
        swaps++;
    }
}

// Rekursinis rūšiavimas
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// ================= Duomenų generavimas =================

// Atsitiktinis masyvas
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100000);

    for (int i = 0; i < size; i++)
        arr[i] = dis(gen);

    return arr;
}

// Rūšiuotas masyvas
vector<int> generateSortedArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++)
        arr[i] = i;
    return arr;
}

// Atvirkštine tvarka surūšiuotas masyvas
vector<int> generateReverseArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++)
        arr[i] = size - i;
    return arr;
}

// ================= Vieno masyvo testas =================
void testWithArray(vector<int> arr) {

    vector<int> arr1 = arr;
    vector<int> arr2 = arr;

    // ===== Selection Sort =====
    comparisons = 0;
    swaps = 0;

    auto start = chrono::high_resolution_clock::now();
    selectionSort(arr1);
    auto end = chrono::high_resolution_clock::now();

    double time1 = chrono::duration<double, milli>(end - start).count();

    cout << "Selection Sort\n";
    cout << "Time: " << time1 << " ms\n";
    cout << "Comparisons: " << comparisons << "\n";
    cout << "Swaps: " << swaps << "\n\n";

    // ===== Merge Sort =====
    comparisons = 0;
    swaps = 0;

    start = chrono::high_resolution_clock::now();
    mergeSort(arr2, 0, arr2.size() - 1);
    end = chrono::high_resolution_clock::now();

    double time2 = chrono::duration<double, milli>(end - start).count();

    cout << "Merge Sort\n";
    cout << "Time: " << time2 << " ms\n";
    cout << "Comparisons: " << comparisons << "\n";
    cout << "Moves: " << swaps << "\n\n";

    cout << "=============================\n\n";
}

// ================= Išsamus testas =================
void runTests(int size) {

    cout << "=====================================\n";
    cout << "Masyvo dydis: " << size << endl;
    cout << "=====================================\n\n";

    // 1. Atsitiktiniai duomenys
    cout << "===== ATRANDAMIEJI DUOMENYS =====\n";
    testWithArray(generateRandomArray(size));

    // 2. Jau surūšiuoti
    cout << "===== SURŪŠIUOTI DUOMENYS =====\n";
    testWithArray(generateSortedArray(size));

    // 3. Rūšiuoti atgaline tvarka
    cout << "===== ATVIRKŠTINĖ TVARKA =====\n";
    testWithArray(generateReverseArray(size));
}

// ================= main =================
int main() {

    runTests(5000);
    runTests(10000);
    runTests(50000);

    return 0;
}
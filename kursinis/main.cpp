#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

// Bendrieji skaitikliai
long long comparisons = 0;
long long swaps = 0;

// Rusiavimas pagal atranką
void selectionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            comparisons++; // atliksime palyginima
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        // elementu keitimas
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
            swaps++; // apskaiciuojame permaina
        }
    }
}

// Merge Sort

// merge (sujungimas)
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
        swaps++; // laikome tai judejimu
    }

    // likusiu elementu kopijavimas
    while (i <= mid) {
        temp[k++] = arr[i++];
        swaps++;
    }

    while (j <= right) {
        temp[k++] = arr[j++];
        swaps++;
    }

    // graziname i pradini masyva
    for (int t = 0; t < temp.size(); t++) {
        arr[left + t] = temp[t];
        swaps++;
    }
}

// rekursyvine funkcija
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Masyvo generavimas
vector<int> generateArray(int size) {
    vector<int> arr(size);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 10000);

    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }

    return arr;
}

// Testavimas
void test(int size) {
    vector<int> arr1 = generateArray(size);
    vector<int> arr2 = arr1;

    // Selection Sort
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

    // Merge Sort
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

// main
int main() {
    test(5000);
    test(10000);
    test(50000);

    return 0;
}
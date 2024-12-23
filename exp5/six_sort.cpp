#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <functional>
#include <string>

using namespace std;

// ð������
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
}

// ��������
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ѡ������
void selectionSort(vector<int>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(arr[min_idx], arr[i]);
    }
}

// �鲢����
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// ��������
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ������
void heapify(vector<int>& arr, int n, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ���Ժ���
void testSortingAlgorithms(int numElements) {
    vector<int> sortedArray(numElements);
    vector<int> reverseSortedArray(numElements);
    vector<int> randomArray(numElements);

    // ��ʼ��˳������
    for (int i = 0; i < numElements; i++) {
        sortedArray[i] = i;
        reverseSortedArray[i] = numElements - i - 1;
        randomArray[i] = rand() % 100; // �������Χ 0-99
    }

    // ����ÿ�������㷨
    // �����㷨����
    std::vector<std::string> algorithms = {
        "Bubble Sort",
        "Insertion Sort",
        "Selection Sort",
        "Merge Sort",
        "Quick Sort",
        "Heap Sort"};

    // ����������ָ��
    std::vector<std::function<void(std::vector<int>&)> > functions = {
        bubbleSort,
        insertionSort,
        selectionSort,
        [](std::vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); },
        [](std::vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); },
        heapSort};

    for (int i = 0; i < algorithms.size(); i++) {
        cout << algorithms[i] << ":\n";

        // ˳���������
        vector<int> arr = sortedArray;
        clock_t start = clock();
        functions[i](arr);
        clock_t end = clock();
        cout << "  Sorted array: " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";

        // �����������
        arr = reverseSortedArray;
        start = clock();
        functions[i](arr);
        end = clock();
        cout << "  Reverse sorted array: " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";

        // ����������
        arr = randomArray;
        start = clock();
        functions[i](arr);
        end = clock();
        cout << "  Random array: " << double(end - start) / CLOCKS_PER_SEC << " seconds\n";
    }
}

int main() {
    srand(time(0)); // �����������
    int numElements = 3000; // �������г���
    //����ʱ��
    testSortingAlgorithms(numElements);
    return 0;
}

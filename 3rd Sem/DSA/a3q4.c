#include <stdio.h>

void printArray(int arr[], int n, int pass) {
    int i;
    printf("Pass %d: ", pass);
    for (i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

void insertionSort(int arr[], int n) {
    int i, j, key;
    printf("\n--- Insertion Sort ---\n");
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
            arr[j + 1] = arr[j--];
        arr[j + 1] = key;
        printArray(arr, n, i);
    }
}

void selectionSort(int arr[], int n) {
    int i, j, min, temp;
    printf("\n--- Selection Sort ---\n");
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min]) min = j;
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
        printArray(arr, n, i + 1);
    }
}

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    printf("\n--- Bubble Sort ---\n");
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        printArray(arr, n, i + 1);
    }
}

int partition(int arr[], int low, int high, int *pass, int n) {
    int pivot = arr[high];
    int i = low - 1;
    int j, temp;
    for (j = low; j < high; j++)
        if (arr[j] <= pivot) {
            i++;
            temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    temp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = temp;
    (*pass)++;
    printArray(arr, n, *pass);
    return i + 1;
}

void quickSortRec(int arr[], int low, int high, int *pass, int n) {
    int pi;
    if (low < high) {
        pi = partition(arr, low, high, pass, n);
        quickSortRec(arr, low, pi - 1, pass, n);
        quickSortRec(arr, pi + 1, high, pass, n);
    }
}

void quickSort(int arr[], int n) {
    int pass = 0;
    printf("\n--- Quick Sort ---\n");
    quickSortRec(arr, 0, n - 1, &pass, n);
}

void merge(int arr[], int l, int m, int r, int *pass, int n) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int i, j, k;
    int L[100], R[100];  /* Using fixed size arrays for compatibility */
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    i = 0; j = 0; k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    (*pass)++;
    printArray(arr, n, *pass);
}

void mergeSortRec(int arr[], int l, int r, int *pass, int n) {
    int m;
    if (l < r) {
        m = (l + r) / 2;
        mergeSortRec(arr, l, m, pass, n);
        mergeSortRec(arr, m + 1, r, pass, n);
        merge(arr, l, m, r, pass, n);
    }
}

void mergeSort(int arr[], int n) {
    int pass = 0;
    printf("\n--- Merge Sort ---\n");
    mergeSortRec(arr, 0, n - 1, &pass, n);
}

void heapify(int arr[], int n, int i) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2, temp;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        temp = arr[i]; arr[i] = arr[largest]; arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    int i, pass = 0, temp;
    printf("\n--- Heap Sort ---\n");
    for (i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (i = n - 1; i > 0; i--) {
        temp = arr[0]; arr[0] = arr[i]; arr[i] = temp;
        heapify(arr, i, 0);
        pass++;
        printArray(arr, n, pass);
    }
}

int main() {
    int n, i;
    int arr[100], copy[100];
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (i = 0; i < n; i++) scanf("%d", &arr[i]);

    for (i = 0; i < n; i++) copy[i] = arr[i];
    insertionSort(copy, n);

    for (i = 0; i < n; i++) copy[i] = arr[i];
    selectionSort(copy, n);

    for (i = 0; i < n; i++) copy[i] = arr[i];
    bubbleSort(copy, n);

    for (i = 0; i < n; i++) copy[i] = arr[i];
    quickSort(copy, n);

    for (i = 0; i < n; i++) copy[i] = arr[i];
    mergeSort(copy, n);

    for (i = 0; i < n; i++) copy[i] = arr[i];
    heapSort(copy, n);

    return 0;
}


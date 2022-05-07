#include "sort.h"

namespace templates {
    void merge(void** ppArray, int left, int middle, int right, CompareSortType pCompareFunc) {
        int i = 0;
        int j = 0;
        int k = left;
        int length1 = middle - left;
        int length2 = right - middle;

        void** leftArray = new void*[length1];
        void** rightArray = new void*[length2];

        for (int i = 0; i < length1; i++)
            leftArray[i] = ppArray[left + i];
        for (int j = 0; j < length2; j++)
            rightArray[j] = ppArray[middle + j];

        while (i < length1 && j < length2) {
            if (pCompareFunc(leftArray[i], rightArray[j]) < 0) {
                ppArray[k] = leftArray[i];
                i++;
            } else {
                ppArray[k] = rightArray[j];
                j++;
            }
            k++;
        }

        while (i < length1) {
            ppArray[k] = leftArray[i];
            i++;
            k++;
        }

        while (j < length2) {
            ppArray[k] = rightArray[j];
            j++;
            k++;
        }

        delete[] leftArray;
        delete[] rightArray;
    }

    void sort(void** ppArray, int left, int right, CompareSortType pCompareFunc) {
        if (left + 1 >= right) {
            return;
        }
        int middle = (left + right) / 2;
        sort(ppArray, left, middle, pCompareFunc);
        sort(ppArray, middle, right, pCompareFunc);
        merge(ppArray, left, middle, right, pCompareFunc);
    }

    void mergeSort(void** ppArray, int length, CompareSortType pCompareFunc) {
        sort(ppArray, 0, length, pCompareFunc);
    }
}

#include "sort.h"


namespace templates {
    void merge(void** ppArray, int left, int middle, int right, CompareSortType pCompareFunc, void** array) {
        int i = left;
        int j = middle;
        int k = left;

        for (int i = left; i < right; ++i) {
            array[i] = ppArray[i];
        }

        while (i < middle && j < right) {
            if (pCompareFunc(array[i], array[j]) < 0) {
                ppArray[k] = array[i];
                i++;
            } else {
                ppArray[k] = array[j];
                j++;
            }
            k++;
        }

        while (i < middle) {
            ppArray[k] = array[i];
            i++;
            k++;
        }

        while (j < right) {
            ppArray[k] = array[j];
            j++;
            k++;
        }
    }

    void sort(void** ppArray, int left, int right, CompareSortType pCompareFunc, void** array) {
        if (left + 1 >= right) {
            return;
        }
        int middle = (left + right) / 2;
        sort(ppArray, left, middle, pCompareFunc, array);
        sort(ppArray, middle, right, pCompareFunc, array);
        merge(ppArray, left, middle, right, pCompareFunc, array);
    }

    void mergeSort(void** ppArray, int length, CompareSortType pCompareFunc) {
        void** array = new void*[length];
        sort(ppArray, 0, length, pCompareFunc, array);
        delete[] array;
    }
}

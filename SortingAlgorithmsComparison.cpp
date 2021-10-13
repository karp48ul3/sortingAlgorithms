// SortingAlgorithmsComparison.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <sstream>

void insertionSort(std::vector<int>& vectorToSort) {

    int i, key, j;

    for (i = 1; i < vectorToSort.size(); ++i) {
        key = vectorToSort[i];
        j = i - 1;

        while (j >= 0 && vectorToSort[j] > key)
        {
            vectorToSort[j + 1] = vectorToSort[j];
            j--;
        }
        vectorToSort[j + 1] = key;
    }

    return;
}

void bubbleSort(std::vector<int>& vectorToSort) {

    int i, j;
    for (i = 0; i < vectorToSort.size() - 1; i++)

        // Last i elements are already in place
        for (j = 0; j < vectorToSort.size() - i - 1; j++)
            if (vectorToSort[j] > vectorToSort[j + 1]) {
                int temp = vectorToSort[j];
                vectorToSort[j] = vectorToSort[j+1];
                vectorToSort[j+1] = temp;
            }
    return;
}

int heapSize = 0;

int parent(int i) {
    return i / 2;
}

int left(int i) {
    return 2 * i;
}

int right(int i) {
    return 2 * i + 1;
}

void heapify(std::vector<int>& vectorToSort, int i) {
    int l = left(i);
    int r = right(i);
    int largest;
    if (l < heapSize && vectorToSort[l] > vectorToSort[i]) {
        largest = l;
    }
    else {
        largest = i;
    }

    if (r < heapSize && vectorToSort[r] > vectorToSort[largest]) {
        largest = r;
    }

    if (largest != i) {
        int temp = vectorToSort[i];
        vectorToSort[i] = vectorToSort[largest];
        vectorToSort[largest] = temp;
        heapify(vectorToSort, largest);
    }

    return;
}

void buildHeap(std::vector<int>& vectorToSort) {
    for (int i = vectorToSort.size() / 2; i >= 0; i--) {
        heapify(vectorToSort, i);
    }
}


void heapSort(std::vector<int>& vectorToSort) {
    heapSize = vectorToSort.size();

    buildHeap(vectorToSort);
    for (int i = vectorToSort.size() - 1; i > 0; --i) {
        int temp = vectorToSort[0];
        vectorToSort[0] = vectorToSort[i];
        vectorToSort[i] = temp;
        heapSize--;
        heapify(vectorToSort, 0);
    }
}

int partition(std::vector<int> &vectorToSort, int p, int r) {

    int pivot = vectorToSort[r];

    int i = (p - 1);

        for (int j = p; j <= r - 1; j++)
        {
            if (vectorToSort[j] < pivot)
            { 
                i++; 
                int temp = vectorToSort[i];
                vectorToSort[i] = vectorToSort[j];
                vectorToSort[j] = temp;
            }
        }

        int temp = vectorToSort[i+1];
        vectorToSort[i+1] = vectorToSort[r];
        vectorToSort[r] = temp;
        return (i + 1);
}

void quickSort2(std::vector<int>& vectorToSort, int p, int r) {

    if (p < r-2) {
        int q = partition(vectorToSort, p, r);
        quickSort2(vectorToSort, p, q - 1);
        quickSort2(vectorToSort, q + 1, r);
    }
    else {
        if (vectorToSort[p] < vectorToSort[p + 1]) {
            if (vectorToSort[p + 1] < vectorToSort[p+2]) {

            }
            else {
                if (vectorToSort[p + 2] < vectorToSort[p]) {
                    int temp1 = vectorToSort[p];
                    vectorToSort[p] = vectorToSort[p + 2];
                    vectorToSort[p + 2] = vectorToSort[p + 1];
                    vectorToSort[p + 1] = temp1;
                }
            }
        }
        else {
            if (vectorToSort[p] < vectorToSort[p + 2]) {
                int temp = vectorToSort[p];
                vectorToSort[p] = vectorToSort[p + 1];
                vectorToSort[p + 1] = temp;
            }
            else {
                if (vectorToSort[p + 2] > vectorToSort[p + 1]) {
                    int temp = vectorToSort[p];
                    vectorToSort[p] = vectorToSort[p + 1];
                    vectorToSort[p + 1] = vectorToSort[p + 2];
                    vectorToSort[p + 2] = temp;
                }
                else {
                    int temp = vectorToSort[p];
                    vectorToSort[p] = vectorToSort[p + 2];
                    vectorToSort[p + 2] = temp;
                                    }
            }
        }
    }
}

void quickSort(std::vector<int>& vectorToSort, int p, int r) {

    if (p < r) {
        int q = partition(vectorToSort, p, r);
        quickSort(vectorToSort, p, q-1);
        quickSort(vectorToSort, q + 1, r);
    }
}

#define INPUT_VECTOR_SIZE 50000

int main()
{
    std::vector<int> inputVector(INPUT_VECTOR_SIZE);
    srand(time(NULL));

    for (int i = 0; i < INPUT_VECTOR_SIZE; ++i) {
        inputVector[i] = rand()%100;
    }

    /*std::cout << "unsorted numbers:" << std::endl;

    for(int number : inputVector)
    {
        std::cout << number << "  ";
    }*/
    
    //*************** QUICKSORT ***************
    std::vector<int> vec2{ inputVector };


    auto start2 = std::chrono::system_clock::now();

    quickSort(vec2, 0, vec2.size() - 1);

    auto end2 = std::chrono::system_clock::now();
    std::chrono::duration<double> diff2 = end2 - start2;
    std::ostringstream o2;
    ;
    o2 << diff2.count();
    std::string s2 = o2.str();
    //*******************************************

    //*************** HEAPSORT ***************
    std::vector<int> vec1{ inputVector };

    auto start = std::chrono::system_clock::now();

    heapSort(vec1);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::ostringstream o;
    o << diff.count();
    std::string s1 = o.str();
    // *******************************************

    //*************** BUBBLE SORT ***************
    std::vector<int> vec3{ inputVector };

    auto start3 = std::chrono::system_clock::now();

    bubbleSort(vec3);

    auto end3 = std::chrono::system_clock::now();
    std::chrono::duration<double> diff3 = end3 - start3;

    std::ostringstream o3;
    o3 << diff3.count();
    std::string s3 = o3.str();
    // *******************************************

    //*************** INSERTION SORT ***************
    std::vector<int> vec4{ inputVector };

    auto start4 = std::chrono::system_clock::now();

    insertionSort(vec4);

    auto end4 = std::chrono::system_clock::now();
    std::chrono::duration<double> diff4 = end4 - start4;

    std::ostringstream o4;
    o4 << diff4.count();
    std::string s4 = o4.str();
    // *******************************************

    std::cout << "Heapsort:      " << s1 << " sec"<< std::endl;
    std::cout << "Quicksort:     " << s2 << " sec" << std::endl;
    std::cout << "Bubblesort:    " << s3 << " sec" << std::endl;
    std::cout << "Insertionsort: " << s4 << " sec" << std::endl;


    /*std::cout << std::endl << "Sorted numbers:"<<std::endl;

    for (int number : vec2)
    {
        std::cout << number << "  ";
    }*/

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

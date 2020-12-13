#include<iostream>
#include<array>
#include<algorithm>
#include<chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

/* Global Variables */
int arraySize = 2000;

/* Algorithm1 - MergeSort */

int Algorithm1(int myArray[], int size, int kth)

{

    sort(myArray, myArray + size);

    return myArray[kth - 1];

}

/* Algorithm 2a - QuickSort Iteratively */

/* partition2 declaration */

int partition2(int myArray[], int l, int r);

int Algorithm2a(int myArray[], int low, int high, int kth)

{

    if (kth > 0 && kth <= high - low + 1)

    {

        int position = partition2(myArray, low, high);

        if (position - low == kth - 1)

        {

            return myArray[position];

            low = position + 1;

        }

        else if (position - low > kth - 1)

        {

            return Algorithm2a(myArray, low, position - 1, kth);

            high = position - 1;

        }

        else

        {

            return Algorithm2a(myArray, position + 1, high,

                kth - position + 1 - 1);

        }

    }

    return INT_MAX;

}

/* Algorithm2b - QuickSort Recursively */

int Algorithm2b(int myArray[], int l, int r, int kth)

{

    if (kth > 0 && kth <= r - l + 1)

    {

        int position = partition2(myArray, l, r);

        if (position - l == kth - 1)

            return myArray[position];

        if (position - l > kth - 1)

            return Algorithm2b(myArray, l, position - 1, kth);

        return Algorithm2b(myArray, position + 1, r, kth - position + l - 1);

    }

    return INT_MAX;

}

/* swap2 definition used in Algorithm2a and Algorithm2b */

void swap2(int* a, int* b)

{

    int temporary = *a;

    *a = *b;

    *b = temporary;

}

/* partition2 definition - used in Algorithm2a and Algorithm2b */

int partition2(int myArray[], int l, int r)

{

    int x = myArray[r], i = l;

    for (int j = l; j <= r - 1; j++)

    {

        if (myArray[j] <= x)

        {

            /* calling swap2 method */

            swap2(&myArray[i], &myArray[j]);

            i++;

        }

    }

    /* calling swap2 method */

    swap2(&myArray[i], &myArray[r]);

    return i;

}

/* Algorithm3 - QuickSort with mm rule */

int partition3(int myArray[], int l, int r, int kth);

/* findMedian3 method */

int findMedian3(int myArray[], int size)

{

    sort(myArray, myArray + size);

    return myArray[size / 2];

}

/* Algorithm3 definition */

int Algorithm3(int myArray[], int l, int r, int kth)

{

    if (kth > 0 && kth <= r - l + 1)

    {

        int size = r - l + 1;

        int i, median[(10 + 4) / 5];

        for (i = 0; i < size / arraySize; i++)

            median[i] = findMedian3(myArray + l + i * 5, 10);

        if (i * 5 < size)

        {

            median[i] = findMedian3(myArray + l + i * 5, size % 10);

            i++;

        }

        int medOfMed = (i == 1) ? median[i - 1] : Algorithm3(median, 0, i - 1, i / 2);

        int position = partition3(myArray, l, r, medOfMed);

        if (position - l == kth - 1)

            return myArray[position];

        if (position - l > kth - 1)

            return Algorithm3(myArray, l, position - 1, kth);

        return Algorithm3(myArray, position + 1, r, kth - position + l - 1);

    }

    return INT_MAX;

}

/* swap3 definition used in Algorithm3 */

void swap3(int* a, int* b)

{

    int temporary = *a;

    *a = *b;

    *b = temporary;

}

/* partition3 definition used in Algorithm3 */

int partition3(int myArray[], int l, int r, int x)

{

    int i;

    for (i = l; i < r; i++)

        if (myArray[i] == x) break;

    /* calling swap3 method */

    swap3(&myArray[i], &myArray[r]);

    i = l;

    for (int j = l; j <= r - 1; j++)

    {

        if (myArray[j] <= x)

        {

            /* calling swap3 method */

            swap3(&myArray[i], &myArray[j]);

            i++;

        }

    }

    /* calling swap3 method */

    swap3(&myArray[i], &myArray[r]);

    return i;

}

/* Main method */

int main()
{

    /* Array size */
    int myArray[2000];

    /* size */
    int size = sizeof(myArray) / sizeof(myArray[0]);

    cout << "Array Size: " << arraySize << endl;
    cout << "MyArray Size: " << size << endl;

    /* Populate array with random integers from 1 - Maxinum integer */
    for (int i = 0; i < size; i++) {
        myArray[i] = (rand() % INT_MAX + 1);
        //cout << myArray[i] << " ";
    }

    /* kth declaration */

    int kth;
    int kthArray[5] = { 1, (size / 4), (size / 2), (3 * size) / 4, size };
    int kthSize = sizeof(kthArray) / sizeof(kthArray[0]);

    /*Collect Total time for each algorithm cases*/
    double a1TotalTime = 0;
    double a2aTotalTime = 0;
    double a2bTotalTime = 0;
    double a3TotalTime = 0;
    
    //Iterate through each K position
    for (int k = 0; k < kthSize; k++) {
        
        kth = kthArray[k];
        cout << endl;
        //Label each Kth
        switch (k) {
            case 0:
                cout << "Kth position: 1 or " << "index: " << kth << endl;
                break;
            case 1:
                cout << "Kth position: N/4 or " << "index: " << kth << endl;
                break;
            case 2:
                cout << "Kth position: N/2 or " << "index: " << kth << endl;
                break;
            case 3:
                cout << "Kth position: 3N/4 or " << "index: " << kth << endl;
                break;
            case 4:
                cout << "Kth position: N or " << "index: " << kth << endl;
                break;
        }
        
        /* ALGO 1 */
        //Run the algorithm 50 times
        for (int x = 0; x < 50; x++) {
            auto start = high_resolution_clock::now();
            Algorithm1(myArray, size, kth);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            //Total the time taken to run all the tests
            a1TotalTime = duration.count() + a1TotalTime;
        }

        //Calculate the average time per iteration after 50 cycles
        //cout << "Select-Kth 1 is:  " << Algorithm1(myArray, size, kth) << endl;
        //cout << a1TotalTime << endl;
        a1TotalTime = a1TotalTime / 50;
        cout << "Average total time: " << setprecision(6) << a1TotalTime << " microseconds" << endl << endl;

        /* ALGO 2A */
        for (int x = 0; x < 50; x++) {
            auto start = high_resolution_clock::now();
            Algorithm2a(myArray, 0, size - 1, kth);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            //Total the time taken to run all the tests
            a2aTotalTime = duration.count() + a2aTotalTime;
        }

        //cout << "Select-Kth 2 is:  " << Algorithm2a(myArray, 0, size - 1, kth) << endl;
        //cout << a2aTotalTime << endl;
        a2aTotalTime = a2aTotalTime / 50;
        cout << "Average total time: " << setprecision(6) << a2aTotalTime << " microseconds" << endl << endl;

        /* ALGO 2B */
        //Run the algorithm 50 times
        for (int x = 0; x < 50; x++) {
            auto start = high_resolution_clock::now();
            Algorithm2b(myArray, 0, size - 1, kth);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            //Total the time taken to run all the tests
            a2bTotalTime = duration.count() + a2bTotalTime;
        }

        //cout << "Select-Kth 3 is:  " << Algorithm2b(myArray, 0, size - 1, kth) << endl;
        //cout << a2bTotalTime << endl;
        a2bTotalTime = a2bTotalTime / 50;
        cout << "Average total time: " << setprecision(6) << a2bTotalTime << " microseconds" << endl << endl;

        /* ALGO 3*/
        //Run the algorithm 50 times
        for (int x = 0; x < 50; x++) {
            auto start = high_resolution_clock::now();
            Algorithm3(myArray, 0, size - 1, kth);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            //Total the time taken to run all the tests
            a3TotalTime = duration.count() + a3TotalTime;
        }

        //cout << "Select-Kth 4 is:  " << Algorithm3(myArray, 0, size - 1, kth) << endl;
        //cout << a3TotalTime << endl;
        a3TotalTime = a3TotalTime / 50;
        cout << "Average total time: " << setprecision(6) << a3TotalTime << " microseconds" << endl << endl;

    }

    getchar(); getchar(); return 0;
}


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>


long* array;
long length = 10000000;
int count = 0;
int counter = 0;
int threads = 16;
clock_t start_time, end_time;


//Requires: It requires nothing as a parameter,but it requires an array as a global variable to work on
//Effects : Returns the number of ones in this array

int countOnes() {
    for (int i = 0; i < length; i++)
    {
        if (array[i] == 1)
        {

            counter++;
        }
    }
    return counter;
}


//Requires: ID thread where the ID ranges from 0 to n - 1 and n is the number of threads, and 0 is the master thread
//Effects : Returns the number of ones the threads have counted.
// 
//Test Cases :
// Array sizes of 100, 1000, 10000, 1000000, 10000000, 100000000, 1000000000 with threads of sizes 1, 2, 4, 8, 16, 32, 64.
// for example we do 100.. with 1,2,4.. thread
void* threadCount(void* ID) {
    long id = (long)ID; // here i am casting the ID from void pointer to long
    long iter = length / threads; // number of iterations
    long start = id * iter;
    long end = start + iter;

    if (length - end < iter)
    {
        end = length;
    }

    for (start; start < end; start++)
    {
        if (array[start] == 1)
            count++;
    }
}
// race condition method:
// requires:number of threads
// effects: it return answers, and we should report the number of times the program returns the right answer
int main() {

    start_time = clock();
    array = (long*)malloc(length * sizeof(long));

    for (long i = 0; i < length; i++)
    {
        array[i] = rand() % 5 + 1;
    }

    counter = countOnes();
        pthread_t T[16];

    for (int i = 0; i < 16; i++)
    {
        pthread_create(&T[i], NULL, &threadCount, (void*)i);
    }

    for (int i = 0; i < threads; i++)
    {
        pthread_join(T[i], NULL);
    }

    end_time = clock();
    double Time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;


    printf("Total time is %f\n", Time);
    printf("the number of ones= %d\n", counter);
    printf("number of ones with multiple threads: %d\n", count);
    free(array);

    return 0;

}
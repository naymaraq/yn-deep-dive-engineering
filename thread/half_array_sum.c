#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Structure to pass the relevant data to each thread
typedef struct ThreadData {
    int* array;
    int start;
    int end;
} threadata;

// Thread function to compute the sum of a section of the array
void* half_sum(void* arg) {
    threadata* data = (threadata*)arg;
    long sum = 0;
    
    // Sum the section of the array assigned to this thread
    for(int i = data->start; i < data->end; i++) {
        sum += (data->array)[i];
    }

    // Print the partial sum for this thread
    printf("Partial sum: %ld\n", sum);
    return NULL;
}

int main() {
    // Create a vector of integers
    const int array_size = 10;
    int *array = (int*)malloc(array_size * sizeof(int));

    for (int i = 0; i<array_size; i++){
        array[i] = i;
    }

    // Define the two threads
    pthread_t thread1, thread2;

    // Define thread data structures
    threadata data1 = {array, 0, array_size / 2 };    // First half
    threadata data2 = {array, array_size / 2, array_size }; // Second half

    // Create the first thread to process the first half of the array
    pthread_create(&thread1, NULL, half_sum, (void*)&data1);

    // Create the second thread to process the second half of the array
    pthread_create(&thread2, NULL, half_sum, (void*)&data2);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Print a final message indicating that all threads are done
    printf("All threads have completed\n");

    return 0;
}

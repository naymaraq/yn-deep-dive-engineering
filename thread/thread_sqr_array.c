#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Thread function to calculate and print the square of the number
void* calculate_square(void* arg) {
    int number = *(int*)arg;  // Cast the void pointer to int* and dereference it to get the number
    int square = number * number;
    printf("Square of %d is %d\n", number, square);
    return NULL;
}

int main() {
    // Define an array of integers
    int numbers[] = {1, 2, 3, 4, 5};
    int num_elements = sizeof(numbers) / sizeof(numbers[0]);

    // Create an array to hold the thread identifiers
    pthread_t threads[num_elements];

    // Create a thread for each number to calculate its square
    for (int i = 0; i < num_elements; i++) {
        // Create a thread and pass the address of the number to it
        pthread_create(&threads[i], NULL, calculate_square, (void*)&numbers[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < num_elements; i++) {
        pthread_join(threads[i], NULL);
    }

    // Indicate that all threads have completed
    printf("All threads have completed\n");

    return 0;
}

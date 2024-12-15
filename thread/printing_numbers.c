#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Thread function to print numbers from 1 to 5 with thread ID
void* print_numbers(void* arg) {
    pthread_t thread_id = pthread_self();  // Get the current thread ID
    
    for (int i = 1; i <= 5; i++) {
        printf("Thread ID: %lu, Number: %d\n", (long)thread_id, i);
    }

    return NULL;
}

int main() {
    pthread_t threads[3];  // Array to hold thread identifiers

    // Create 3 threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, print_numbers, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    // Indicate that all threads have completed
    printf("All threads have completed\n");

    return 0;
}

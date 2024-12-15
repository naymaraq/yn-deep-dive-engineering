#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Thread function
void* thread_function(void* arg) {
    long thread_id = (long)arg;  // Thread ID passed as an argument
    printf("Thread %ld is running\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[3];  // Array to store thread identifiers

    // Create three threads
    for (long i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, (void*)i) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // Wait for each thread to complete
    for (int i = 0; i < 3; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    printf("All threads have completed\n");

    return 0;
}

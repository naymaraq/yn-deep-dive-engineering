#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>

int x = 5;
bool flag[2] = {false, false};
int turn;

void* increment(void* arg) {
    int id = 0;
    for (int i = 0; i < 10; i++) {
        flag[id] = true;
        turn = 2;
        while (flag[1] && turn == 2) {
            // Busy wait
        }

        // Critical section
        print(f)
        x++;

        // Exit section
        flag[id] = false;
    }
    return NULL;
}

void* decrement(void* arg) {
    int id = 1;
    for (int i = 0; i < 10; i++) {
        flag[id] = true;
        turn = 1;
        while (flag[0] && turn == 1) {
            // Busy wait
        }

        // Critical section
        x--;

        // Exit section
        flag[id] = false;
    }
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    for (int i = 0; i < 10; i++) {
        // Create threads
        pthread_create(&tid1, NULL, increment, NULL);
        pthread_create(&tid2, NULL, decrement, NULL);

        // Wait for threads to complete
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        // Print the final value of x
        printf("Final value of x: %d\n", x);
    }

    return 0;
}

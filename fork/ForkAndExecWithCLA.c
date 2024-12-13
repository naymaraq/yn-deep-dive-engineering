#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"

//Assignment 4: Fork and Exec with Command-Line Arguments
//Objective: Use fork and execl to run a command with multiple arguments.
//Prepare a test.txt file with some text.
//
// Write a program that:
//Uses fork to create a child process.
//The child process should use execl to run the pwd command


int main(void) {
    const int pid = fork();
    check_fork_result(pid);

    if (pid) {
        printf("Parent process done\n");
        wait(NULL);
    } else {
        int ret = execl("/bin/pwd", "pwd", NULL);
        check_exec_result(ret);
    }
    return 0;
}
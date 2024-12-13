#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"

// Assignment 1: Simple Fork and Exec
// Objective: Understand the creation of a child process using fork and how
// to replace it with a new program using execl.
//
// Write a program that:
// Uses fork to create a child process.
// In the child process, use execl to run the ls command
// to list the contents of the current directory.
// The parent process should print "Parent process done"
// after the child process is created.
// Expected Output: The directory listing should be printed,
// followed by the parent's message.


int main(void) {
    const int pid = fork();
    check_fork_result(pid);
    if (pid) {
        printf("Parent process %d\n", pid);
        wait(NULL);
    } else {
        printf("Child process %d\n", pid);
        const int ret = execl( "/bin/ls", "ls", "-l", (char*)0 );
        check_exec_result(ret);
    }
    return 0;
}
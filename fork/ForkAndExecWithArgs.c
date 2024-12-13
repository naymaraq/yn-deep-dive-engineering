#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"

//Assignment 3: Fork and Exec with Arguments
//Objective: Understand how to pass arguments to programs executed with execl.
//Write a program that:
//Uses fork to create a child process.
//The child process should use execl to run the echo command with an argument
//(e.g., "Hello from the child process").
//The parent process should print "Parent process done" after the child process is created.
//Expected Output: The message from the echo command followed by the parent's message.


int main(void) {
    const int pid = fork();
    check_fork_result(pid);
    if (pid) {
        printf("Parent process done\n");
        wait(NULL);
    }
    else {
        int ret = execl("/bin/echo", "echo", "Hello from the child process", NULL);
        check_exec_result(ret);
    }
    return 0;
}
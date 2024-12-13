//Assignment 2: Multiple Forks and Execs
//Objective: Work with multiple child processes created
//using fork and run different commands using execl.
//
// Write a program that:
//Creates two child processes using fork.
//The first child process should use execl to run the ls command.
//The second child process should use execl to run the date command.
//The parent process should print "Parent process done" after creating both child processes.
//Expected Output: The output of the ls command followed by
//the output of the date command, and finally the parent's message.

#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"


int main(void) {
    const int pid1 = fork();
    check_fork_result(pid1);

    if (pid1 == 0) {
        //parent - > child1 will print ls
        int ret = execl("/bin/ls", "ls", NULL);
        check_exec_result(ret);
    } else {
        const int pid2 = fork();
        check_fork_result(pid2);
        if (pid2 == 0) {
            //parent - > child2 will print date
            int ret = execl("/bin/date", "date", NULL);
            check_exec_result(ret);
        } else {
            //parent
            wait(NULL);
            wait(NULL);
            printf("Parent process done\n");
        }
    }
    return 0;
}
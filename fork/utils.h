#pragma once
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


void check_fork_result(int pid) {
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

void check_exec_result(int ret_code) {
    if (ret_code == -1) {
        perror("execl");
        exit(errno);
    }
}
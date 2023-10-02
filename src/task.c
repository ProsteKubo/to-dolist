#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "task.h"

char* create_task_string(Task* task) {
    char* res = malloc(sizeof(task->name) + sizeof(task->description) + sizeof(task->done) + 4);

    char* done_string = malloc(sizeof(char));

    sprintf(done_string, "%d", task->done);

    strcpy(res, task->name);
    strcat(res, " ");
    strcat(res, task->description);
    strcat(res, " ");
    strcat(res, done_string);
    strcat(res, "\n");

    return res;
}
#include <string.h>
#include <stdlib.h>
#include "task_list.h"

Task* get_by_name(struct TaskList* list, char* name) {
    if (list == NULL) {
        return NULL;
    }

    struct TaskList* current_node = list;

    while (current_node != NULL) {
        if (strcmp(name, current_node->data.name) == 0) {
            return &current_node->data;
        }
        current_node = current_node->next;
    }

    return NULL;
}

int insert(struct TaskList** list, Task* task) {
    if (*list == NULL) {
        return 1;
    }

    struct TaskList* current_node = *list;
    struct TaskList* new_node = malloc(sizeof(struct TaskList));

    if (new_node == NULL) {
        return 1;
    }

    new_node->data = *task;
    new_node->next = NULL;

    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    current_node->next = new_node;

    return 0;
}

int delete(struct TaskList** list, char* name) {
    if (*list == NULL) {
        return 1;
    }

    struct TaskList* current_node = *list;
    struct TaskList* previous = *list;

    while (current_node != NULL) {
        if (strcmp(name, current_node->data.name) == 0) {
            if (previous == current_node) {
                *list = current_node->next;
                free(current_node);
                return 0;
            }
            previous->next = current_node->next;
            free(current_node);

            return 0;
        }
        previous = current_node;
        current_node = current_node->next;
    }

    return 1;
}

int update_task_list(struct TaskList* list, char* name, Task* task) {
    if (list == NULL) {
        return 1;
    }

    struct TaskList* current_node = list;

    while (current_node != NULL) {
        if (strcmp(name, current_node->data.name) == 0) {
            current_node->data = *task;
            return 0;
        }
        current_node = current_node->next;
    }

    return 1;
}

int destroy(struct TaskList** list) {
    if (*list == NULL) {
        return 0;
    }

    struct TaskList* current_node = *list;

    while (current_node != NULL) {
        struct TaskList* temp_node = current_node;
        current_node = current_node->next;
        free(temp_node);
    }

    *list = NULL;

    return 0;
}

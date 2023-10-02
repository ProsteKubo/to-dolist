#ifndef TO_DOLIST_TASK_LIST_H
#define TO_DOLIST_TASK_LIST_H
#include "task.h"

struct TaskList{
    Task data;
    struct TaskList* next;
};

Task* get_by_name(struct TaskList* list, char* name);
int insert(struct TaskList** list, Task* task);
int delete(struct TaskList** list, char* name);
int update_task_list(struct TaskList* list, char* name, Task* task);
int destroy(struct TaskList** list);

#endif //TO_DOLIST_TASK_LIST_H

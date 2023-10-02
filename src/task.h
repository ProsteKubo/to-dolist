#ifndef TASK
#define TASK

typedef struct {
	char* name;
	char* description;
	int done;
} Task;

char* create_task_string(Task* task);

#endif // !TASK

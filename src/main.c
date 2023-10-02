#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "map.h"
#include "task.h"
#include "utilities/task_list.h"

// TODO: saving tasks and encryption, web-server, web-sockets, mobile app

typedef struct TaskList TaskList;
int logged_in = 0;

FILE * file_ptr;

int running = 1;

int max_character_limit = 50;

struct TaskList* tasks = NULL;

Command commands [] = {
    {-1, "q"}, // quit
    {1, "l"},  // login
	{2, "r"},  // register
    {3, "lo"}, // logout
    {4, "s"},  // see all tasks
    {5, "c"},  // create task
    {6, "u"},  // update_task_list task
    {7, "ss"}, // see single task
    {8, "d"},  // delete task
};

void delete_single_task() {
    char* name = malloc(sizeof(char) * max_character_limit);
    printf("Enter task name: ");
    scanf("%s", name);

    delete(&tasks, name);
}

Task* get_task_info() {
    char* task_name = malloc(sizeof(char) * max_character_limit);
    char* description = malloc(sizeof(char) * max_character_limit);
    char* is_done = malloc(sizeof(char));

    printf("Task name: ");
    scanf("%s", task_name);
    printf("\nTask description: ");
    scanf("%s", description);
    printf("\nIs task finished(y/n): ");
    scanf("%s", is_done);

    Task* task = malloc(sizeof(Task));

    task->name = task_name;
    task->description = description;
    task->done = strcmp(is_done, "y") == 0;

    return task;
}

void print_single_task() {
    char* task_name = malloc(sizeof(char) * max_character_limit);
    printf("Enter task name: ");
    scanf("%s", task_name);

    Task* task = get_by_name(tasks, task_name);

    if (task == NULL) {
        printf("Couldn't find task with name: %s", task_name);
        return;
    }

    printf("%s", create_task_string(task));
}

void create_task() {
    Task* task = get_task_info();

    if (tasks == NULL) {
        tasks = malloc(sizeof(struct TaskList));
        tasks->data = *task;
        tasks->next = NULL;
    } else
        insert(&tasks, task);

    printf("successfully inserted new task\n");
}

void update_task() {
    char* name = malloc(sizeof(char) * max_character_limit);
    printf("Enter name of the task you want to update_task_list: ");
    scanf("%s", name);

    // check if task exist
    Task* task = get_by_name(tasks, name);

    if (task == NULL) {
        printf("Couldn't find task with this name");
        return;
    }

    // get new info about task
    Task* new_task = get_task_info();

    // update_task_list task
    update_task_list(tasks, name, new_task);

    printf("Updated task with name: %s\n", name);
}

void print_all_tasks() {
    TaskList* current_task = tasks;
    while(current_task != NULL) {
        printf("%s\n", create_task_string(&current_task->data));
        current_task = current_task->next;
    }
}

char* create_login_string(char* given_username, char* given_password) {
    char* login_string = malloc(sizeof(char) + 110);
    strcpy(login_string, given_username);
    strcat(login_string, "||");
    strcat(login_string, given_password);
    strcat(login_string, "\n");

    return  login_string;
}

void login() {
    char* username = malloc(sizeof(char) * max_character_limit);
    char* password = malloc(sizeof(char) * max_character_limit);

    printf("Username: ");
	scanf("%s", username);
	printf("\nPassword: ");
	scanf("%s", password);

	char* login_string = create_login_string(username, password);

    file_ptr = fopen("users.txt", "r");

    if (file_ptr == NULL) {
        // maybe create file later idk
        return;
    }

    //get all users
    // scheme in file username||password
    char* file_data = malloc(sizeof(char) * 110);
    while (fgets(file_data, 110, file_ptr)) {
        if (strcmp(login_string, file_data) == 0) {
            logged_in = 1;
            break;
        }
    }

    if (logged_in == 1) {
        printf("Successfully registered with username: %s\n", username);
    } else {
        printf("Failed to log in with username: %s\n", username);
    }

    fclose(file_ptr);
    free(file_data);
    free(username);
    free(password);
}

void reg() {
    char* username = malloc(sizeof(char) * max_character_limit);
    char* password = malloc(sizeof(char) * max_character_limit);

    printf("Username: ");
    scanf("%s", username);
    printf("\nPassword: ");
    scanf("%s", password);

    char* login_string = create_login_string(username, password);

    file_ptr = fopen("users.txt", "a");

    if (file_ptr == NULL) {
        // maybe create file later idk
        return;
    }

    fputs(login_string, file_ptr);

    fclose(file_ptr);

    free(username);
    free(password);
    free(login_string);
}

void logout() {
    logged_in = 0;
}

int parse_command(char* input) {
	for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
		if (strcmp(input, commands[i].values) == 0) {
			return commands[i].key;
		}
	}

	return 0;
}

void parse_secure_commands(int command) {
    switch (command) {
        case 3:
            logout();
            break;
        case 4:
            print_all_tasks();
            break;
        case 5:
            create_task();
            break;
        case 6:
            update_task();
            break;
        case 7:
            print_single_task();
            break;
        case 8:
            delete_single_task();
            break;
        default:
            printf("Unknown command\n");
            break;
    }
}

void parse_auth_commands(int command) {
    if (command == 1) {
        login();
    }

    if (command == 2) {
        reg();
    }
}

int main() {
	char* current_command_string = malloc(5 * sizeof(char));

	while (running == 1) {

        if (!logged_in) {
            printf("Hello welcome into To-Do list.\n"
                   "If you want to log in write l if you want to register write r and if you need help write h.\n");

        } else {
            printf("Hello, if you want to see your tasks write s, if you want to create new one write c.\n");
        }

		scanf("%s", current_command_string);
		int current_command = parse_command(current_command_string);

		if (current_command == -1) {
			running = 0;
		}

        if (!logged_in && current_command <= 2) {
            parse_auth_commands(current_command);
        }

        if (logged_in && current_command > 2) {
            parse_secure_commands(current_command);
        }
    }

    // cleaning up
	free(current_command_string);
    destroy(&tasks);

	return 0;
}

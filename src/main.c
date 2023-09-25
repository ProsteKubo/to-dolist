#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "map.h"
#include "task.h"

int current_task_list_length = 2;

int logged_in = 0;

FILE * fileptr;

int running = 1;

int max_character_limit = 50;

Task* tasks;

Command commands [] = {
	{1, "l"},
	{2, "r"},
	{3, "q"},
};

void add_task() {
    current_task_list_length += 1;

	tasks = realloc(tasks, current_task_list_length);

    if (tasks == NULL) {
        return;
    }
}

char* create_login_string(char* given_username, char* given_password) {
    char* login_string = malloc(sizeof(char) + 110);
    strcpy(login_string, given_username);
    strcat(login_string, "||");
    strcat(login_string, given_password);

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

	fileptr = fopen(".\\users.txt", "a+");

    if (fileptr == NULL) {
        // maybe create file later idk
        return;
    }

    //get all users
    // scheme in file username||password
    char* file_data = malloc(sizeof(char) * 110);
    while (fgets(file_data, 110, fileptr)) {
        printf("%s", file_data);
        if (strcmp(login_string, file_data) == 0) {
            logged_in = 0;
            break;
        }
    }

    fclose(fileptr);
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

    fileptr = fopen("users.txt", "a");

    if (fileptr == NULL) {
        // maybe create file later idk
        return;
    }

    fputs(login_string, fileptr);

    fclose(fileptr);
    free(username);
    free(password);
    free(login_string);
}

int parse_command(char* input) {
	for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
		if (strcmp(input, commands[i].values) == 0) {
			return commands[i].key;
		}
	}

	return 0;
}

int main() {
	char* current_command_string = malloc(5 * sizeof(char));

	while (running == 1) {
		printf("Hello welcom into To-Dolist.\n"
               "If you want to log in write l if you want to register write r and if you need help write h.\n");

		int current_command = parse_command(current_command_string);

		if (current_command == 3) {
			running = 0;
		}

        if (current_command == 1) {
            login();
        }

        if (current_command == 2) {
            reg();
        }
    }

    // cleaning up
	free(current_command_string);
    free(fileptr);
    free(tasks);

	return 0;
}

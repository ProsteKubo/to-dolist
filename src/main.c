#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "map.h"
#include "task.h"

int current_tasklist_length = 2;

char* username;
char* password;

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
	current_tasklist_length += 1;

	tasks = realloc(tasks, current_tasklist_length);

    if (tasks == NULL) {
        return;
    }
}

void login() {
    username = malloc(sizeof(char) * max_character_limit);
    password = malloc(sizeof(char) * max_character_limit);

    printf("Username: ");
	scanf("%s", username);
	printf("\nPassword: ");
	scanf("%s", password);
	
	fileptr = fopen(".\\data.txt", "r+");
}

void reg() {

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
		scanf("%s", current_command_string);

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

		printf("%d", current_command);
	}

    // cleaning up
	free(current_command_string);
    free(username);
    free(password);
    free(fileptr);
    free(tasks);

	return 0;
}

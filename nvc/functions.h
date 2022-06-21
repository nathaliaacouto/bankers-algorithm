#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define F 1 //False
#define T 0 //True

#define SAFE_STATE 0
#define UNSAFE_STATE -1

#define REQUEST_RESOURCES 1
#define RELEASE_RESOURCES 2
#define SHOW_VALUES 3

int number_of_resources;
int number_of_costumers;

int *available; //number of resources available

int number_of_commands;
//int commands_arr[100]; //store commands from commands.txt
char read_com[100];
int next_command;

int count_file_lines(FILE *file);
int verify_command(char* arr);
int system_state(int *av, int n[number_of_costumers][number_of_resources], int client, int al[number_of_costumers][number_of_resources]);
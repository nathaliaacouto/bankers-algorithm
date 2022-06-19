#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 1
#define TRUE 0

#define SAFE_STATE 10

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
int** get_max_resources(void);
char* read_commands(void);
int verify_command(char* arr);
int* request(void);
void print_commands(void);
int system_state(int *w, int *f, int *ni, int *ai);
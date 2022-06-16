#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number_of_resources;
int number_of_costumers;

int count_file_lines(FILE *file);
void get_max_resources(void);
void read_commands(void);
void verify_command(char* arr);
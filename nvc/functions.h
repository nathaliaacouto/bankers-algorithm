#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number_of_resources;
int number_of_costumers;
char read_com[100];

int count_file_lines(FILE *file);
void get_max_resources(void);
void read_commands(int count);
void verify_command(char* arr);
void request(char* r, int* av);
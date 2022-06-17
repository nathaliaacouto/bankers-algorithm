#include "functions.h"
#include "errors.h"

/* Counts how many lines there are in a file */
int count_file_lines(FILE *file) 
{
  char a = 0;
  int count = 0;

  while (a != EOF) {
    a = getc(file);
    if (a == '\n') {
      count++;
    }
  }

  int b = count + 1;
  return b;
}

/* Get numbers from a file and
stores then in a matrix */
void get_max_resources(void) 
{
  FILE *costumers = fopen("customer.txt", "r");
  error_open_file(costumers);

  int maximum[number_of_costumers][number_of_resources];
  int read_com;

  for(int i = 0; i < number_of_costumers; i++) {
    for(int j = 0; j < number_of_resources; j++) {
      fscanf(costumers, "%d,", &read_com);
      maximum[i][j] = read_com;
    }
  }

  FILE *test = fopen("test.txt", "w");
  for(int i = 0; i < number_of_costumers; i++) {
    fprintf(test, "\nCliente %d\n", i);
    for(int j = 0; j < number_of_resources; j++) {
      fprintf(test, "%d  ", maximum[i][j]);
    }
  }
  fclose(test);

  fclose(costumers);
}

/* Reads lines in the file "commands.txt" */
void read_commands(int count)
{
  FILE *com = fopen("commands.txt", "r");
  int a = 0;
  while(a != count) {
    fgets(read_com, 20, com);
    printf("\nread_com: %s", read_com);
    verify_command(read_com);
    a++;
  }

  fclose(com);
}

void verify_command(char* arr)
{
  if(arr[0] == '*') {
    printf("asterisco\n");
  }
  else if(arr[0] == 'R') {
    if(arr[1] == 'Q') {
      printf("requesting resources\n");
    }
    else if(arr[1] == 'L') {
      printf("releasing resources\n");
    }
  }
}

void request(char* r, int* av)
{
  int a = 3;
  int client = r[a] - '0';
  int req[number_of_resources];

  for(int i = 0; i < number_of_resources; i++) {
    a = a + 2; //jump space between numbers
    req[i] = r[a] - '0';
  }

  for(int i = 0; i < number_of_resources; i++) {
    if(req[i] < av[i]) {
      printf("ok");
    }
  }
}
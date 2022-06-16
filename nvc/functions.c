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
  int aux;

  for(int i = 0; i < number_of_costumers; i++) {
    for(int j = 0; j < number_of_resources; j++) {
      fscanf(costumers, "%d,", &aux);
      maximum[i][j] = aux;
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

  read_commands();
}

/* Reads lines in the file "commands.txt" */
void read_commands(void)
{
  char aux[20];
  char teste[20];
  int a = 0;

  FILE *commands = fopen("commands.txt", "r");
  //int c = count_file_lines(commands);
  fgets(aux, 20, commands);

  printf("aux: %s\n", aux);

  char *token = strtok(aux, " ");
  //printf("%c\n", token[1]); //printing the token
  verify_command(token);
  
  fclose(commands);
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
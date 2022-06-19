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
stores then in a matrix 
int** get_max_resources(void) 
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

  return maximum;
} */

/* Reads lines in the file "commands.txt" */
char* read_commands(void)
{
  FILE *com = fopen("commands.txt", "r");
  int a = 0;
  while(a != number_of_commands) {
    fgets(read_com, 20, com);
    //printf("\nread_com: %s", read_com);
    verify_command(read_com);
    a++;
  }
  count_commands = 0;
  fclose(com);

  return read_com;
}

/* See wich command was given and
stores its value in the commands array */
int verify_command(char* arr)
{
  if(arr[0] == '*') {
    //printf("asterisco\n");
    return SHOW_VALUES;
  }
  else if(arr[0] == 'R') {
    if(arr[1] == 'Q') {
      //printf("requesting resources\n");
      return REQUEST_RESOURCES;
    }
    else if(arr[1] == 'L') {
      //printf("releasing resources\n");
      return RELEASE_RESOURCES;
    }
  }
}

/* Prints the commands array 
void print_commands(void)
{
  for(int i = 0; i < number_of_commands; i++) {
    printf("\ncomando %d: %d", i, commands_arr[i]);
  }
}
*/
/* Request Resources */
int* request(void)
{
  int a = 3;
  int client = read_com[3] - '0';
  printf("%d", client);
  int req[number_of_resources+1];
  req[0] = client;
  for(int i = 1; i < number_of_resources; i++) {
    a = a + 2; //jump space between numbers
    req[i] = read_com[a] - '0';
  }
  return req;
} 

/*
int system_state(int *w, int *f, int *ni, int *ai)
{
  for(int i = 0; i < number_of_commands; i++) {
    w[i] = available[i];
  }
  for(int i = 0; i < number_of_costumers; i++) {
    f[i] = FALSE;
  }

  for(int i = 0; i < number_of_commands; i++) { //problema: f tem mais q num de comandos
    if(ni[i] <= w[i] && f[i] == FALSE) {
      f[i] = TRUE;
      for(int j = 0; j < number_of_commands; j++) {
        w[j] = w[j] + ai[j];
      }
    }
  }
  int count = 0;
  for(int i = 0; i < number_of_costumers; i++) {
    if(f[i] == TRUE) {
      count++;
    }
  }

  if(count == number_of_costumers) {
    return SAFE_STATE;
  }
} */


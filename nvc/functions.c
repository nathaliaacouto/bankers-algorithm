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

int system_state(int *av, int n[number_of_costumers][number_of_resources], int client, int al[number_of_costumers][number_of_resources])
{
  int work[number_of_resources];
  int finish[number_of_costumers];
  int exit = 0, count_true = 0;

  /* Initialize the arrays - Begin */
  for(int i = 0; i < number_of_resources; i++) { 
    work[i] = av[i]; 
  } 
  for(int i = 0; i < number_of_costumers; i++) {
    finish[i] = F;
  }
  /* Initialize the arrays - End */
  int arr_finish[number_of_costumers];
  int arr_work[number_of_resources];

  for(int i = 0; i < number_of_costumers; i++) {
    if(finish[i] == F) {
      arr_finish[i] = 1;
    }
    else {
      arr_finish[i] = 0;
    }
  } 
  for(int i = 0; i < number_of_resources; i++) {
    if(n[client][i] <= work[i]) {
      arr_work[i] = 1;
    }
    else {
      arr_work[i] = 0;
    }
  }

  for(int i = 0; i < number_of_resources; i++) { //i = 1
    for(int j = 0; j < number_of_costumers; j++) { //j = 0
      if(arr_work[i] == 1 && arr_finish[j] == 1) { 
        work[i] = work[i] + al[client][i];
        finish[j] = T;
      }
    }
  }

  for(int j = 0; j < number_of_costumers; j++) {
    if(finish[j] == T) {
      count_true++;
    }
  }

  if(count_true == number_of_costumers) {
    return SAFE_STATE;
  }
  return UNSAFE_STATE;
}

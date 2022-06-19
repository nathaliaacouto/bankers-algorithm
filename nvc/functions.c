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

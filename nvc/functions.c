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

/* Get String from a file and turn it into Int
Then, add the numbers into a array and returns this array */
void get_maximum(void) 
{
  FILE *costumers = fopen("customer.txt", "r");
  error_open_file(costumers);

  int maximum[number_of_costumers][number_of_resources];
  int aux;

  for(int i = 0; i < number_of_resources; i++) {
    for(int j = 0; j < number_of_costumers; j++) {
      fscanf(costumers, "%d", &aux);
      maximum[i][j] = aux;
    }
  }

  for(int i = 0; i < number_of_resources; i++) {
    for(int j = 0; j < number_of_costumers; j++) {
      printf("%d  ", maximum[i][j]);
    }
    printf("\n");
  }

  fclose(costumers);
}

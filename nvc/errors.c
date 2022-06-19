#include "errors.h"

/* Check for error opening a file */
int error_open_file(FILE *file)
{
  if (file == NULL) {
    printf("Error opening file");
    exit(0);
  }
  return 0;
}

/* Check if file is empty */
int error_file_empty(int count)
{
  if (count < 1) {
    printf("Error: file empty");
    exit(0);
  }
  return 0;
}

int error_more_than_available(int* av, int** max)
{
  for(int i = 0; i < number_of_costumers; i++) {
    for(int j = 0; i < number_of_resources; j++) {
      if (max[i][j] > av[i]) {
        printf("Error: Maximum number of resource is more than Available");
        exit(0);
      }
    }
  }
  return 0;
}
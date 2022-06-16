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
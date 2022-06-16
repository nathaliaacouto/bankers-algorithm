#include "functions.h"

int main(int argc, char *argv[ ]) 
{  
  number_of_resources = argc;
  int available[number_of_resources];

  for(int i = 1; i < number_of_resources; i++) {
    available[i] = atoi(argv[i]);
  }

  return 0;
}
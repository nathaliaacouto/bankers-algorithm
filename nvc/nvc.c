#include "functions.h"
#include "errors.h"

int main(int argc, char *argv[ ]) 
{  
  //Get the number of resources
  number_of_resources = argc-1;
  
  int available[number_of_resources];

  //get number of available resources from command line
  for(int i = 1; i < number_of_resources; i++) {
    available[i] = atoi(argv[i]);
  }
  
  FILE *costumers = fopen("customer.txt", "r");
  error_open_file(costumers);
  number_of_costumers = count_file_lines(costumers);
  fclose(costumers);
  
  get_max_resources();

  FILE *commands = fopen("commands.txt", "r");
  int b = count_file_lines(commands);
  read_commands(b);
  
  int allocation[number_of_costumers][number_of_resources];

  return 0;
}
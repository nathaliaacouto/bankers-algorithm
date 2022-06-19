#include "functions.h"
#include "errors.h"

int main(int argc, char *argv[ ]) 
{  
  /* Declarations - Begin */
  //Get the number of resources
  number_of_resources = argc - 1;

  //Allocate array available
  available = (int*)malloc(number_of_resources*sizeof(int));

  //Number of resources the costumers still need
  int need[number_of_costumers][number_of_resources]; //need = max - allocation
  //Number of resources allocated to each costumer
  int allocation[number_of_costumers][number_of_resources];
  //Max number of resources each costumer will need
  int maximum[number_of_costumers][number_of_resources];
  /* Declarations - End */


  /* Initialize Matrices and Variables - Begin */
  int count_av = 0;
  //Get number of available resources from command line
  for(int i = 1; i < number_of_resources+1; i++) {
    available[count_av] = atoi(argv[i]);
    count_av++;
  }
  
  //Get number of costumers from file lines
  FILE *costumers = fopen("customer.txt", "r");
  error_open_file(costumers);
  number_of_costumers = count_file_lines(costumers);
  
  //Get number of commands from file lines
  FILE *commands = fopen("commands.txt", "r");
  error_open_file(commands);
  number_of_commands = count_file_lines(commands);

  for(int i = 0; i < number_of_costumers; i++) {
    for(int j = 0; j < number_of_resources; j++) {
      //In the start of program, no resource is allocated
      allocation[i][j] = 0;
    }
  }

  /* Get Max resources - Begin */
  /* The number of maximum resources for each 
  costumer is given in the costumer.txt file */
  int read_costumer;

  for(int i = 0; i < number_of_costumers; i++) {
    for(int j = 0; j < number_of_resources; j++) {
      fscanf(costumers, "%d,", &read_costumer);
      maximum[i][j] = read_costumer; //OK - tá pegando os valores direito
    }
  }

  fclose(costumers);
  /* Get Max resources - End */
  
  for(int i = 0; i < number_of_costumers; i++) {
    for(int j = 0; j < number_of_resources; j++) {
      //In the start of the program, need = maximum
      need[i][j] = maximum[i][j]; //OK - tá pegando os valores direitinho
    }
  }
  /* Initialize Matrices and Variables - End */

  FILE *result = fopen("result.txt", "w");
  //char *c = read_commands();
  FILE *com = fopen("commands.txt", "r");
  int x = 0;
  char commands_arr[100];
  while(x != number_of_commands) {
    fgets(commands_arr, 20, com);
    printf("%s", commands_arr);
    int verify = verify_command(commands_arr);
    //printf("%d ", verify);
    if(verify == REQUEST_RESOURCES) {
      int index = 3;
      int client = commands_arr[index] - '0'; //cliente sempre o mesmo
      int req[number_of_resources+1];
      req[0] = client;
      for(int i = 1; i < number_of_resources; i++) {
        index = index + 2; //jump space between numbers
        req[i] = commands_arr[index] - '0';
      }
      for(int j = 0; j < number_of_resources; j++) {
        if(req[j] >= need[client][j]) {
          fprintf(result, "The customer %d request %d %d %d was denied because exceed its maximum allocation\n", req[0], req[1], req[2], req[3]);
          break;
        }
        if(req[j] <= available[j]) {
          available[j] = available[j] - req[j];
          allocation[client][j] = allocation[client][j] + req[j];
          need[client][j] = need[client][j] - req[j]; 
          //precisa verificar se o estado novo é seguro, caso não, volta
        }
        else if(req[j] > available[j]) {
          fprintf(result, "The customer %d request %d %d %d was denied because exceed the available resources\n", req[0], req[1], req[2], req[3]);
        }
      }
    }
    else if(verify == RELEASE_RESOURCES) {
      //
    }
    else if(verify == SHOW_VALUES) {
      fprintf(result, "MAXIMUM | ALLOCATION | NEED\n");
      for(int i = 0; i < number_of_costumers; i++) {
        for(int j = 0; j < number_of_resources; j++) {
          fprintf(result, "%d ", maximum[i][j]);
        }
        fprintf(result, "\t|");
        for(int j = 0; j < number_of_resources; j++) {
          fprintf(result, "%d ", allocation[i][j]);
        }
        fprintf(result, "\t\t   |");
        for(int j = 0; j < number_of_resources; j++) {
          fprintf(result, "%d ", need[i][j]);
        }
        fprintf(result, "\n");
      }
      fprintf(result, "AVAILABLE");
      for(int i = 0; i < number_of_resources; i++) {
        fprintf(result, " %d ", available[i]);
      }
      fprintf(result, "\n");
    }
    else {
      //printf("\nCommand %d not known, it will be skipped\n", x);
    }
    x++;
  }
  count_commands = 0;


  /* Safe State - Begin */
  //n is the number of threads in the system and, m is the number of resource types
  int work[number_of_resources];
  int finish[number_of_costumers];
  for(int i = 0; i < number_of_resources; i++) {
    work[i] = available[i];
  }
  for(int i = 0; i < number_of_costumers; i++) {
    finish[i] = FALSE;
  }
  int a = 0;
  for(int i = 0; i < number_of_costumers; i++) {
    for(int j = 0; j < number_of_resources; j++) {
      if(finish[i] == FALSE && (need[i][j] <= work[j])) {
        finish[i] = TRUE;
        work[j] = work[j] + allocation[i];
      }
      else {
        a = 1;
      }
    }
    if(a == 1) {
      break;
    }
  }
  int count_finish = 0;
  for(int i = 0; i < number_of_resources; i++) {
    if(finish[i] == TRUE) {
      count_finish++;
    }
  }
  if(count_finish == number_of_resources) {
    printf("\nSystem in safe state\n");
  }
  else {
    printf("\nSystem not safe\n");
  }
  /* Safe State - End */

  free(available);
  fclose(result);
  fclose(commands);

  return 0;
}
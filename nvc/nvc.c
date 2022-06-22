#include "functions.h"
#include "errors.h"

int main(int argc, char *argv[ ]) 
{  
  //Get the number of resources
  number_of_resources = argc - 1;

  //Get number of costumers from file lines
  FILE *costumers = fopen("customer.txt", "r");
  error_open_file(costumers);
  number_of_costumers = count_file_lines(costumers);
  fclose(costumers);

  //Allocate array available
  available = (int*)malloc(number_of_resources*sizeof(int));
  
  /* Initialize Matrices and Variables - Begin */
  int count_av = 0;
  //Get number of available resources from command line
  for(int i = 1; i < number_of_resources+1; i++) {
    available[count_av] = atoi(argv[i]);
    count_av++;
  }


  /* Declarations - Begin */
  
  //Number of resources the costumers still need
  int need[number_of_costumers][number_of_resources]; //need = max - allocation
  //Number of resources allocated to each costumer
  int allocation[number_of_costumers][number_of_resources];
  //Max number of resources each costumer will need
  int maximum[number_of_costumers][number_of_resources];
  
  /* Declarations - End */

  //Get number of commands from file lines
  FILE *commands = fopen("commands.txt", "r");
  error_open_file(commands);
  number_of_commands = count_file_lines(commands);
  error_file_empty(number_of_commands);

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
  FILE *cos = fopen("customer.txt", "r");
  error_open_file(cos);
  for(int i = 0; i < number_of_costumers; i++) {
    for(int j = 0; j < number_of_resources; j++) {
      fscanf(cos, "%d,", &read_costumer);
      maximum[i][j] = read_costumer; 
    }
  }
  fclose(cos);
  /* Get Max resources - End */
  
  for(int i = 0; i < number_of_costumers; i++) {
    for(int j = 0; j < number_of_resources; j++) {
      //In the start of the program, need = maximum
      need[i][j] = maximum[i][j]; //OK - tá pegando os valores direitinho
    }
  }
  /* Initialize Matrices and Variables - End */
 
  /* Read Commands - Begin */
  FILE *result = fopen("result.txt", "w");
  error_open_file(result);
  FILE *com = fopen("commands.txt", "r");
  error_open_file(com);
  int count_commands = 0;
  char commands_arr[100];
  while(count_commands != number_of_commands) { 
    fgets(commands_arr, 20, com); 
    /* Read Commands - End */

    /* Do Commands - Begin */
    int exit = 0;
    int verify = verify_command(commands_arr); 
    if(verify == REQUEST_RESOURCES) { 
      int index = 3; 
      int client = commands_arr[index] - '0'; 
      int req[number_of_resources+1]; 
      req[0] = client;
      for(int i = 1; i < number_of_resources + 1; i++) {
        index = index + 2; //jump space between numbers
        req[i] = commands_arr[index] - '0'; 
      }

      int c = 0;
      for(int j = 1; j < number_of_resources + 1; j++) {
        if (client > number_of_costumers || client < 0) {
          printf("The client %d does not exist, this command will be skipped", client);
          exit = 1;
          break;
        }
        if(req[j] > need[client][c]) { 
          fprintf(result, "The costumer %d request ", req[0]);
          for(int a = 1; a < number_of_resources + 1; a++) {
            fprintf(result, "%d ", req[a]);
          }
          fprintf(result, "was denied because exceed its maximum allocation\n");
          exit = 1;
          break; 
        }
        c++;
      }
      
      if(exit == 0) {
        int unsafe = 0;
        c = 0;
        int count_av = 0;
        for(int j = 1; j < number_of_resources + 1; j++) {
          if(req[j] <= available[c]) {
            count_av++;
          }
          c++;
        }
        c = 0;
        if(count_av == number_of_resources) {
          for(int j = 1; j < number_of_resources + 1; j++) {
            available[c] = available[c] - req[j]; 
            allocation[client][c] = allocation[client][c] + req[j]; 
            need[client][c] = maximum[client][c] - allocation[client][c];
            c++;
          }
          //Verify is system is safe after alteration
          int sys_state = system_state(available, need, client, allocation); 
          if(sys_state == UNSAFE_STATE) {
            c = 0;
            for(int j = 1; j < number_of_resources + 1; j++) {
              available[c] = available[c] + req[j]; 
              allocation[client][c] = allocation[client][c] - req[j]; 
              need[client][c] = maximum[client][c] - allocation[client][c];
              c++;
            }
            unsafe = 1;
          }
          if(unsafe == 0) {
            fprintf(result, "Allocate to customer %d the resources ", req[0]);
            for(int a = 1; a < number_of_resources + 1; a++) {
              fprintf(result, "%d ", req[a]);
            }
            fprintf(result, "\n");
          }
          else if(unsafe == 1) {
            fprintf(result, "The customer %d request ", req[0]);
            for(int a = 1; a < number_of_resources + 1; a++) {
              fprintf(result, "%d ", req[a]);
            }
            fprintf(result, "was denied because result in an unsafe state\n");
          }
        }
        else {
          fprintf(result, "The resources ");
          for(int i = 0; i < number_of_resources; i++) {
            fprintf(result, "%d ", available[i]);
          }
          fprintf(result, "are not enough to customer %d request ", req[0]);
          for(int a = 1; a < number_of_resources + 1; a++) {
            fprintf(result, "%d ", req[a]);
          }
          fprintf(result, "\n");
        }
      }
      c = 0;
      c++;
      exit = 0;
    }

    else if(verify == RELEASE_RESOURCES) {
      int index = 3; 
      int client = commands_arr[index] - '0'; 
      int req[number_of_resources+1]; 
      req[0] = client;
      exit = 0;
      if (client > number_of_costumers || client < 0) {
          printf("The client %d does not exist, this command will be skipped", client);
          exit = 1;
          break;
      }
      if(exit == 0) {
        for(int i = 1; i < number_of_resources + 1; i++) {
          index = index + 2; //jump space between numbers
          req[i] = commands_arr[index] - '0'; 
        }
        int c = 0;
        for(int i = 1; i < number_of_resources + 1; i++) {
          available[c] = available[c] + req[i]; //Return the resources to available
          c++;
        }
        c = 0;
        for(int i = 1; i < number_of_resources + 1; i++) {
          allocation[client][c] = allocation[client][c] - req[i];
          need[client][c] = maximum[client][c] - allocation[client][c];
          c++;
        }

        fprintf(result, "Release from costumer %d the resources ", req[0]);
        for(int a = 1; a < number_of_resources + 1; a++) {
          fprintf(result, "%d ", req[a]);
        }
        fprintf(result, "\n");
      }
    }

    else if(verify == SHOW_VALUES) {
      fprintf(result, "MAXIMUM\t|ALLOCATION\t|NEED\n");
      for(int i = 0; i < number_of_costumers; i++) {
        for(int j = 0; j < number_of_resources; j++) {
          fprintf(result, "%d ", maximum[i][j]);
        }
        fprintf(result, "\t|");
        for(int j = 0; j < number_of_resources; j++) {
          fprintf(result, "%d ", allocation[i][j]);
        }
        fprintf(result, "\t\t\t|");
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
      printf("\nCommand %d not known, it will be skipped\n", count_commands);
    }
    /* Do Commands - End */
    count_commands++;
  }

  free(available);
  fclose(result);
  fclose(commands);
  fclose(com);

  return 0;
}
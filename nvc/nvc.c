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

  for(int i = 0; i < number_of_resources; i++) {
    printf(" %d ", available[i]);
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
  FILE *com = fopen("commands.txt", "r");
  int count_commands = 0;
  char commands_arr[100];
  while(count_commands != number_of_commands) { 
    fgets(commands_arr, 20, com); 
    /* Read Commands - End */
    //O ARQUIVO RESULT ESTÁ DIFERENTE DO DELE PQ AINDA NÃO DEI RELEASE!!!
    /* Do Commands - Begin */
    int exit = 0;
    int verify = verify_command(commands_arr); 
    if(verify == REQUEST_RESOURCES) { //request está funcionando
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
        c = 0;
        int count_av = 0;
        for(int j = 1; j < number_of_resources + 1; j++) {
          if(req[j] <= available[c]) {
            count_av++;
            //precisa verificar se o estado novo é seguro, caso não, volta
          }
          c++;
        }
        c = 0;
        if(count_av == number_of_resources) {
          for(int j = 1; j < number_of_resources + 1; j++) {
            available[c] = available[c] - req[j]; //ok
            allocation[client][c] = allocation[client][c] + req[j]; 
            need[client][c] = maximum[client][c] - allocation[client][c];
            c++;
          }
          fprintf(result, "Allocate to customer %d the resources %d %d %d\n", req[0], req[1], req[2], req[3]);
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


    else if(verify == SHOW_VALUES) {
      fprintf(result, "MAXIMUM |ALLOCATION  |NEED\n");
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
      printf("\nCommand %d not known, it will be skipped\n", count_commands);
    }
    /* Do Commands - End */
    count_commands++;
  }

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
  fclose(com);

  return 0;
}
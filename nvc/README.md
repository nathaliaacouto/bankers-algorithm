# Banker’s Algorithm :money_with_wings:
This exercise is based in *Banker’s Algorithm* shown in page P-45 of the book *Operating System Concepts by Silberschatz, A.* \
\
The idea of this implementation is to simulate the Banker’s Algorithm which is one of the famous ways to **Avoid Deadlocks**. 

## How it works 🤔
- The amout of each resource is passed in the command line and the code identifies how many resources there are in total, for exemple:
  - `./banker 10 10 10`: there are 3 resources with 10 each in the system.
- From the file `customer.txt` the amout of costumers and, for each of them, the maximum needed of each resource.
- In the file `commands.txt` the commands are read, there are three of them:
  - RQ: Request Resources
  - RL: Release Resources
  - *: Show Values
- The `result.txt` file shows the output for each command, if it was possible or not to request the resource, if the resource was released, and the matrices.

### Commands to test it :pencil:
- `git clone https://github.com/nathaliaacouto/bankers-algorithm.git`: Clone the repository in your machine
- `cd nvc`: Get inside the folder where the code is
- `make`: Compile code
- `./banker + amout of resources`: Run code*
- `make clean`: Clean project, delete the files created by the Makefile

### Files Index :file_folder:
- main: `nvc.c`
- all functions used: `functions.c`
- error treatment: `errors.c`
- files created by implementation: `result.txt`

### Contact me :phone:
If you have any questions about the code, or issues you might have found, 
feel free to contact me through my github: [@nathaliaacouto](https://github.com/nathaliaacouto)

*Created by Nathália Couto*

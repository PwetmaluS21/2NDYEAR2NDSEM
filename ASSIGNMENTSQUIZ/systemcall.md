Code Explanation: Process Creation and Process Tree Management
This C++ program demonstrates process forking and process tree creation in Linux/Unix systems. It creates multiple child processes and grandchild processes, showing the hierarchical relationship between parent and child processes.

Overview
The program creates a process tree with the following structure:


        Parent       /      \   Child1    Child2    /          /Grandchild1  Grandchild2
Each process prints its own Process ID (PID) to show the execution sequence.

Header Files Explained

#include <iostream>
Standard input/output library for console output (cout, cerr, endl).


#include <unistd.h>
Provides access to POSIX API functions like fork() and getpid().

fork(): Creates a new process (child process)
getpid(): Returns the Process ID of the current process

#include <sys/wait.h>
Provides the wait() function to synchronize process execution.

wait(NULL): Makes parent process wait for child process to complete
Main Program Flow
Variable Declarations

pid_t pid1, pid2, pid3, pid4;
pid_t is a special data type for storing Process IDs. These variables store:

pid1: Return value of first fork() call
pid2: Return value of second fork() call
pid3: Return value of fork in first child
pid4: Return value of fork in second child
Fork Operation and Return Values
The fork() function is the key to this program. When called, it does:

Creates an exact copy of the calling process
Returns different values to parent and child:
Parent process: fork() returns the child's PID (positive number)
Child process: fork() returns 0
Error: fork() returns -1
Step-by-Step Execution
First Fork: Creating First Child

pid1 = fork();if (pid1 < 0) {    cerr << "Fork failed" << endl;    return 1;}else if (pid1 == 0) {    // This code runs in FIRST CHILD process    // Code here...}else {    // This code runs in PARENT process    // Code here...}
What happens:

fork() creates a new process
If fork fails (returns -1), error message is printed
If pid1 == 0: We are in the child process (First Child)
If pid1 > 0: We are in the parent process
First Child Creates Grandchild
Inside the first child process (when pid1 == 0):


pid3 = fork();if (pid3 < 0) {    cerr << "Fork failed" << endl;    return 1;}else if (pid3 == 0) {    // GRANDCHILD 1 process    cout << "Grandchild Process ID: " << getpid() << endl;} else {    wait(NULL); // Wait for grandchild to complete    cout << "First Child Process ID: " << getpid() << endl;}
Execution:

First child creates another process (grandchild)
Grandchild prints its PID
First child waits for grandchild to finish using wait(NULL)
First child prints its PID after grandchild completes
Parent Creates Second Child
In the parent process (when pid1 > 0):


pid2 = fork();if (pid2 < 0) {    cerr << "Fork failed" << endl;    return 1;}else if (pid2 == 0) {    // SECOND CHILD process    pid4 = fork();    if (pid4 < 0) {        cerr << "Fork failed" << endl;        return 1;    }    else if (pid4 == 0) {        // GRANDCHILD 2 process        cout << "Grandchild Process ID: " << getpid() << endl;    } else {        wait(NULL); // Wait for grandchild        cout << "Second Child Process ID: " << getpid() << endl;    }}else {    wait(NULL); // Wait for first child    wait(NULL); // Wait for second child    cout << "Parent Process ID: " << getpid() << endl;}
Execution:

Parent creates second child process
Second child creates its own grandchild (grandchild 2)
Grandchild 2 prints its PID
Second child waits for grandchild 2 to complete
Second child prints its PID
Parent waits for both children to complete
Parent prints its PID
Process Tree Visualization

Parent Process (Main)    |    ├─── First Child (from first fork)    |    └─── Grandchild 1 (from fork inside first child)    |    └─── Second Child (from second fork)         └─── Grandchild 2 (from fork inside second child)
Wait() Function Explanation

wait(NULL);
Purpose: Makes the parent process wait until a child process terminates
Benefit: Ensures proper synchronization and prevents zombie processes
NULL parameter: Means we don't care about the exit status of the child
Sequence: In parent, two wait() calls ensure both children complete before parent prints
Execution Order
Grandchild 1 prints (executes first among its branch)
First Child prints (after waiting for grandchild 1)
Grandchild 2 prints (executes first among its branch)
Second Child prints (after waiting for grandchild 2)
Parent prints (after waiting for both children)
Complete Code in Text Format

#include <iostream>#include <unistd.h>#include <sys/wait.h>using namespace std;int main(){    pid_t pid1, pid2, pid3, pid4;    pid1 = fork();    if (pid1 < 0) {        cerr << "Fork failed" << endl;        return 1;    }    else if (pid1 == 0) {        // First child process        pid3 = fork();        if (pid3 < 0) {            cerr << "Fork failed" << endl;            return 1;        }        else if (pid3 == 0) {            // Grandchild process            cout << "Grandchild Process ID: " << getpid() << endl;        } else {            wait(NULL);            cout << "First Child Process ID: " << getpid() << endl;        }    }     else {        // Parent process        pid2 = fork();        if (pid2 < 0) {            cerr << "Fork failed" << endl;            return 1;        }        else if (pid2 == 0) {            // Second child process            pid4 = fork();            if (pid4 < 0) {                cerr << "Fork failed" << endl;                return 1;            }            else if (pid4 == 0) {                // Grandchild process                cout << "Grandchild Process ID: " << getpid() << endl;            } else {                wait(NULL);                cout << "Second Child Process ID: " << getpid() << endl;            }        }         else {            wait(NULL);            wait(NULL);            cout << "Parent Process ID: " << getpid() << endl;        }    }    return 0;}
Typical Output Example

Grandchild Process ID: 1523First Child Process ID: 1521Grandchild Process ID: 1524Second Child Process ID: 1522Parent Process ID: 1520
Note: PIDs will be different each time you run the program, but the order remains consistent.

Key Concepts
Fork()
Duplicates the entire process
Child gets a copy of parent's memory, file descriptors, etc.
Returns 0 to child, child's PID to parent
Process ID (PID)
Unique identifier assigned to each process
getpid() returns the current process's PID
Parent-Child Relationship
Parent that creates child is responsible for waiting on it
Without wait(), child becomes a "zombie" process
Synchronization
wait(NULL) ensures parent waits for child completion
Prevents parent from exiting before children finish
Error Handling
Checks if fork() failed (returns -1)
Prints error message if fork fails
Returns 1 to indicate error
Use Cases
This type of process forking is used in:

Web servers: Creating child processes to handle client requests
Batch processing: Creating multiple worker processes
Daemon programs: Creating background processes
Parallel processing: Running tasks concurrently in separate processes
Important Notes
Each fork() doubles the number of active processes
This program creates 4 child processes total (2 children + 2 grandchildren)
The program uses wait() for proper process synchronization
Process IDs are assigned by the operating system and vary each execution
This code is specific to Linux/Unix systems (won't work on Windows)

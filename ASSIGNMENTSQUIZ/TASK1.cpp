#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(){
    pid_t pid1, pid2, pid3, pid4;

    pid1 = fork();
    if (pid1 < 0) {
        cerr << "Fork failed" << endl;
        return 1;
    }
    else if (pid1 == 0) {
        // First child process
        pid3 = fork();
        if (pid3 < 0) {
            cerr << "Fork failed" << endl;
            return 1;
        }
        else if (pid3 == 0) {
            // Grandchild process
            cout << "Grandchild Process ID: " << getpid() << endl;
        } else {
            wait(NULL); // Wait for grandchild
            cout << "First Child Process ID: " << getpid() << endl;
        }
    } 
    else {
        // Parent process
        pid2 = fork();
        if (pid2 < 0) {
            cerr << "Fork failed" << endl;
            return 1;
        }
        else if (pid2 == 0) {
            // Second child process
            pid4 = fork();
            if (pid4 < 0) {
                cerr << "Fork failed" << endl;
                return 1;
            }
            else if (pid4 == 0) {
                // Grandchild process
                cout << "Grandchild Process ID: " << getpid() << endl;
            } else {
                wait(NULL); // Wait for grandchild
                cout << "Second Child Process ID: " << getpid() << endl;
            }
        } 
        else {
            wait(NULL); // Wait for first child
            wait(NULL); // Wait for second child
            cout << "Parent Process ID: " << getpid() << endl;
        }
    }
    return 0;
}
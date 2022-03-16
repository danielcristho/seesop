#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {
    pid_t child_id;
    int status;
    child_id = fork();

    if (child_id < 0) {
        exit(EXIT_FAILURE);
    }

    if (child_id == 0) {
    //child process

    char *argv[] = {"mkdir", "-p", "/home/daniel1/modul2/darat", NULL };
    execv("/bin/mkdir", argv);

    } else {
        //parent
    while ((wait(&status)) > 0);
    char *argv[] = {"mkdir", "-p", "/home/daniel1/modul2/air", NULL};
    execv("/bin/mkdir", argv);
    }

}
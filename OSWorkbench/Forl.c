#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <readline/history.h>
#include <sys/wait.h>

int main(){
    pid_t child=fork();
    if(child==0){
        printf("This is the child because the value is 0\n\n");
        printf("%d",getpid());
    }
    else {
        printf("This is the parent part with process id as %d\n\n",getpid());
        printf("The child is %d",child);
    }
    return 0;
}
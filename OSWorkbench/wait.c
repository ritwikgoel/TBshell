#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <readline/history.h>
#include <sys/wait.h>
int main(){
    pid_t child,staller;
    int status;

    child=fork();
    if(child==0){
        //child process
        printf("this is the child\n\n");
        for(int i=0;i<10;i++){
            printf("%d",i);
            
        }
        printf("\n");
        sleep(1);
    }
    else{
        //parent block
        staller= waitpid(child,&status,WUNTRACED);
        printf("This is supposed to beprinted aftewr 1 second of the chi;d sleep\n\n");

    }
    return 0;
}
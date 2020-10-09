#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <readline/history.h>
#include <sys/wait.h>

int main(){
    int arr[2];
    pipe(arr);
    pid_t child=fork();
    if(child==0){
        //child 
        close(arr[0]);
        printf("ENter a value");
        int x;
        scanf("%d",&x);
        write(arr[1],&x,sizeof(x));
        close(arr[1]);
    }
    else {
        //parent process
        close(arr[1]);
        int lol;
        read(arr[0],&lol,sizeof(lol));
        printf("%d",lol);

    }
    return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    pid_t child=fork();
    printf("%d \n",child);
    printf("%d",getpid());
    if(child==0){
        sleep(1);
        printf("THis is chile %d \n",child);
    }
    else 
    {
        printf("%d",getpid());
    }
    return 0;
}
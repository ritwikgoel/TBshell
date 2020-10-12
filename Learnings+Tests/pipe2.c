#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <readline/history.h>
#include <sys/wait.h>
#include<sys/stat.h>


int main(){
    //summning elements dividing the work
    int fd[2];
    int arr[]={1,2,3,4,5,6,7,8,9};
    int len=sizeof(arr)/sizeof(arr[2]);
    pipe(fd);
    pid_t child=fork();
    if(child==0){
        int start =0;
        int end=len/2;
        int sum=0;
        for(int i=0;i<end;i++){
            sum+=arr[i];
        }
        printf("%d",sum);
        close(fd[0]);
        write(fd[1],&sum,sizeof(sum));
        close(fd[1]);
    }
    else{
        close(fd[1]);
        int start= len/2;
        int end= len;
        int sum=0,new;
        for(int i=start;i<end;i++)sum+=arr[i];
        printf("%d",sum);
        read(fd[1],&new,sizeof(sum));
        sum+=new;
        close(fd[1]);
        printf("%d",sum);
    }
    return 0;
}

//a better method is to declare start and end only in the child and parents
//then write the loop only once 
//then once again we can call the if(child==0)
//then read and add and print 
//also wait for the child process to finish in the end as we need 
//also call the if  statements multiple times 

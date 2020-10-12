#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <readline/history.h>
#include <sys/wait.h>
 int main()
 {
     //they are called file descriptors
     int arr[2];//0 for reading and 1 for writing i think 
     pipe(arr);
     pid_t child=fork();
     if(child==0){
         //child
         close(arr[0]);
         int x;
         scanf("%d",&x);
         write(arr[1],&x,sizeof(x));
         close(arr[1]);
     }
     else{
         close(arr[1]);
         int ans;
         read(arr[0],&ans,sizeof(ans));
         printf("%d",ans);
         close(arr[0]);
     }
     return 0;
 }
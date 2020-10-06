#include<stdio.h>
#include<unistd.h>
#include<syscall.h>

int main(){
    char *args[]={"ls","-l",NULL};
    execvp(args[0],args);
    return 0;
}
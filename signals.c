#include<signal.h>
#include<stdio.h>

int main(){
    void signal_handlee(int signo){
        printf("The signal has been caught!");
    }
    signal(SIGINT,signal_handlee);
    while(1);
}
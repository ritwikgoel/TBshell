#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <readline/history.h>
#include <sys/wait.h>
char **get_input(char *);
char **get_input(char *input) {
    char **command = malloc(10 * sizeof(char *));//mkaing a word of max 10 characters
    char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);//splittting into an array of char stirngs
    while (parsed != NULL) {
        command[index] = parsed;
        index++;

        parsed = strtok(NULL, separator);
    }

    command[index] = NULL;
    return command;
}
int main(){
    /*
    fork 
    child goes to exevp
    parent waits for the child to return 
    loop up baby
    handle cd later using the cd() function in c 
    */

  
   while(1){
        pid_t child,domer;
        int stat_loc;
       //ask for the input first
        char **command;
        char *input;

    
        input = readline("Kilt:> ");
        command = get_input(input);
       child=fork();
       if(child==0){
           //this is the child
           //run the execvp here 
           execvp(command[0],command);

       }
       else if(child!=0){
           //this is the parent 
           //wait for the child to return
           //THEn release all aloocated stuff.
           domer=waitpid(child,&stat_loc,WUNTRACED);
           free(input);
           free(command);

       }
   }
   return 0;
}
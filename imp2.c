#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <readline/history.h>
#include <sys/wait.h>
//ctrl+z to quit 
char **get_input(char *);
int cd(char *path) {
    return chdir(path);
}
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
    printf("Welcome to my shell\n\n");
    while(1){
        signal(SIGINT, SIG_IGN);//what this does is basically ignores the ctrl c
        pid_t child,domer;
        int stat_loc;
       //ask for the input first
        char **command;
        char *input;
        input = readline("Kilt:> $PATH~");//add the shell name here 
        command = get_input(input);
        //if the command is empty
            if (command[0]==NULL) {      /* Handle empty commands */
            free(input);
            free(command);
            printf("\n");
            continue;
        }
        if(strcmp(command[0], "cd") == 0){
            cd(command[1]);
            continue;
        }
        child=fork();
        if(child==0){
            //this is the child
            //over here before the execvp command we need to add a signal handler resetter
            signal(SIGINT,SIG_DFL);//this is signal defaulter. this will allow us to use ctrl c in out progrmam 
            execvp(command[0],command);
            printf("This is not supposed to get printed \n\n\n\n");//this can happen if the execvp is unknown
        }
        else if(child!=0){
            domer=waitpid(child,&stat_loc,WUNTRACED);
            printf("The command is sucessfully run\n");
            free(command);
            free(input);
        }
    }
    return 0;

}
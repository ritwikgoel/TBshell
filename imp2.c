#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <readline/history.h>
#include <sys/wait.h>
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
    while(1){
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
            continue;
        }
        if(strcmp(command[0], "cd") == 0){
            cd(command[1]);
            continue;
        }
        child=fork();
        if(child==0){
            //this is the child
            execvp(command[0],command);
            printf("This is not supposed to get printed \n\n\n\n");
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